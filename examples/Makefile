ROOT := $(abspath ..)

include $(ROOT)/variables.mk

ALL_TARGETS := build

ifeq ($(strip $(BOARD)), workstation)
ALL_TARGETS += run
endif

all: $(ALL_TARGETS)

build-minimal:
	$(QUIET_CHAR)$(MAKE) -C minimal bin/minimal QUIET="$(QUIET)" VERBOSE="$(VERBOSE)" \
                                                    BOARD="$(BOARD)" \
                                                    PREFIX="$(PREFIX)" CC="$(CC)" \
                                                    DEBUG="$(DEBUG)" COAP="$(COAP)" \
                                                    LOG="$(LOG)" \
                                                    LOG_SEVERITY_LEVEL="$(LOG_SEVERITY_LEVEL)" \
                                                    CFLAGS="$(CFLAGS)"

clean-minimal:
	$(QUIET_CHAR)$(MAKE) -C minimal clean QUIET="$(QUIET)" VERBOSE="$(VERBOSE)"

realclean-minimal:
	$(QUIET_CHAR)$(MAKE) -C minimal realclean QUIET="$(QUIET)" VERBOSE="$(VERBOSE)"

ifeq ($(strip $(BOARD)), workstation)
run-minimal:
	$(QUIET_CHAR)$(MAKE) -C minimal run QUIET="$(QUIET)" VERBOSE="$(VERBOSE)" \
                                            BOARD="$(BOARD)" \
                                            PREFIX="$(PREFIX)" CC="$(CC)" \
                                            DEBUG="$(DEBUG)" COAP="$(COAP)" \
                                            LOG="$(LOG)" \
                                            LOG_SEVERITY_LEVEL="$(LOG_SEVERITY_LEVEL)" \
                                            CFLAGS="$(CFLAGS)"
endif

build: build-minimal

ifeq ($(strip $(BOARD)), workstation)
run: run-minimal
endif

clean: clean-minimal

realclean: realclean-minimal

help:
	$(call help_rule_line,help,Displays this text)
	$(call help_rule_line,build,Builds all examples)
	$(call help_rule_line,run,Runs all examples (when BOARD is equal to \"$(BOARD_WORKSTATION)\"))
	$(call help_rule_line,all,Performs \"$(ALL_TARGETS)\" targets)
	$(call help_rule_line,clean,Cleans all examples)
	$(call help_rule_line,realclean,Cleans all artifacts in all examples)
	$(call help_rule_line,build-minimal,Builds \"minimal\" example)
	$(call help_rule_line,run-minimal,Runs \"minimal\" example (when BOARD is equal to \"$(BOARD_WORKSTATION)\")))
	$(call help_rule_line,clean-minimal,Cleans \"minimal\" example)
	$(call help_rule_line,realclean-minimal,Cleans all artifacts in \"minimal\" example)
	$(call help_variables)

.PHONY: all build clean realclean \
        build-minimal run-minimal clean-minimal realclean-minimal
