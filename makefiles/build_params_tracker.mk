ifeq ($(strip $(BUILD_PARAMS_TRACKER_MK)),)
BUILD_PARAMS_TRACKER_MK := BUILD_PARAMS_TRACKER_MAKEFILE

ifdef BUILD_DIR_PATH_NONE
    $(error BUILD_DIR_PATH_NONE has already been defined outside of build_params_tracker.mk)
endif
BUILD_DIR_PATH_DEFAULT_VALUE :=

ifdef BUILD_DIR_PATH_DEFAULT_VALUE
    $(error BUILD_DIR_PATH_DEFAULT_VALUE has already been defined outside of build_params_tracker.mk)
endif
BUILD_DIR_PATH_DEFAULT_VALUE := build

ifndef BUILD_DIR_PATH
    BUILD_DIR_PATH := $(BUILD_DIR_PATH_NONE)
endif

ifeq ($(strip $(BUILD_DIR_PATH)),)
    override BUILD_DIR_PATH := $(BUILD_DIR_PATH_DEFAULT_VALUE)
    ifeq ($(strip $(QUIET_CHAR)),)
        $(warning BUILD_DIR_PATH has not been defined, fallback to "$(BUILD_DIR_PATH)")
    endif
endif

ifdef BUILD_PARAMS_TRACKER
    $(error BUILD_PARAMS_TRACKER is already defined as "$(BUILD_PARAMS_TRACKER)")
endif
BUILD_PARAMS_TRACKER := $(BUILD_DIR_PATH)/params_tracker

$(BUILD_PARAMS_TRACKER): FORCE | $(BUILD_DIR_PATH)
	@echo "BOARD=\"$(BOARD)\" DEBUG=\"$(DEBUG)\" \
               LOG="$(LOG)" LOG_SEVERITY_LEVEL="$(LOG_SEVERITY_LEVEL)" \
               PREFIX=\"$(PREFIX)\" CC=\"$(CC)\" CFLAGS=\"$(CFLAGS)\"" | \
         cmp -s - $@ || \
         echo "BOARD=\"$(BOARD)\" DEBUG=\"$(DEBUG)\" \
               LOG="$(LOG)" LOG_SEVERITY_LEVEL="$(LOG_SEVERITY_LEVEL)" \
               PREFIX=\"$(PREFIX)\" CC=\"$(CC)\" CFLAGS=\"$(CFLAGS)\"" > $@

FORCE:

endif # ($(strip $(BUILD_PARAMS_TRACKER_MK),)
