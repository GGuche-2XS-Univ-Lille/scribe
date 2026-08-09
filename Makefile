ROOT := $(abspath .)

include $(ROOT)/variables.mk

ifndef RIOT_CFLAGS

ifeq ("$(wildcard toolchain.mk)","")
    ifeq ($(BOARD),)
        $(error "Run ./configure.sh first")
    else
        $(shell ./configure.sh --board=$(BOARD))
        ifeq ("$(wildcard toolchain.mk)","")
            $(error "Failed to configure toolchain with BOARD='$(BOARD)'")
        endif
    endif
endif

include toolchain.mk
include boards/$(BOARD)/toolchain.mk
endif # RIOT_CFLAGS

include $(ROOT)/cflags.mk

AR      := $(PREFIX)ar
TARGET  := scribe
SOURCES := $(wildcard src/*.c)
OBJECTS := $(SOURCES:.c=.o)
OBJS    := $(addprefix $(BOARD)/,$(OBJECTS))
DEPS    := $(OBJS:%.o=%.d)

RELATIVE_HEADERS_AND_SOURCES := $(SOURCES) $(HEADERS)
HEADERS_AND_SOURCES := $(foreach f,$(RELATIVE_HEADERS_AND_SOURCES),$(abspath $(f)))

ALL_TARGETS := $(BOARD)/$(TARGET).a build-examples
ifeq ($(strip $(BOARD)), workstation)
ALL_TARGETS += run-examples
endif

all: $(ALL_TARGETS)

$(BOARD)/src:
	$(QUIET_CHAR)mkdir -p $(BOARD)/src

$(BOARD)/src/%.c: src/%.c | $(BOARD)/src
	$(QUIET_CHAR)cmp -s $< $@ || cp $< $@

.PRECIOUS: $(BOARD)/src/%.c

ifdef BUILD_DIR_PATH
    $(error BUILD_DIR_PATH has already been defined as '$(BUILD_DIR_PATH)')
endif
BUILD_DIR_PATH := $(BOARD)/src
include makefiles/build_params_tracker.mk

$(BOARD)/$(TARGET).a: $(OBJS)
	$(QUIET_CHAR)$(AR) rcs $@ $^

build-library: $(BOARD)/$(TARGET).a

$(BOARD)/src/%.o: $(BOARD)/src/%.c $(BUILD_PARAMS_TRACKER)
	$(QUIET_CHAR)$(CC) $(CFLAGS) -MD -MP -MF $(patsubst %.o,%.d, $@) -c $< -o $@

-include $(DEPS)

build-examples: $(BOARD)/$(TARGET).a
	$(QUIET_CHAR)$(MAKE) -C examples build QUIET="$(QUIET)" VERBOSE="$(VERBOSE)" \
                                               BOARD="$(BOARD)" DEBUG="$(DEBUG)" \
                                               PREFIX="$(PREFIX)" CC="$(CC)" CFLAGS="$(CFLAGS)" \
                                               LOG="$(LOG)" \
                                               LOG_SEVERITY_LEVEL="$(LOG_SEVERITY_LEVEL)" \
                                               COAP="$(COAP)"
ifeq ($(strip $(BOARD)), workstation)
run-examples: build-examples
	$(QUIET_CHAR)$(MAKE) -C examples run QUIET="$(QUIET)" VERBOSE="$(VERBOSE)" \
                                             BOARD="$(BOARD)" DEBUG="$(DEBUG)" \
                                             PREFIX="$(PREFIX)" CC="$(CC)" CFLAGS="$(CFLAGS)" \
                                             LOG="$(LOG)" \
                                             LOG_SEVERITY_LEVEL="$(LOG_SEVERITY_LEVEL)" \
                                             COAP="$(COAP)"
endif # ($(strip $(BOARD)), workstation)

clean-examples:
	$(QUIET_CHAR)$(MAKE) -C examples clean QUIET="$(QUIET)" VERBOSE="$(VERBOSE)"

realclean-examples:
	$(QUIET_CHAR)$(MAKE) -C examples realclean QUIET="$(QUIET)" VERBOSE="$(VERBOSE)"

clean-objects:
	$(QUIET_CHAR)$(RM) -f $(OBJS)

clean-library:
	$(QUIET_CHAR)$(RM) -f $(BOARD)/$(TARGET).a

clean: clean-objects clean-examples

realclean: realclean-examples
	$(QUIET_CHAR)$(RM) -rf workstation
	$(QUIET_CHAR)$(RM) -f toolchain.mk

help:
	$(call help_rule_line,help,Displays this text)
	$(call help_rule_line,build-library,Builds $(TARGET) static library according to the selected BOARD)
	$(call help_rule_line,build-examples,Builds all examples)
	$(call help_rule_line,run-examples,Runs all examples (when BOARD is equal to \"$(BOARD_WORKSTATION)\"))
	$(call help_rule_line,clean-examples,Cleans all examples)
	$(call help_rule_line,realclean-examples,Cleans all artifacts in all examples)
	$(call help_rule_line,all,Performs \"$(ALL_TARGETS)\" targets)
	$(call help_rule_line,clean,Cleans objects and all examples)
	$(call help_rule_line,realclean,Cleans all artifacts)
	$(call help_variables)

.PHONY: all build-library clean-objects clean-library clean realclean \
        clean-examples realclean-examples run-examples
