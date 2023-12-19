/*
Copyright 2012-2020 Jun Wako, Jack Humbert, Yiancar, Kostyuk, Pierre Chevalier
          2023 ozsan <monkeypad39@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "quantum.h"
#include "matrix.h"
#include "debounce.h"
#include "wait.h"
#include "debug.h"
#include "i2c_master.h"
#include "print.h"

#ifdef SPLIT_KEYBOARD
#    include "split_common/split_util.h"
#    include "split_common/transactions.h"
#    include <string.h>
#    ifndef MATRIX_IO_DELAY
#        define MATRIX_IO_DELAY 30
#    endif
#    define ROWS_PER_HAND (MATRIX_ROWS / 2)
#else
#    define ROWS_PER_HAND (MATRIX_ROWS)
#endif

#ifdef DIRECT_PINS_RIGHT
#    define SPLIT_MUTABLE
#else
#    define SPLIT_MUTABLE const
#endif
#ifdef MATRIX_ROW_PINS_RIGHT
#    define SPLIT_MUTABLE_ROW
#else
#    define SPLIT_MUTABLE_ROW const
#endif
#ifdef MATRIX_COL_PINS_RIGHT
#    define SPLIT_MUTABLE_COL
#else
#    define SPLIT_MUTABLE_COL const
#endif

#ifndef MATRIX_INPUT_PRESSED_STATE
#    define MATRIX_INPUT_PRESSED_STATE 0
#endif

/* matrix state(1:on, 0:off) */
matrix_row_t raw_matrix[MATRIX_ROWS];
matrix_row_t matrix[MATRIX_ROWS];

#ifdef SPLIT_KEYBOARD
// row offsets for each hand
uint8_t thisHand, thatHand;
#endif

#ifdef MATRIX_MASKED
extern const matrix_row_t matrix_mask[];
#endif

// user-defined overridable functions
// I2C address:
// http://ww1.microchip.com/downloads/en/devicedoc/20001952c.pdf
// The I2C address pins of the mcp23107 can be selected by solder jumpers on the PCB.
// If you want to change it, change the lower 3 bits of I2C_ADDR.
// By default, all address pins are connected to ground on monkeypad.
// | 0  | 1  | 0  | 0  | A2 | A1 | A0 |
// | 0  | 1  | 0  | 0  | 0  | 0  | 0  |
#define I2C_WRITE 0x00
#define I2C_READ 0x01
#define I2C_ADDR 0b0100000
#define I2C_ADDR_WRITE ((I2C_ADDR << 1) | I2C_WRITE)
#define I2C_ADDR_READ ((I2C_ADDR << 1) | I2C_READ)

// Register addresses
#define IODIRA  0x00 // I/O direction register
#define IODIRB  0x01
#define GPPUA   0x0C // GPIO pull-up resistor register
#define GPPUB   0x0D
#define GPIOA   0x12 // general purpose i/o port register
#define GPIOB   0x13
#define OLATA   0x14 // output latch register
#define OLATB   0x15

bool           i2c_initialized = false;
i2c_status_t   mcp23017_status;
static uint8_t mcp23017_reset_loop;

// user-defined overridable functions
static void unselect_rows_mcu(void);
static bool select_row_mcu(uint8_t row);
static bool select_row_mcp(uint8_t row);

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }
__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }
__attribute__((weak)) void matrix_init_user(void) {}
__attribute__((weak)) void matrix_scan_user(void) {}

// user-defined overridable functions
uint8_t init_mcp23017(void) {
    dprintf("starting init\n");
    mcp23017_status = I2C_ADDR;

    // I2C subsystem
    if (i2c_initialized == 0) {
        i2c_init(); // on pins D(1,0)
        i2c_initialized = true;
        wait_ms(I2C_TIMEOUT);
    }

    // Set pin direction (diode direction COL to ROW)
    // Read all the pins on GPIOA (GPA0:col0, GPA1:col1, GPA2:col2, GPA3:col3, GPA4:col4, GPA5:col5)
    // Write to the pins 0-8 on GPIOB (GPB5:row0, GPB4:row1, GPB3:row2, GPB2:row3)
    uint8_t buf[]   = {IODIRA, 0b11111111, 0b11000011};
    mcp23017_status = i2c_transmit(I2C_ADDR_WRITE, buf, sizeof(buf), I2C_TIMEOUT);

    if (!mcp23017_status) {
        uint8_t pullup_buf[] = {GPPUA, 0b11111111, 0b00000000};
        mcp23017_status      = i2c_transmit(I2C_ADDR_WRITE, pullup_buf, sizeof(pullup_buf), I2C_TIMEOUT);
    }
    return mcp23017_status;
}

inline matrix_row_t matrix_get_row(uint8_t row) {
    // Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
    // switch blocker installed and the switch is always pressed.
#ifdef MATRIX_MASKED
    return matrix[row] & matrix_mask[row];
#else
    return matrix[row];
#endif
}

#define print_matrix_header() print("\nr/c 01234567\n")
#define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))

void matrix_print(void) {
    print_matrix_header();
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row);
        print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

#ifdef SPLIT_KEYBOARD
bool matrix_post_scan(void) {
    bool changed = false;
    if (is_keyboard_master()) {
        static bool  last_connected              = false;
        matrix_row_t slave_matrix[ROWS_PER_HAND] = {0};

        if (transport_master_if_connected(matrix + thisHand, slave_matrix)) {
            changed = memcmp(matrix + thatHand, slave_matrix, sizeof(slave_matrix)) != 0;
            last_connected = true;
        } else if (last_connected) {
            // reset other half when disconnected
            memset(slave_matrix, 0, sizeof(slave_matrix));
            changed = true;
            last_connected = false;
        }

        if (changed) {
            memcpy(matrix + thatHand, slave_matrix, sizeof(slave_matrix));
        }

        matrix_scan_kb();
    } else {
        transport_slave(matrix + thatHand, matrix + thisHand);

        matrix_slave_scan_kb();
    }

    return changed;
}
#endif

/* `matrix_io_delay ()` exists for backwards compatibility. From now on, use matrix_output_unselect_delay(). */
__attribute__((weak)) void matrix_io_delay(void) {
    wait_us(MATRIX_IO_DELAY);
}
__attribute__((weak)) void matrix_output_select_delay(void) {
    waitInputPinDelay();
}
__attribute__((weak)) void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    matrix_io_delay();
}

static matrix_row_t read_cols_mcp(uint8_t row) {
    dprintf("mcp23017_status: %d\n", mcp23017_status);
    if (mcp23017_status) { // if there was an error
        return 0;
    } else {
        uint8_t buf[]   = {GPIOA};
        mcp23017_status = i2c_transmit(I2C_ADDR_WRITE, buf, sizeof(buf), I2C_TIMEOUT);

        uint8_t data[] = {0};
        if (!mcp23017_status) {
            mcp23017_status = i2c_receive(I2C_ADDR_READ, data, sizeof(data), I2C_TIMEOUT);
            data[0]         = ~(data[0]);
        }
        return data[0];
    }
}

// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_matrix_row(matrix_row_t current_matrix[], uint8_t index) {
    matrix_row_t temp = read_cols_mcp(index);
    if (current_matrix[index] != temp) {
        current_matrix[index] = temp;
        return true;
    }
    return false;
}

__attribute__((weak)) void matrix_init_custom(void) {
    mcp23017_status = init_mcp23017();

    unselect_rows_mcu();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    if (mcp23017_status) { // if there was an error
        if (++mcp23017_reset_loop == 0) {
            // since mcp23017_reset_loop is 8 bit - try to reset once in 255 matrix scans
            dprintf("trying to reset mcp23017\n");
            mcp23017_status = init_mcp23017();
            if (mcp23017_status) {
                dprintf("sub board is not responding\n");
            } else {
                dprintf("sub board is connected\n");
            }
        }
    }

    for (uint8_t index = 0; index < ROWS_PER_HAND - MATRIX_ROWS_MCU; index++) {
        // select rows from left and right hands
        select_row_mcp(index);

        uint8_t left_index  = index;
        uint8_t right_index = index + ROWS_PER_HAND;
        changed |= store_matrix_row(current_matrix, left_index);
        changed |= store_matrix_row(current_matrix, right_index);
    }

    unselect_rows_mcu();

    return changed;
}

#ifdef SPLIT_KEYBOARD
__attribute__((weak)) void matrix_slave_scan_kb(void) {
    matrix_slave_scan_user();
}
__attribute__((weak)) void matrix_slave_scan_user(void) {}
#endif

__attribute__((weak)) bool peek_matrix(uint8_t row_index, uint8_t col_index, bool raw) {
    return 0 != ((raw ? raw_matrix[row_index] : matrix[row_index]) & (MATRIX_ROW_SHIFTER << col_index));
}

#ifdef MATRIX_ROW_PINS
static SPLIT_MUTABLE_ROW pin_t row_pins[ROWS_PER_HAND] = MATRIX_ROW_PINS;
#endif
#ifdef MATRIX_COL_PINS
static SPLIT_MUTABLE_COL pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
extern matrix_row_t matrix[MATRIX_ROWS];     // debounced values

#ifdef SPLIT_KEYBOARD
// row offsets for each hand
extern uint8_t thisHand, thatHand;
#endif

__attribute__((weak)) void matrix_init_pins(void);
__attribute__((weak)) void matrix_read_cols_mcu(matrix_row_t current_matrix[], uint8_t current_row);

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinOutput_writeHigh(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinHigh(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinInputHigh(pin);
    }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return (readPin(pin) == MATRIX_INPUT_PRESSED_STATE) ? 0 : 1;
    } else {
        return 1;
    }
}

#if defined(DIODE_DIRECTION)
#    if defined(MATRIX_ROW_PINS) && defined(MATRIX_COL_PINS)
#        if (DIODE_DIRECTION == COL2ROW)

static bool select_row_mcu(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
        return true;
    }
    return false;
}

static void unselect_row_mcu(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinInputHigh_atomic(pin);
    }
}

static void unselect_rows_mcu(void) {
    for (uint8_t x = 0; x < ROWS_PER_HAND; x++) {
        unselect_row_mcu(x);
    }
}

static bool select_row_mcp(uint8_t row) {
    // select on mcp23017
    if (mcp23017_status) { // if there was an error
        return false;      // do nothing
    } else {
        // Select the row pins to write on the GPIOB bus.
        // Write to the pins 0-8 on GPIOB (GPB5:row0, GPB4:row1, GPB3:row2, GPB2:row3)
        uint8_t buf[]   = {GPIOB, 0xFF & ~(1 << (5 - row))};
        mcp23017_status = i2c_transmit(I2C_ADDR_WRITE, buf, sizeof(buf), I2C_TIMEOUT);
    }
    return true;
}

__attribute__((weak)) void matrix_init_pins(void) {
    unselect_rows_mcu();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (col_pins[x] != NO_PIN) {
            setPinInputHigh_atomic(col_pins[x]);
        }
    }
}

__attribute__((weak)) void matrix_read_cols_mcu(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    if (!select_row_mcu(current_row)) { // Select row
        return;                         // skip NO_PIN row
    }
    matrix_output_select_delay();

    // For each col...
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
        uint8_t pin_state = readMatrixPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : row_shifter;
    }

    // Unselect row
    unselect_row_mcu(current_row);
    matrix_output_unselect_delay(current_row, current_row_value != 0); // wait for all Col signals to go HIGH

    // Update the matrix
    current_matrix[current_row] = current_row_value;
}
#        else
#            error DIODE_DIRECTION must be COL2ROW!
#        endif
#    endif // defined(MATRIX_ROW_PINS) && defined(MATRIX_COL_PINS)
#else
#    error DIODE_DIRECTION is not defined!
#endif

void matrix_init(void) {
#ifdef SPLIT_KEYBOARD
    // Set pinout for right half if pinout for that half is defined
    if (!isLeftHand) {
#    ifdef MATRIX_ROW_PINS_RIGHT
        const pin_t row_pins_right[ROWS_PER_HAND] = MATRIX_ROW_PINS_RIGHT;
        for (uint8_t i = 0; i < ROWS_PER_HAND; i++) {
            row_pins[i] = row_pins_right[i];
        }
#    endif
#    ifdef MATRIX_COL_PINS_RIGHT
        const pin_t col_pins_right[MATRIX_COLS] = MATRIX_COL_PINS_RIGHT;
        for (uint8_t i = 0; i < MATRIX_COLS; i++) {
            col_pins[i] = col_pins_right[i];
        }
#    endif
    }
    thisHand = isLeftHand ? 0 : (ROWS_PER_HAND);
    thatHand = ROWS_PER_HAND - thisHand;
#endif

    // initialize key pins
    matrix_init_pins();
    matrix_init_custom();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    // initialize matrix state: all keys off
    memset(matrix, 0, sizeof(matrix));
    memset(raw_matrix, 0, sizeof(raw_matrix));

    debounce_init(ROWS_PER_HAND);

    matrix_init_kb();
}

#ifdef SPLIT_KEYBOARD
// Fallback implementation for keyboards not using the standard split_util.c
__attribute__((weak)) bool transport_master_if_connected(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    transport_master(master_matrix, slave_matrix);
    return true; // Treat the transport as always connected
}
#endif

uint8_t matrix_scan(void) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};
    memcpy(curr_matrix, raw_matrix, sizeof(curr_matrix));

    // Set row, read cols
    for (uint8_t current_row = MATRIX_ROWS_MCP; current_row < ROWS_PER_HAND; current_row++) {
        matrix_read_cols_mcu(curr_matrix, current_row);
    }

    bool changed = memcmp(raw_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) memcpy(raw_matrix, curr_matrix, sizeof(curr_matrix));

    changed |= matrix_scan_custom(raw_matrix);

#ifdef SPLIT_KEYBOARD
    changed = debounce(raw_matrix, matrix + thisHand, ROWS_PER_HAND, changed) | matrix_post_scan();
#else
    changed = debounce(raw_matrix, matrix, ROWS_PER_HAND, changed);
    matrix_scan_kb();
#endif
    return (uint8_t)changed;
}
