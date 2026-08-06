ifeq ($(strip $(COMPILER_MK)),)
COMPILER_MK := COMPILER_MAKEFILE

ifdef PREFIX_NONE
    $(error PREFIX_NONE has already been defined outside of compiler.mk)
endif
PREFIX_NONE :=

ifdef PREFIX_ARM_NONE_EABI
    $(error PREFIX_ARM_NONE_EABI has already been defined outside of compiler.mk)
endif
PREFIX_ARM_NONE_EABI := arm-none-eabi-

ifdef PREFIX_DEFAULT
    $(error PREFIX_DEFAULT has already been defined outside of compiler.mk)
endif
PREFIX_DEFAULT := $(PREFIX_NONE)

ifdef PREFIX_POSSIBLE_VALUES
    $(error PREFIX_POSSIBLE_VALUES has already been defined outside of compiler.mk)
endif
PREFIX_POSSIBLE_VALUES := \"$(PREFIX_ARM_NONE_EABI)\"

ifdef CC_NONE
    $(error CC_NONE has already been defined outside of compiler.mk)
endif
CC_NONE :=

ifdef CC_GCC
    $(error CC_GCC has already been defined outside of compiler.mk)
endif
CC_GCC := $(PREFIX)gcc

ifdef CC_POSSIBLE_VALUES
    $(error CC_POSSIBLE_VALUES has already been defined outside of compiler.mk)
endif
CC_POSSIBLE_VALUES := \"$(CC_GCC)\"

ifdef CC_DEFAULT_VALUE
    $(error CC_DEFAULT_VALUE has already been defined outside of compiler.mk)
endif
CC_DEFAULT_VALUE := $(CC_GCC)

ifndef CC
    CC := $(CC_NONE)
endif

ifeq ($(strip $(CC)),)
    override CC := $(CC_DEFAULT_VALUE)
    ifeq ($(QUIET_CHAR),)
        $(warning CC has not been defined, fallback to "$(CC)")
    endif
else
    ifeq ($(strip $(CC)),cc)
        override CC := $(CC_DEFAULT_VALUE)
        ifeq ($(QUIET_CHAR),)
            $(warning CC has been defined as "cc", fallback to "$(CC)")
        endif
    endif
endif

ifneq ($(words $(CC)), 1)
    $(error CC variable must contain only one word ! Here CC="$(CC)")
endif

ifeq ($(filter \"$(CC)\", $(CC_POSSIBLE_VALUES)),)
    $(error CC ("$(CC)") is not in supported coap values ($(CC_POSSIBLE_VALUES)))
endif

ifeq ($(QUIET_CHAR),)
    $(info CC is "$(CC)")
endif

endif # ($(strip $(COMPILER_MK),)
