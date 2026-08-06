ifndef ROOT
    ROOT:=
endif

ifeq ($(strip $(ROOT)),)
    $(error ROOT variable has not been defined. Please fix this.)
endif
