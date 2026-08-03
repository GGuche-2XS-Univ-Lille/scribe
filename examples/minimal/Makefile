ROOT             := $(abspath ../..)
ifeq ($(BOARD),)
$(warning BOARD has not been defined, fallback to 'workstation')
override BOARD := workstation
endif

TARGET           ?= bin/minimal
SOURCES          := $(wildcard *.c)
OBJECTS          := $(SOURCES:%.c=build/%.o)
SCRIBE_LIB_SHORT := $(BOARD)/scribe.a
SCRIBE_LIB       := $(ROOT)/$(SCRIBE_LIB_SHORT)
CONFIGURE        := $(ROOT)/configure.sh
ALL_TARGETS      := $(TARGET)

ifeq ($(ROOT),)
$(error ROOT has not been defined)
endif

ifeq ($(CC),)
$(warning CC has not been defined, fallback to 'cc')
CC := cc
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
override CFLAGS           += -Og
override CFLAGS           += -ggdb
endif

all: $(ALL_TARGETS)

$(SCRIBE_LIB):
ifdef VERBOSE
	$(info For $(SCRIBE_LIB):)
	$(info - PREFIX is '$(PREFIX)')
	$(info - CC is '$(CC)')
	$(info - BOARD is '$(BOARD)')
	$(info - CFLAGS is '$(CFLAGS)')
endif
	$(CONFIGURE) --board=$(BOARD)
	$(MAKE) -C $(ROOT) $(SCRIBE_LIB_SHORT) \
		BOARD="$(BOARD)" DEBUG="$(DEBUG)" PREFIX="$(PREFIX)" CFLAGS="$(CFLAGS)"

build:
	mkdir -p $@

bin:
	mkdir -p $@

build/%.o: %.c | build
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) $(SCRIBE_LIB) | bin
	$(CC) $(OBJECTS) $(SCRIBE_LIB) -o $@

clean:
	$(RM) -r build

realclean: clean
	$(RM) -r bin

.PHONY: all clean realclean
