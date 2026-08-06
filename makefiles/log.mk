ifeq ($(strip $(LOG_MK)),)
LOG_MK := LOG_MAKEFILE

ifdef LOG_NONE
    $(error LOG_NONE has already been defined outside of log.mk)
endif
LOG_NONE :=

ifdef LOG_DISABLED
    $(error LOG_DISABLED has already been defined outside of log.mk)
endif
LOG_DISABLED := 0

ifdef LOG_ENABLED
    $(error LOG_ENABLED has already been defined outside of log.mk)
endif
LOG_ENABLED := 1

ifdef LOG_POSSIBLE_VALUES
    $(error LOG_POSSIBLE_VALUES has already been defined outside of log.mk)
endif
LOG_POSSIBLE_VALUES := \"$(LOG_DISABLED)\" \"$(LOG_ENABLED)\"

ifdef LOG_DEFAULT_VALUE
    $(error LOG_DEFAULT_VALUE has already been defined outside of log.mk)
endif
LOG_DEFAULT_VALUE := $(LOG_DISABLED)

ifndef LOG
    $LOG := $(LOG_NONE)
endif

ifeq ($(strip $(LOG)),)
    override LOG := $(LOG_DEFAULT_VALUE)
    ifeq ($(QUIET_CHAR),)
        $(warning LOG has not been defined, fallback to "$(LOG)")
    endif
endif

ifneq ($(words $(LOG)), 1)
    $(error LOG variable must contain only one word ! Here LOG="$(LOG)")
endif

ifeq ($(filter \"$(LOG)\", $(LOG_POSSIBLE_VALUES)),)
    $(error LOG "$(LOG)" is not in supported logs ($(LOG_POSSIBLE_VALUES)))
endif

ifeq ($(QUIET_CHAR),)
    $(info LOG is "$(LOG)")
endif

ifneq ($(LOG), $(LOG_DISABLED))
    ifndef CFLAGS
        CFLAGS := -DSCRIBE_LOG_ENABLED
    else
       ifeq ($(filter "-DSCRIBE_LOG_ENABLED", $(CFLAGS)),)
           override CFLAGS += -DSCRIBE_LOG_ENABLED
       endif
    endif
endif

endif # ($(strip $(LOG_MK),)
