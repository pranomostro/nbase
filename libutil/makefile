include config.mk

all: libutil.a

%.o: %.c $(HDR) $(CONFIG)
	$(CC) $(CFLAGS) -c -o $@ $<

libutil.a: $(OBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@
clean:
	-rm -- *.o *.a

.PHONY: all clean
