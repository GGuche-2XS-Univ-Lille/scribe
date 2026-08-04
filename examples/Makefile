ROOT := $(abspath ..)
include $(ROOT)/quiet.mk

all: build run

build-minimal:
	$(QUIET_CHAR)$(MAKE) -C minimal bin/minimal QUIET="$(QUIET)" \
                                                    BOARD="$(BOARD)" DEBUG="$(DEBUG)" \
                                                    PREFIX="$(PREFIX)" CC="$(CC)" \
                                                    CFLAGS="$(CFLAGS)" \
                                                    WITH_COAP_ENABLED="$(WITH_COAP_ENABLED)"

clean-minimal:
	$(QUIET_CHAR)$(MAKE) -C minimal clean

realclean-minimal:
	$(QUIET_CHAR)$(MAKE) -C minimal realclean

run-minimal:
	$(QUIET_CHAR)$(MAKE) -C minimal run QUIET="$(QUIET)" \
                                            BOARD="$(BOARD)" DEBUG="$(DEBUG)" \
                                            PREFIX="$(PREFIX)" CC="$(CC)" \
                                            CFLAGS="$(CFLAGS)" \
                                            WITH_COAP_ENABLED="$(WITH_COAP_ENABLED)"

build: build-minimal

run: run-minimal

clean: clean-minimal

realclean: realclean-minimal

.PHONY: all build clean realclean \
        build-minimal run-minimal clean-minimal realclean-minimal
