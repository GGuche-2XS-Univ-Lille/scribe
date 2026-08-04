ifeq ($(BOARD),)
$(warning BOARD has not been defined, fallback to 'workstation')
override BOARD := workstation
endif

ifdef BOARD
ifneq ($(words $(BOARD)), 1)
$(error BOARD variable must contain only one word ! Here BOARD=$(BOARD))
endif
endif
