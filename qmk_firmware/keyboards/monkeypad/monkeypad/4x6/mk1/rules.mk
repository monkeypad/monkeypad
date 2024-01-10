# Monkeypad build options
# Select module type
# Module type := analog_joystick / pmw3389 / encoder
# pmw3389 = trackball sensor
MODULE_DEVICE_LEFT = pmw3389
MODULE_DEVICE_RIGHT = analog_joystick

# If you are using different pointing devices (analog_joystick / pmw3389) on the left and right,
# you must select the target pointing device and compile twice, once for each side.
# If you use an encoder, the files will be the same for left and right.

# Please select the TARGET_POINTING_DEVICE. If both are encoders, this is ignored.
# Type (analog_joystick / pmw3389) ?
TARGET_POINTING_DEVICE = analog_joystick

# ***********************************************************************************
# QMK build options
#   change yes to no to disable
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB
RGB_MATRIX_ENABLE = no		# Disable keyboard RGB Matrix
AUDIO_ENABLE = no           # Audio output
AUDIO_SUPPORTED = no        # Audio is not supported
# Get key matrix on sub-board via I2C
CUSTOM_MATRIX = yes
SRC += matrix.c
QUANTUM_LIB_SRC += i2c_master.c

# RP2040-specific options
ALLOW_WARNINGS = yes
PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS.

ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes

# ***********************************************************************************
# Compiler options (The following do not need to be changed)
# This definition can not be moved to "post_rules.mk"
# Check whether the pointing device is on MODULE_DEVICE_LEFT or MODULE_DEVICE_RIGHT
POINTING_MODULE_NAME := analog_joystick pmw3389
ifneq (,$(filter $(POINTING_MODULE_NAME),$(MODULE_DEVICE_LEFT) $(MODULE_DEVICE_RIGHT)))
#	if it has at least one pointing device
	ifeq ($(strip $(TARGET_POINTING_DEVICE)), encoder)
		ifeq ($(or $(findstring pmw3389,$(MODULE_DEVICE_LEFT)), $(findstring pmw3389,$(MODULE_DEVICE_RIGHT))),pmw3389)
			TARGET_POINTING_DEVICE = pmw3389
		else ifeq ($(or $(findstring analog_joystick,$(MODULE_DEVICE_LEFT)), $(findstring analog_joystick,$(MODULE_DEVICE_RIGHT))),analog_joystick)
			TARGET_POINTING_DEVICE = analog_joystick
		endif
	endif

	OPT_DEFS += -DSPLIT_POINTING_ENABLE
	OPT_DEFS += -DUSE_DEVICE_$(strip $(TARGET_POINTING_DEVICE))
	POINTING_DEVICE_ENABLE = yes
#	Set pointing device driver on TARGET_POINTING_DEVICE
	ifeq ($(strip $(TARGET_POINTING_DEVICE)), pmw3389)
		POINTING_DEVICE_DRIVER = pmw3389
		MOUSE_SHARED_EP = no
	else ifeq ($(strip $(TARGET_POINTING_DEVICE)), analog_joystick)
#		Custom code modules/analog_joystick.c
		POINTING_DEVICE_DRIVER = custom
		OPT_DEFS += -DSTM32_ADC -DHAL_USE_ADC=TRUE
		SRC += modules/analog_joystick.c
		LIB_SRC += analog.c
	endif
else
#POINTING_MODULE_NAME is neither MODULE_DEVICE_LEFT nor MODULE_DEVICE_RIGHT
POINTING_DEVICE_ENABLE = no
endif
