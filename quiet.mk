QUIET ?= 0
MAKE_SILENT_FLAGS= -s --silent --quiet
ifeq ($(QUIET), 0)
QUIET_CHAR := @
ifeq ($(filter $(MAKE_SILENT_FLAGS), $(MAKEFLAGS)),)
MAKEFLAGS += --silent
endif
else
QUIET_CHAR :=
endif
