ROOT             := $(abspath ../..)

include $(ROOT)/makefiles/root.mk
include $(ROOT)/makefiles/quiet.mk
include $(ROOT)/makefiles/board.mk
include $(ROOT)/makefiles/coap.mk
include $(ROOT)/makefiles/debug.mk
include $(ROOT)/makefiles/compiler.mk
include $(ROOT)/makefiles/help.mk

include $(ROOT)/variables.mk

ifeq ($(ROOT),)
    $(error ROOT has not been defined)
endif

BUILD_DIR        := build
BIN_DIR          := bin
TARGET           := $(BIN_DIR)/minimal
SOURCES          := $(wildcard *.c)
OBJECTS          := $(SOURCES:%.c=$(BUILD_DIR)/%.o)
DEPS             := $(SOURCES:%.c=$(BUILD_DIR)/%.d)
SCRIBE_LIB_SHORT := $(BOARD)/scribe.a
SCRIBE_LIB       := $(ROOT)/$(SCRIBE_LIB_SHORT)
CONFIGURE        := $(ROOT)/configure.sh
ALL_TARGETS      := $(TARGET)

ifeq ($(strip $(BOARD)), workstation)
    ALL_TARGETS  += run
endif

ifeq ($(strip $(MAKECMDGOALS)),)
    override MAKECMDGOALS := $(ALL_TARGETS)
endif

CFLAGS_TARGETS := $(TARGET) $(SCRIBE_LIB)
ifneq ($(filter $(CFLAGS_TARGETS), $(MAKECMDGOALS)),)
    ifeq ($(strip $(CFLAGS)),)
        $(warning CFLAGS has not been defined)
    endif
endif

include $(ROOT)/cflags.mk

PHONY_RULES := all clean realclean
ifeq ($(BOARD), workstation)
    PHONY_RULES += run
endif

all: $(ALL_TARGETS)

$(BUILD_DIR):
	$(QUIET_CHAR)mkdir -p $@

$(BIN_DIR):
	$(QUIET_CHAR)mkdir -p $@

include $(ROOT)/makefiles/build_params_tracker.mk

$(SCRIBE_LIB):
ifdef VERBOSE
	$(info For $(SCRIBE_LIB):)
	$(info - QUIET is '$(QUIET)')
	$(info - PREFIX is '$(PREFIX)')
	$(info - CC is '$(CC)')
	$(info - LOG is '$(LOG)')
	$(info - LOG_SEVERITY_LEVEL is '$(LOG_SEVERITY_LEVEL)')
	$(info - BOARD is '$(BOARD)')
	$(info - CFLAGS is '$(CFLAGS)')
	$(info - COAP is '$(COAP)')
endif
	$(QUIET_CHAR)$(MAKE) -C $(ROOT) \
                             $(SCRIBE_LIB_SHORT) \
                             QUIET="$(QUIET)" BOARD="$(BOARD)" \
                             PREFIX="$(PREFIX)" CC="$(CC)" \
                             DEBUG="$(DEBUG)" COAP="$(COAP)" \
                             LOG="$(LOG)" LOG_SEVERITY_LEVEL="$(LOG_SEVERITY_LEVEL)" \
                             CFLAGS="$(CFLAGS)"

$(BUILD_DIR)/%.o: %.c $(BUILD_PARAMS_TRACKER) | $(BUILD_DIR)
	$(QUIET_CHAR)$(CC) $(CFLAGS) -MD -MP -MF $(patsubst %.o,%.d, $@) -c $< -o $@

-include $(DEPS)


$(TARGET): $(OBJECTS) $(SCRIBE_LIB) | $(BIN_DIR)
	$(QUIET_CHAR)$(CC) $(OBJECTS) $(SCRIBE_LIB) -o $@

ifeq ($(BOARD), workstation)
run: $(TARGET)
	$(QUIET_CHAR)$(TARGET)
endif

clean:
	$(QUIET_CHAR)$(RM) -r $(BUILD_DIR)

realclean: clean
	$(QUIET_CHAR)$(RM) -r $(BIN_DIR)

help:
	$(call help_rule_line,help,Displays this text)
	$(call help_rule_line,$(TARGET),Builds executable into \"$(BUILD_DIR)\" directory)
	$(call help_rule_line,run,Executes \"$(TARGET)\" (when BOARD is equal to \"$(BOARD_WORKSTATION)\"))
	$(call help_rule_line,all,Performs \"$(ALL_TARGETS)\" targets)
	$(call help_rule_line,clean,Deletes \"$(BUILD_DIR)\" directory)
	$(call help_rule_line,realclean,Deletes \"$(BIN_DIR)\" directory and performs also \"clean\" target)
	$(call help_variables)

.PHONY: $(PHONY_RULES)
