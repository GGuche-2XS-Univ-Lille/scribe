ifeq ($(strip $(VARIABLES_MK)),)
VARIABLES_MK := VARIABLES_MAKEFILE


include $(ROOT)/makefiles/root.mk
include $(ROOT)/makefiles/help.mk
include $(ROOT)/makefiles/quiet.mk
include $(ROOT)/makefiles/board.mk
include $(ROOT)/makefiles/debug.mk
include $(ROOT)/makefiles/compiler.mk
include $(ROOT)/makefiles/log.mk
include $(ROOT)/makefiles/log_severity_level.mk
include $(ROOT)/makefiles/coap.mk

define help_variables
$(call help_start_variables_lines)

$(call help_variable_line,QUIET,"Silences all commands in makefiles when it is defined and differs from \"$(QUIET_DISABLED)\"","$(QUIET_POSSIBLE_VALUES)","$(QUIET_DEFAULT_VALUE)")

$(call help_variable_line,BOARD,"Sets the target compilation platform","$(BOARD_POSSIBLE_VALUES)","$(BOARD_DEFAULT_VALUE)")

$(call help_variable_line,PREFIX,"Defines the prefix to prepend to the chosen compiler","$(PREFIX_POSSIBLE_VALUES)","$(PREFIX_DEFAULT_VALUE)")

$(call help_variable_line,CC,"Defines the chosen compiler","$(CC_POSSIBLE_VALUES)","$(CC_DEFAULT_VALUE)")

$(call help_variable_line,DEBUG,"Controls debug mode","$(DEBUG_POSSIBLE_VALUES)","$(DEBUG_DEFAULT_VALUE)")

$(call help_variable_line,LOG,"Controls logging support","$(LOG_POSSIBLE_VALUES)","$(LOG_DEFAULT_VALUE)")

$(call help_variable_line,LOG_SEVERITY_LEVEL,"Controls the DEFAULT logging severity level","$(LOG_SEVERITY_LEVELS_POSSIBLE_VALUES)","$(LOG_SEVERITY_LEVEL_DEFAULT_VALUE)")

$(call help_variable_line,COAP,"Controls COAP support","$(COAP_POSSIBLE_VALUES)","$(COAP_DEFAULT_VALUE)")
endef

endif # ($(strip $(VARIABLES_MK),)
