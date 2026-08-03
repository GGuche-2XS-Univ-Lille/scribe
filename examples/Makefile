
all: minimal

minimal:
	$(MAKE) -C minimal BOARD="$(BOARD)" DEBUG="$(DEBUG)" PREFIX="$(PREFIX)" CC="$(CC)" \
                           CFLAGS="$(CFLAGS)"

clean-minimal:
	$(MAKE) -C minimal clean

realclean-minimal:
	$(MAKE) -C minimal realclean

clean: clean-minimal

realclean: realclean-minimal

.PHONY: all clean realclean \
        minimal clean-minimal realclean-minimal
