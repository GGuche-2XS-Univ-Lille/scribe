ifeq ($(strip $(CFLAGS_MK)),)
CFLAGS_MK := CFLAGS_MAKEFILE

ifndef ROOT
    ROOT=
endif

ifeq ($(ROOT),)
    $(error ROOT variable has not been defined. Please fix this before including cflags.mk file)
endif

override CFLAGS         += -Wall
override CFLAGS         += -Wextra
override CFLAGS         += -Werror
ifeq ($(BOARD), workstation)
override CFLAGS         += -std=c11
override CFLAGS         += -Wno-unused-function
else
override CFLAGS         += -ffreestanding
override CFLAGS         += -mthumb
endif
override CFLAGS         += $(BOARD_CFLAGS)
override CFLAGS         += -I$(abspath $(ROOT))
override CFLAGS         += -I$(abspath $(ROOT)/include)
ifdef RIOT_CFLAGS
override CFLAGS         += $(RIOT_INCLUDES)
override CFLAGS         += $(RIOT_CFLAGS)
else # RIOT_CFLAGS
override CFLAGS         += -I$(abspath $(ROOT)/boards/$(BOARD))
endif # RIOT_CFLAGS


# $(sort ...) also removes duplicates.
override CFLAGS := $(sort $(CFLAGS))

endif # ($(strip $(CFLAGS_MK),)
