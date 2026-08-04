ROOT             := $(abspath ../..)

include $(ROOT)/quiet.mk
include $(ROOT)/board.mk

TARGET           ?= bin/minimal
SOURCES          := $(wildcard *.c)
OBJECTS          := $(SOURCES:%.c=build/%.o)
SCRIBE_LIB_SHORT := $(BOARD)/scribe.a
SCRIBE_LIB       := $(ROOT)/$(SCRIBE_LIB_SHORT)
CONFIGURE        := $(ROOT)/configure.sh
ALL_TARGETS      := $(TARGET)


ifeq ($(BOARD), workstation)
ALL_TARGETS      += run
endif

ifeq ($(ROOT),)
$(error ROOT has not been defined)
endif

ifeq ($(CC),)
$(warning CC has not been defined, fallback to 'cc')
override CC := cc
endif


ifeq ($(MAKECMDGOALS),)
override MAKECMDGOALS := $(ALL_TARGETS)
endif

CFLAGS_TARGETS := $(TARGET) $(SCRIBE_LIB)
ifneq ($(filter $(CFLAGS_TARGETS), $(MAKECMDGOALS)),)
ifeq ($(CFLAGS),)
$(warning CFLAGS has not been defined)
endif
endif

override CFLAGS           += -Wall
override CFLAGS           += -Wextra
override CFLAGS           += -Werror
override CFLAGS           += --std=c11
override CFLAGS           += -I$(ROOT)
override CFLAGS           += -I$(ROOT)/boards/$(BOARD)
override CFLAGS           += -I$(ROOT)/include
ifdef DEBUG
override CFLAGS           += -Og -ggdb
else
override CFLAGS           += -Os -DNDEBUG
endif
ifdef WITH_COAP_ENABLED
ifeq ($(filter "-DSCRIBE_COAP_SINK_ENABLED", $(CFLAGS)),)
override CFLAGS           += -DSCRIBE_COAP_SINK_ENABLED
endif
endif

PHONY_RULES := all clean realclean
ifeq ($(BOARD), workstation)
PHONY_RULES += run
endif

all: $(ALL_TARGETS)

$(SCRIBE_LIB):
ifdef VERBOSE
	$(info For $(SCRIBE_LIB):)
	$(info - PREFIX is '$(PREFIX)')
	$(info - CC is '$(CC)')
	$(info - BOARD is '$(BOARD)')
	$(info - CFLAGS is '$(CFLAGS)')
	$(info - WITH_COAP_ENABLED is '$(WITH_COAP_ENABLED)')
endif
	$(QUIET_CHAR)$(CONFIGURE) --board=$(BOARD)
	$(QUIET_CHAR)$(MAKE) -C $(ROOT) $(SCRIBE_LIB_SHORT) \
                                        BOARD="$(BOARD)" DEBUG="$(DEBUG)" \
                                        CC=$(CC) PREFIX="$(PREFIX)" CFLAGS="$(CFLAGS)" \
                                        WITH_COAP_ENABLED="$(WITH_COAP_ENABLED)"

build:
	$(QUIET_CHAR)mkdir -p $@

bin:
	$(QUIET_CHAR)mkdir -p $@

build/%.o: %.c | build
	$(QUIET_CHAR)$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) $(SCRIBE_LIB) | bin
	$(QUIET_CHAR)$(CC) $(OBJECTS) $(SCRIBE_LIB) -o $@

ifeq ($(BOARD), workstation)
run: $(TARGET)
	$(QUIET_CHAR)$(TARGET)
endif

clean:
	$(QUIET_CHAR)$(RM) -r build

realclean: clean
	$(QUIET_CHAR)$(RM) -r bin

.PHONY: $(PHONY_RULES)
