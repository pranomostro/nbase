include config.mk

all: $(TARGET)

libzahl/libzahl.a: $(ZAHLSRC)
	make -C libzahl/

raedler: raedler.o $(LIB)
	$(CC) $(LDFLAGS) -o $@ $< $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	make -C libzahl/ clean
	rm -rf *.o $(TARGET)

install: $(TARGET)
	mkdir -p $(PREFIX)/bin
	cp $(TARGET) $(PREFIX)/bin
	cd $(PREFIX)/bin/ && chmod 755 $(TARGET)

uninstall:
	cd $(PREFIX)/bin && rm -f $(TARGET)
