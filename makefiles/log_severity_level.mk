ifeq ($(strip $(LOG_SEVERITY_LEVEL_MK)),)
LOG_SEVERITY_LEVEL_MK := LOG_SEVERITY_LEVEL_MAKEFILE

ifdef LOG_SEVERITY_LEVEL_NONE
    $(error LOG_SEVERITY_LEVEL_NONE has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_NONE :=

ifdef LOG_SEVERITY_LEVEL_EMERGENCY
    $(error LOG_SEVERITY_LEVEL_EMERGENCY has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_EMERGENCY := SCRIBE_LOG_SEVERITY_LEVEL_EMERGENCY

ifdef LOG_SEVERITY_LEVEL_EMERG
    $(error LOG_SEVERITY_LEVEL_EMERG has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_EMERG := SCRIBE_LOG_SEVERITY_LEVEL_EMERG

ifdef LOG_SEVERITY_LEVEL_0
    $(error LOG_SEVERITY_LEVEL_0 has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_0 := 0

ifdef LOG_SEVERITY_LEVEL_EMERGENCY_POSSIBLE_VALUES
    $(error LOG_SEVERITY_LEVEL_EMERGENCY_POSSIBLE_VALUES has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_EMERGENCY_POSSIBLE_VALUES := \"$(LOG_SEVERITY_LEVEL_EMERGENCY)\" \"$(LOG_SEVERITY_LEVEL_EMERG)\" \"$(LOG_SEVERITY_LEVEL_0)\"


ifdef LOG_SEVERITY_LEVEL_ALERT
    $(error LOG_SEVERITY_LEVEL_ALERT has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_ALERT := SCRIBE_LOG_SEVERITY_LEVEL_ALERT

ifdef LOG_SEVERITY_LEVEL_1
    $(error LOG_SEVERITY_LEVEL_1 has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_1 := 1

ifdef LOG_SEVERITY_LEVEL_ALERT_POSSIBLE_VALUES
    $(error LOG_SEVERITY_LEVEL_ALERT_POSSIBLE_VALUES has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_ALERT_POSSIBLE_VALUES := \"$(LOG_SEVERITY_LEVEL_ALERT)\" \"$(LOG_SEVERITY_LEVEL_1)\"


ifdef LOG_SEVERITY_LEVEL_CRITICAL
    $(error LOG_SEVERITY_LEVEL_CRITICAL has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_CRITICAL := SCRIBE_LOG_SEVERITY_LEVEL_CRITICAL

ifdef LOG_SEVERITY_LEVEL_CRIT
    $(error LOG_SEVERITY_LEVEL_CRIT has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_CRIT := SCRIBE_LOG_SEVERITY_LEVEL_CRIT

ifdef LOG_SEVERITY_LEVEL_2
    $(error LOG_SEVERITY_LEVEL_2 has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_2 := 2

ifdef LOG_SEVERITY_LEVEL_CRITICAL_POSSIBLE_VALUES
    $(error LOG_SEVERITY_LEVEL_CRITICAL_POSSIBLE_VALUES has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_CRITICAL_POSSIBLE_VALUES := \"$(LOG_SEVERITY_LEVEL_CRITICAL)\" \"$(LOG_SEVERITY_LEVEL_CRIT)\" \"$(LOG_SEVERITY_LEVEL_2)\"


ifdef LOG_SEVERITY_LEVEL_ERROR
    $(error LOG_SEVERITY_LEVEL_ERROR has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_ERROR := SCRIBE_LOG_SEVERITY_LEVEL_ERROR

ifdef LOG_SEVERITY_LEVEL_ERR
    $(error LOG_SEVERITY_LEVEL_ERR has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_ERR := SCRIBE_LOG_SEVERITY_LEVEL_ERR

ifdef LOG_SEVERITY_LEVEL_3
    $(error LOG_SEVERITY_LEVEL_3 has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_3 := 3

ifdef LOG_SEVERITY_LEVEL_ERROR_POSSIBLE_VALUES
    $(error LOG_SEVERITY_LEVEL_ERROR_POSSIBLE_VALUES has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_ERROR_POSSIBLE_VALUES := \"$(LOG_SEVERITY_LEVEL_ERROR)\" \"$(LOG_SEVERITY_LEVEL_ERR)\" \"$(LOG_SEVERITY_LEVEL_3)\"


ifdef LOG_SEVERITY_LEVEL_WARNING
    $(error LOG_SEVERITY_LEVEL_WARNING has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_WARNING := SCRIBE_LOG_SEVERITY_LEVEL_WARNING

ifdef LOG_SEVERITY_LEVEL_WARN
    $(error LOG_SEVERITY_LEVEL_WARN has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_WARN := SCRIBE_LOG_SEVERITY_LEVEL_WARN

ifdef LOG_SEVERITY_LEVEL_4
    $(error LOG_SEVERITY_LEVEL_4 has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_4 := 4

ifdef LOG_SEVERITY_LEVEL_WARNING_POSSIBLE_VALUES
    $(error LOG_SEVERITY_LEVEL_WARNING_POSSIBLE_VALUES has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_WARNING_POSSIBLE_VALUES := \"$(LOG_SEVERITY_LEVEL_WARNING)\" \"$(LOG_SEVERITY_LEVEL_WARN)\" \"$(LOG_SEVERITY_LEVEL_4)\"


ifdef LOG_SEVERITY_LEVEL_NOTICE
    $(error LOG_SEVERITY_LEVEL_NOTICE has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_NOTICE := SCRIBE_LOG_SEVERITY_LEVEL_NOTICE

ifdef LOG_SEVERITY_LEVEL_5
    $(error LOG_SEVERITY_LEVEL_5 has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_5 := 5

ifdef LOG_SEVERITY_LEVEL_NOTICE_POSSIBLE_VALUES
    $(error LOG_SEVERITY_LEVEL_NOTICE_POSSIBLE_VALUES has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_NOTICE_POSSIBLE_VALUES := \"$(LOG_SEVERITY_LEVEL_NOTICE)\" \"$(LOG_SEVERITY_LEVEL_5)\"


ifdef LOG_SEVERITY_LEVEL_INFORMATION
    $(error LOG_SEVERITY_LEVEL_INFORMATION has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_INFORMATION := SCRIBE_LOG_SEVERITY_LEVEL_INFORMATION

ifdef LOG_SEVERITY_LEVEL_INFO
    $(error LOG_SEVERITY_LEVEL_INFO has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_INFO := SCRIBE_LOG_SEVERITY_LEVEL_INFO

ifdef LOG_SEVERITY_LEVEL_6
    $(error LOG_SEVERITY_LEVEL_6 has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_6 := 6

ifdef LOG_SEVERITY_LEVEL_INFORMATION_POSSIBLE_VALUES
    $(error LOG_SEVERITY_LEVEL_INFORMATION_POSSIBLE_VALUES has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_INFORMATION_POSSIBLE_VALUES := \"$(LOG_SEVERITY_LEVEL_INFORMATION)\" \"$(LOG_SEVERITY_LEVEL_INFO)\" \"$(LOG_SEVERITY_LEVEL_6)\"


ifneq ($(DEBUG),0)

    ifdef LOG_SEVERITY_LEVEL_DEBUG
        $(error LOG_SEVERITY_LEVEL_DEBUG has already been defined outside of log_severity_level.mk)
    endif
    LOG_SEVERITY_LEVEL_DEBUG := SCRIBE_LOG_SEVERITY_LEVEL_DEBUG

    ifdef LOG_SEVERITY_LEVEL_7
        $(error LOG_SEVERITY_LEVEL_7 has already been defined outside of log_severity_level.mk)
    endif
    LOG_SEVERITY_LEVEL_7 := 7

    ifdef LOG_SEVERITY_LEVEL_DEBUG_POSSIBLE_VALUES
        $(error LOG_SEVERITY_LEVEL_DEBUG_POSSIBLE_VALUES has already been defined outside of log_severity_level.mk)
    endif
    LOG_SEVERITY_LEVEL_DEBUG_POSSIBLE_VALUES := \"$(LOG_SEVERITY_LEVEL_DEBUG)\" \"$(LOG_SEVERITY_LEVEL_7)\"

endif # ($(DEBUG),0))


ifdef LOG_SEVERITY_LEVELS_POSSIBLE_VALUES
    $(error LOG_SEVERITY_LEVELS_POSSIBLE_VALUES has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVELS_POSSIBLE_VALUES := $(LOG_SEVERITY_LEVEL_EMERGENCY_POSSIBLE_VALUES) $(LOG_SEVERITY_LEVEL_ALERT_POSSIBLE_VALUES) $(LOG_SEVERITY_LEVEL_CRITICAL_POSSIBLE_VALUES) $(LOG_SEVERITY_LEVEL_ERROR_POSSIBLE_VALUES) $(LOG_SEVERITY_LEVEL_WARNING_POSSIBLE_VALUES) $(LOG_SEVERITY_LEVEL_NOTICE_POSSIBLE_VALUES) $(LOG_SEVERITY_LEVEL_INFORMATION_POSSIBLE_VALUES) $(LOG_SEVERITY_LEVEL_DEBUG_POSSIBLE_VALUES)


ifdef LOG_SEVERITY_LEVEL_DEFAULT_VALUE
    $(error LOG_SEVERITY_LEVEL_DEFAULT_VALUE has already been defined outside of log_severity_level.mk)
endif
LOG_SEVERITY_LEVEL_DEFAULT_VALUE := $(LOG_SEVERITY_LEVEL_WARNING)


ifeq ($(strip $(LOG_SEVERITY_LEVEL)),$(LOG_SEVERITY_LEVEL_NONE))

    ifeq ($(strip $(DEBUG)),1)

        ifeq ($(strip $(LOG_SEVERITY_LEVEL)),)
            LOG_SEVERITY_LEVEL := $(LOG_SEVERITY_LEVEL_DEBUG)
            ifeq ($(QUIET_CHAR),)
                $(warning LOG_SEVERITY_LEVEL automatically defined due to DEBUG)
            endif
        else # ($(strip $(LOG_SEVERITY_LEVEL)),)
            LOG_SEVERITY_LEVEL_IS_SET_TO_DEBUG := $(filter $(LOG_SEVERITY_LEVEL_DEBUG_POSSIBLE_VALUES),$(LOG_SEVERITY_LEVEL))
            ifneq ($(strip $(LOG_SEVERITY_LEVEL_IS_SET_TO_DEBUG)),)
                $(error LOG_SEVERITY_LEVEL (\"$(LOG_SEVERITY_LEVEL)\") is not set to {$(LOG_SEVERITY_LEVEL_DEBUG_POSSIBLE_VALUES)} and DEBUG is enabled)
            endif # ($(strip $(LOG_SEVERITY_LEVEL_IS_SET_TO_DEBUG)),))
        endif # ($(strip $(LOG_SEVERITY_LEVEL)),)

    endif # ($(strip $(DEBUG)),1)

endif # ($(strip $(LOG_SEVERITY_LEVEL)),$(LOG_SEVERITY_LEVEL_NONE))

ifeq ($(strip $(LOG_SEVERITY_LEVEL)),)
    override LOG_SEVERITY_LEVEL := $(LOG_SEVERITY_LEVEL_DEFAULT_VALUE)
    ifeq ($(QUIET_CHAR),)
        $(warning LOG_SEVERITY_LEVEL has not been defined, fallback to "$(LOG_SEVERITY_LEVEL)")
    endif
endif

ifneq ($(words $(LOG_SEVERITY_LEVEL)),1)
    $(error LOG_SEVERITY_LEVEL variable must contain only one word ! Here LOG_SEVERITY_LEVEL="$(LOG_SEVERITY_LEVEL)")
endif

ifeq ($(filter \"$(LOG_SEVERITY_LEVEL)\", $(LOG_SEVERITY_LEVELS_POSSIBLE_VALUES)),)
    $(error LOG_SEVERITY_LEVEL "$(LOG_SEVERITY_LEVEL)" is not in supported log severity levels ($(LOG_SEVERITY_LEVELS_POSSIBLE_VALUES)))
endif


ifeq ($(QUIET_CHAR),)
    $(info LOG_SEVERITY_LEVEL is "$(LOG_SEVERITY_LEVEL)")
endif

ifneq ($(LOG_SEVERITY_LEVEL),$(LOG_SEVERITY_LEVEL_NONE))
    ifndef CFLAGS
        CFLAGS := "-DSCRIBE_LOG_SEVERITY_LEVEL_DEFAULT=$(LOG_SEVERITY_LEVEL)"
    else
       ifeq ($(filter "-DSCRIBE_LOG_SEVERITY_LEVEL_DEFAULT=$(LOG_SEVERITY_LEVEL)", $(CFLAGS)),)
           override CFLAGS += "-DSCRIBE_LOG_SEVERITY_LEVEL_DEFAULT=$(LOG_SEVERITY_LEVEL)"
       endif
    endif
endif

endif # ($(strip $(LOG_SEVERITY_LEVEL_MK),)
