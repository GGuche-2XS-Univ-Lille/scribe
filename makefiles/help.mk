ifeq ($(strip $(HELP_MK)),)
HELP_MK := HELP_MAKEFILE

ifneq ($(strip $(HELP_RULE_LINE_FORMAT)),)
    $(error "HELP_RULE_LINE_FORMAT has already been defined")
endif

ifneq ($(strip $(help_rule_line)),)
    $(error "help_rule_line has already been defined")
endif

HELP_RULE_LINE_FORMAT := "%-24s %s\n"

define help_rule_line
printf $(HELP_RULE_LINE_FORMAT) "$(1)" "$(2)"
endef

define help_start_variables_lines
printf "\nMakefile VARIABLES:\n"
printf "  The following variables can be overriden on \"%s\" commands line.\n\n" $(MAKE)
endef

define help_variable_line
printf "  -Name:\"%s\"\n" $(1)
printf "    -Description : %s\n" $(2)
printf "    -Possible values : %s\n" $(3)
printf "    -Default value : \"%s\"\n" $(4)
endef

endif # ($(strip $(HELP_MK),)
