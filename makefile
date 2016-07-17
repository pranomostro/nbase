include config.mk

all: $(TARGET)

libzahl/libzahl.a: $(ZAHLSRC)
	make -C libzahl/
libutil/libutil.a: $(NALSRC)
	make -C libutil

leyland: leyland.o $(LIB)
	$(CC) $(LDFLAGS) -o $@ $< $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	make -C libzahl/ clean
	make -C libutil/ clean
	rm -rf *.o $(TARGET)

install: $(TARGET)
	mkdir -p $(PREFIX)/bin
	cp $(TARGET) $(PREFIX)/bin
	cd $(PREFIX)/bin/ && chmod 755 $(TARGET)

uninstall:
	cd $(PREFIX)/bin && rm -f $(TARGET)

.PHONY: all clean install uninstall
