ifeq ($(strip $(QUIET_MK)),)
QUIET_MK := QUIET_MAKEFILE

ifdef QUIET_NONE
    $(error QUIET_NONE has already been defined outside of quiet.mk)
endif
QUIET_NONE :=

ifdef QUIET_DISABLED
    $(error QUIET_DISABLED has already been defined outside of quiet.mk)
endif
QUIET_DISABLED := 0

ifdef QUIET_ENABLED
    $(error QUIET_ENABLED has already been defined outside of quiet.mk)
endif
QUIET_ENABLED := 1

ifdef QUIET_POSSIBLE_VALUES
    $(error QUIET_POSSIBLE_VALUES has already been defined outside of quiet.mk)
endif
QUIET_POSSIBLE_VALUES := \"$(QUIET_DISABLED)\" \"$(QUIET_ENABLED)\"

ifdef QUIET_DEFAULT_VALUE
    $(error QUIET_DEFAULT_VALUE has already been defined outside of quiet.mk)
endif
QUIET_DEFAULT_VALUE := $(QUIET_ENABLED)

ifndef QUIET
    QUIET := $(QUIET_NONE)
endif

ifeq ($(strip $(QUIET)),)
    override QUIET := $(QUIET_DEFAULT_VALUE)
endif

ifneq ($(words $(QUIET)), 1)
    $(error QUIET variable must contain only one word ! Here QUIET="$(QUIET)")
endif

ifeq ($(filter \"$(QUIET)\", $(QUIET_POSSIBLE_VALUES)),)
    $(error QUIET "$(QUIET)" is not in supported values ($(QUIET_POSSIBLE_VALUES)))
endif

ifeq ($(strip $(QUIET)), $(QUIET_DISABLED))
    override QUIET_CHAR :=
else
    QUIET_CHAR := @
    MAKE_SILENT_FLAGS= -s --silent --quiet
    ifeq ($(filter $(MAKE_SILENT_FLAGS), $(MAKEFLAGS)),)
        override MAKEFLAGS += --silent
    endif
endif

ifeq ($(QUIET_CHAR),)
    $(info QUIET is "$(QUIET)")
endif

endif # ($(strip $(QUIET_MK),)
