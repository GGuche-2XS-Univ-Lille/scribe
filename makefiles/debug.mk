ifeq ($(strip $(DEBUG_MK)),)
DEBUG_MK := DEBUG_MAKEFILE

ifdef DEBUG_NONE
    $(error DEBUG_NONE has already been defined outside of debug.mk)
endif
DEBUG_NONE :=

ifdef DEBUG_DISABLED
    $(error DEBUG_DISABLED has already been defined outside of debug.mk)
endif
DEBUG_DISABLED := 0

ifdef DEBUG_ENABLED
    $(error DEBUG_ENABLED has already been defined outside of debug.mk)
endif
DEBUG_ENABLED := 1

ifdef DEBUG_DEFAULT_VALUE
    $(error DEBUG_DEFAULT_VALUE has already been defined outside of debug.mk)
endif
DEBUG_DEFAULT_VALUE := $(DEBUG_DISABLED)

ifdef DEBUG_POSSIBLE_VALUES
    $(error DEBUG_POSSIBLE_VALUES has already been defined outside of debug.mk)
endif
DEBUG_POSSIBLE_VALUES := \"$(DEBUG_DISABLED)\" \"$(DEBUG_ENABLED)\"

ifndef DEBUG
    $DEBUG := $(DEBUG_NONE)
endif

ifeq ($(strip $(DEBUG)),) # Empty DEBUG var
   override DEBUG := $(DEBUG_DEFAULT_VALUE)
endif

ifneq ($(words $(DEBUG)), 1)
    $(error DEBUG variable must contain only one word ! Here DEBUG="$(DEBUG)")
endif

ifeq ($(filter \"$(DEBUG)\", $(DEBUG_POSSIBLE_VALUES)),)
    $(error DEBUG "$(DEBUG)" is not in supported debug values ($(DEBUG_POSSIBLE_VALUES)))
endif


ifeq ($(QUIET_CHAR),)
    $(info DEBUG is "$(DEBUG)")
endif

ifeq ($(DEBUG),$(DEBUG_DISABLED))

    ifdef RELEASE_CFLAGS
        ifdef VERBOSE
            $(info RELEASE_CFLAGS has already been defined ("$(RELEASE_CFLAGS)"))
        endif
    else
        RELEASE_CFLAGS := -Os -DNDEBUG
        ifeq ($(strip $(QUIET_CHAR)),)
            $(warning RELEASE_CFLAGS has not been defined, fallback to "$(RELEASE_CFLAGS)")
        endif
    endif

    ifndef CFLAGS
        CFLAGS := $(RELEASE_CFLAGS)
    else
       INCOMING_CFLAGS := $(CFLAGS)
       override CFLAGS += $(filter-out $(INCOMING_CFLAGS),$(RELEASE_CFLAGS))
    endif

else #($(DEBUG), $(DEBUG_DISABLED))

    ifdef DEBUG_CFLAGS
        ifdef VERBOSE
            $(info DEBUG_CFLAGS has already been defined ("$(DEBUG_CFLAGS)"))
        endif
    else
       DEBUG_CFLAGS := -Og -ggdb
       ifeq ($(strip $(QUIET_CHAR)),)
           $(warning DEBUG_CFLAGS has not been defined, fallback to "$(DEBUG_CFLAGS)")
       endif
    endif

    ifndef CFLAGS
        CFLAGS := $(DEBUG_CFLAGS)
    else
       INCOMING_CFLAGS := $(CFLAGS)
       override CFLAGS += $(filter-out $(INCOMING_CFLAGS),$(DEBUG_CFLAGS))
    endif

endif # #($(DEBUG), $(DEBUG_DISABLED))

endif # ($(strip $(DEBUG_MK),)
