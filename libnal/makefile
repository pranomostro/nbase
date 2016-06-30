include config.mk

all: libnal.a

%.o: %.c $(HDR) $(CONFIG)
	$(CC) $(CFLAGS) -c -o $@ $<

libnal.a: $(OBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@
clean:
	-rm -- *.o *.a

.PHONY: all clean
