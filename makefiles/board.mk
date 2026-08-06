ifeq ($(strip $(BOARD_MK)),)
BOARD_MK := BOARD_MAKEFILE

ifdef BOARD_NONE
    $(error BOARD_NONE has already been defined outside of board.mk)
endif
BOARD_NONE :=

ifdef BOARD_WORKSTATION
    $(error BOARD_WORKSTATION has already been defined outside of board.mk)
endif
BOARD_WORKSTATION := workstation

ifdef BOARD_DWM1001
    $(error BOARD_DWM1001 has already been defined outside of board.mk)
endif
BOARD_DWM1001 := dwm1001

ifdef BOARD_POSSIBLE_VALUES
    $(error BOARD_POSSIBLE_VALUES has already been defined outside of board.mk)
endif
BOARD_POSSIBLE_VALUES := \"$(BOARD_WORKSTATION)\" \"$(BOARD_DWM1001)\"

ifdef BOARD_DEFAULT_VALUE
    $(error BOARD_DEFAULT_VALUE has already been defined outside of board.mk)
endif
BOARD_DEFAULT_VALUE := $(BOARD_WORKSTATION)

ifeq ($(strip $(BOARD)),)
    override BOARD := $(BOARD_DEFAULT_VALUE)
    ifeq ($(QUIET_CHAR),)
        $(warning BOARD has not been defined, fallback to "$(BOARD)")
    endif
endif

ifneq ($(words $(BOARD)), 1)
    $(error BOARD variable must contain only one word ! Here BOARD=$(BOARD))
endif

ifeq ($(filter \"$(BOARD)\", $(BOARD_POSSIBLE_VALUES)),)
    $(error BOARD "$(BOARD)" is not in supported boards ($(BOARD_POSSIBLE_VALUES)))
endif

ifeq ($(QUIET_CHAR),)
    $(info BOARD is "$(BOARD)")
endif

endif # ($(strip $(BOARD_MK),)
