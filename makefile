include config.mk

all: $(TARGET)
deps/libzahl/libzahl.a:
	make -C deps/libzahl/

raedler: raedler.o $(LIB)
	$(CC) $(LDFLAGS) -o $@ $< $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	make -C deps/libzahl/ clean
	rm -rf *.o $(TARGET)

install: $(TARGET)
	mkdir -p $(PREFIX)/bin
	cp $(TARGET) $(PREFIX)/bin
	cd $(PREFIX)/bin/ && chmod 755 $(TARGET)

uninstall:
	cd $(PREFIX)/bin && rm -f $(TARGET)
