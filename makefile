include config.mk

all: $(TARGET)

deps/liblist/liblist.a:
	make -C deps/liblist/

deps/libzahl/libzahl.a:
	make -C deps/libzahl/

sraedler: sraedler.o
	$(CC) $(LDFLAGS) -o $@ $<

craedler: craedler.o $(LIB)
	$(CC) $(LDFLAGS) -o $@ $< $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	make -C deps/liblist/ clean
	make -C deps/libzahl/ clean
	rm -rf *.o $(TARGET)

install: $(TARGET)
	mkdir -p $(PREFIX)/bin
	cp $(TARGET) $(PREFIX)/bin
	cd $(PREFIX)/bin/ && chmod 755 $(TARGET)

uninstall:
	cd $(PREFIX)/bin && rm -f $(TARGET)
