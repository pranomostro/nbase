include config.mk

all: $(TARGET)

libzahl/libzahl.a: $(ZAHLSRC)
	make -C libzahl/
libnal/libnal.a: $(NALSRC)
	make -C libnal

leyland: leyland.o $(LIB)
	$(CC) $(LDFLAGS) -o $@ $< $(LIB)

zerbin: zerbin.o $(LIB)
	$(CC) $(LDFLAGS) -o $@ $< $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	make -C libzahl/ clean
	make -C libnal/ clean
	rm -rf *.o $(TARGET)

install: $(TARGET)
	mkdir -p $(PREFIX)/bin
	cp $(TARGET) $(PREFIX)/bin
	cd $(PREFIX)/bin/ && chmod 755 $(TARGET)

uninstall:
	cd $(PREFIX)/bin && rm -f $(TARGET)

.PHONY: all clean install uninstall
