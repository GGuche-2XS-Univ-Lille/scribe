ifndef RIOT_CFLAGS
ifeq ("$(wildcard toolchain.mk)","")
    $(error "Run ./configure.sh first")
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
CFLAGS         += -Os
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

TARGET          = scribe
SOURCES         = $(wildcard src/*.c)
OBJECTS         = $(SOURCES:.c=.o)

OBJS = $(addprefix $(BOARD)/,$(OBJECTS))

all: $(BOARD)/$(TARGET).a examples

$(BOARD)/src:
	mkdir -p $(BOARD)/src

$(BOARD)/src/%.c: src/%.c $(BOARD)/src
	cp $< $@

ifdef DEBUG
.PRECIOUS: $(BOARD)/src/%.c
endif

$(BOARD)/$(TARGET).a: $(OBJS)
	$(AR) rcs $@ $^

$(BOARD)/src/%.o: $(BOARD)/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

examples:
	$(MAKE) -C examples BOARD="$(BOARD)" DEBUG="$(DEBUG)" PREFIX="$(PREFIX)" CC="$(CC)" \
                           CFLAGS="$(CFLAGS)"

clean-examples:
	$(MAKE) -C examples clean

realclean-examples:
	$(MAKE) -C examples realclean

clean-objects:
	$(RM) $(BOARD)/$(OBJECTS)

clean: clean-objects clean-examples

realclean: realclean-examples
	$(RM) -rf workstation
	$(RM) -f toolchain.mk

.PHONY: all clean clean-objects realclean clean-examples realclean-examples
