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

ifeq ($(DEBUG), $(DEBUG_DISABLED))

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


    ifndef LOG

       ifeq ($(strip $(QUIET_CHAR)),)
           $(warning LOG automatically enabled due to DEBUG)
           LOG := $(LOG_ENABLED)
       endif

    else # LOG

       ifeq ($(strip $(LOG)),0)
           $(error LOG has been disabled but DEBUG needs to enable it)
       endif

    endif # LOG


    ifndef LOG_SEVERITY_LEVEL

       ifeq ($(strip $(QUIET_CHAR)),)
           LOG_SEVERITY_LEVEL := SCRIBE_LOG_SEVERITY_LEVEL_DEBUG
           $(warning LOG_SEVERITY_LEVEL automatically set to "$(LOG_SEVERITY_LEVEL)" due to DEBUG)
       endif

    else # LOG_SEVERITY_LEVEL

       ifdef DEBUG_REQUIRED_LOG_SEVERITY_LEVELS
           $(error DEBUG_REQUIRED_LOG_SEVERITY_LEVELS has already been defined outside of debug.mk)
       endif
       DEBUG_REQUIRED_LOG_SEVERITY_LEVELS := SCRIBE_LOG_SEVERITY_LEVEL_DEBUG 7

       ifeq ($(filter $(DEBUG_REQUIRED_LOG_SEVERITY_LEVELS),$(LOG_SEVERITY_LEVEL)),)
           $(error LOG_SEVERITY_LEVEL ("$(LOG_SEVERITY_LEVEL)") has been set but DEBUG requires "$(DEBUG_REQUIRED_LOG_SEVERITY_LEVELS)" )
       endif

    endif # LOG_SEVERITY_LEVEL

endif # #($(DEBUG), $(DEBUG_DISABLED))

endif # ($(strip $(DEBUG_MK),)
