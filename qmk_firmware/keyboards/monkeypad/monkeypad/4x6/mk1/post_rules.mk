# Compiler options (The following do not need to be changed)
# Check whether the validated module is on MODULE_DEVICE_LEFT or MODULE_DEVICE_RIGHT
VALID_MONKEYPAD_MODULE_TYPES := encoder $(POINTING_MODULE_NAME)
ifeq (,$(filter $(MODULE_DEVICE_LEFT) $(MODULE_DEVICE_RIGHT),$(VALID_MONKEYPAD_MODULE_TYPES)))
	$(call CATASTROPHIC_ERROR,Invalid Monkeypad Device type,MONKEYPAD_DEVICE_TYPE="$(MODULE_DEVICE_LEFT)" or "$(MODULE_DEVICE_RIGHT)" is not a valid device)
else
#	Check if encoder is present on either MODULE_DEVICE_LEFT or MODULE_DEVICE_RIGHT
	ifeq ($(or $(findstring encoder,$(MODULE_DEVICE_LEFT)), $(findstring encoder,$(MODULE_DEVICE_RIGHT))),encoder)
		ENCODER_ENABLE = yes
	else
# 		ENCODER_ENABLE = no
	endif
	OPT_DEFS += -DMODULE_DEVICE_LEFT_$(strip $(MODULE_DEVICE_LEFT))
	OPT_DEFS += -DMODULE_DEVICE_RIGHT_$(strip $(MODULE_DEVICE_RIGHT))

#	Check whether the pointing device is on MODULE_DEVICE_LEFT or MODULE_DEVICE_RIGHT
	ifneq (,$(filter $(POINTING_MODULE_NAME),$(MODULE_DEVICE_LEFT) $(MODULE_DEVICE_RIGHT)))
#		if it has at least one pointing device
		ifneq (,$(filter $(POINTING_MODULE_NAME),$(MODULE_DEVICE_LEFT)))
			ifneq (,$(filter $(POINTING_MODULE_NAME),$(MODULE_DEVICE_RIGHT)))
#			POINTING_MODULE_NAME are both MODULE_DEVICE_LEFT and MODULE_DEVICE_RIGHT
			OPT_DEFS += -DPOINTING_DEVICE_COMBINED
			else
#			POINTING_MODULE_NAME is MODULE_DEVICE_LEFT
			OPT_DEFS += -DPOINTING_DEVICE_LEFT
			endif
		else ifneq (,$(filter $(POINTING_MODULE_NAME),$(MODULE_DEVICE_RIGHT)))
#			POINTING_MODULE_NAME is MODULE_DEVICE_RIGHT
			OPT_DEFS += -DPOINTING_DEVICE_RIGHT
		endif
	endif
endif

# If MIDI_ENABLE is 'yes', set the following parameters to 'no'
ifeq ($(strip $(MIDI_ENABLE)), yes)
CONSOLE_ENABLE = no
NKRO_ENABLE = no
EXTRAKEY_ENABLE = no
MOUSEKEY_ENABLE = no
endif
