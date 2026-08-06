ifeq ($(strip $(COAP_MK)),)
COAP_MK := COAP_MAKEFILE

ifdef COAP_NONE
    $(error COAP_NONE has already been defined outside of coap.mk)
endif
COAP_NONE :=

ifdef COAP_DISABLED
    $(error COAP_DISABLED has already been defined outside of coap.mk)
endif
COAP_DISABLED := 0

ifdef COAP_ENABLED
    $(error COAP_ENABLED has already been defined outside of coap.mk)
endif
COAP_ENABLED := 1

ifdef COAP_POSSIBLE_VALUES
    $(error COAP_POSSIBLE_VALUES has already been defined outside of board.mk)
endif
COAP_POSSIBLE_VALUES := \"$(COAP_DISABLED)\" \"$(COAP_ENABLED)\"

ifdef COAP_DEFAULT_VALUE
    $(error COAP_DEFAULT_VALUE has already been defined outside of board.mk)
endif
COAP_DEFAULT_VALUE := $(COAP_DISABLED)

ifndef COAP
    COAP := $(COAP_NONE)
endif

ifeq ($(strip $(COAP)),) # Empty COAP var
    override COAP := $(COAP_DEFAULT_VALUE)
    ifeq ($(QUIET_CHAR),)
        $(warning COAP has not been defined, fallback to "$(COAP)")
    endif
endif

ifneq ($(words $(COAP)), 1)
    $(error COAP variable must contain only one word ! Here COAP="$(COAP)")
endif

ifeq ($(filter \"$(COAP)\", $(COAP_POSSIBLE_VALUES)),)
    $(error COAP "$(COAP)" is not in supported coap values ($(COAP_POSSIBLE_VALUES)))
endif

ifneq ($(COAP), $(COAP_DISABLED))
    ifndef CFLAGS
        CFLAGS := -DSCRIBE_COAP_SINK_ENABLED
    else
       ifeq ($(filter "-DSCRIBE_COAP_SINK_ENABLED", $(CFLAGS)),)
           override CFLAGS += -DSCRIBE_COAP_SINK_ENABLED
       endif
    endif
endif

ifeq ($(QUIET_CHAR),)
    $(info COAP is "$(COAP)")
endif

endif # ($(strip $(COAP_MK),)
