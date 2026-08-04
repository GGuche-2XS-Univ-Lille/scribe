include board.mk
include quiet.mk

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

CC              = $(PREFIX)gcc
AR              = $(PREFIX)ar

CFLAGS          = -Wall
CFLAGS         += -Wextra
CFLAGS         += -Werror
ifeq ($(BOARD), workstation)
CFLAGS         += -std=c11
CFLAGS         += -Wno-unused-function
else
CFLAGS         += -ffreestanding
CFLAGS         += -mthumb
endif
CFLAGS         += $(BOARD_CFLAGS)
ifndef DEBUG
CFLAGS         += -Os -DNDEBUG
else
CFLAGS         += -Og
CFLAGS         += -ggdb
endif
CFLAGS         += -I./include
ifdef RIOT_CFLAGS
CFLAGS         += $(RIOT_INCLUDES)
CFLAGS         += $(RIOT_CFLAGS)
else # RIOT_CFLAGS
CFLAGS         += -Iboards/$(BOARD)
endif # RIOT_CFLAGS
ifdef WITH_COAP_ENABLED
ifeq ($(filter "-DSCRIBE_COAP_SINK_ENABLED", $(CFLAGS)),)
CFLAGS         += -DSCRIBE_COAP_SINK_ENABLED
endif
endif

TARGET          = scribe
SOURCES         = $(wildcard src/*.c)
OBJECTS         = $(SOURCES:.c=.o)

OBJS = $(addprefix $(BOARD)/,$(OBJECTS))


all: $(BOARD)/$(TARGET).a build-examples run-examples

$(BOARD)/src:
	$(QUIET_CHAR)mkdir -p $(BOARD)/src

$(BOARD)/src/%.c: src/%.c $(BOARD)/src
	$(QUIET_CHAR)cp $< $@

ifdef DEBUG
.PRECIOUS: $(BOARD)/src/%.c
endif

$(BOARD)/$(TARGET).a: $(OBJS)
	$(QUIET_CHAR)$(AR) rcs $@ $^

$(BOARD)/src/%.o: $(BOARD)/src/%.c
	$(QUIET_CHAR)$(CC) $(CFLAGS) -c $< -o $@

build-examples: $(BOARD)/$(TARGET).a
	$(QUIET_CHAR)$(MAKE) -C examples build QUIET="$(QUIET)" \
                                               BOARD="$(BOARD)" DEBUG="$(DEBUG)" \
                                               PREFIX="$(PREFIX)" CC="$(CC)" CFLAGS="$(CFLAGS)" \
                                               WITH_COAP_ENABLED="$(WITH_COAP_ENABLED)"

run-examples: build-examples
	$(QUIET_CHAR)$(MAKE) -C examples run QUIET="$(QUIET)" \
                                             BOARD="$(BOARD)" DEBUG="$(DEBUG)" \
                                             PREFIX="$(PREFIX)" CC="$(CC)" CFLAGS="$(CFLAGS)" \
                                             WITH_COAP_ENABLED="$(WITH_COAP_ENABLED)"

clean-examples:
	$(QUIET_CHAR)$(MAKE) -C examples clean

realclean-examples:
	$(QUIET_CHAR)$(MAKE) -C examples realclean

clean-objects:
	$(QUIET_CHAR)$(RM) $(BOARD)/$(OBJECTS)

clean: clean-objects clean-examples

realclean: realclean-examples
	$(QUIET_CHAR)$(RM) -rf workstation
	$(QUIET_CHAR)$(RM) -f toolchain.mk

.PHONY: all clean-objects clean realclean \
        clean-examples realclean-examples run-examples
