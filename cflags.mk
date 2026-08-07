ifeq ($(strip $(CFLAGS_MK)),)
CFLAGS_MK := CFLAGS_MAKEFILE

ifndef ROOT
    ROOT=
endif

ifeq ($(ROOT),)
    $(error ROOT variable has not been defined. Please fix this before including cflags.mk file)
endif

INCOMING_CFLAGS := $(CFLAGS)
override CFLAGS         += $(filter-out $(INCOMING_CFLAGS),-Wall)
override CFLAGS         += $(filter-out $(INCOMING_CFLAGS),-Wextra)
override CFLAGS         += $(filter-out $(INCOMING_CFLAGS),-Werror)
ifeq ($(BOARD), workstation)
override CFLAGS         += $(filter-out $(INCOMING_CFLAGS),-std=c11)
override CFLAGS         += $(filter-out $(INCOMING_CFLAGS),-Wno-unused-function)
else
override CFLAGS         += $(filter-out $(INCOMING_CFLAGS),-ffreestanding)
override CFLAGS         += $(filter-out $(INCOMING_CFLAGS),-mthumb)
endif
override CFLAGS         += $(filter-out $(INCOMING_CFLAGS),$(BOARD_CFLAGS))
override CFLAGS         += $(filter-out $(INCOMING_CFLAGS),-I$(abspath $(ROOT)))
override CFLAGS         += $(filter-out $(INCOMING_CFLAGS),-I$(abspath $(ROOT)/include))
ifndef RIOT_CFLAGS
override CFLAGS         += $(filter-out $(INCOMING_CFLAGS),-I$(abspath $(ROOT)/boards/$(BOARD)))
endif # RIOT_CFLAGS

ifdef RIOT_INCLUDES
override CFLAGS         += $(filter-out $(INCOMING_CFLAGS),$(RIOT_INCLUDES))
endif # RIOT_CFLAGS


endif # ($(strip $(CFLAGS_MK),)
