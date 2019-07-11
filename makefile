include config.mk

HDR= \
	arg.h \
	queue.h \
	util.h \
	zahl.h

LIBZAHL=libzahl.a
LIBZAHLSRC= \
	libzahl/allocator.c \
	libzahl/zadd.c \
	libzahl/zand.c \
	libzahl/zbset.c \
	libzahl/zdivmod.c \
	libzahl/zerror.c \
	libzahl/zfree.c \
	libzahl/zgcd.c \
	libzahl/zload.c \
	libzahl/zlsh.c \
	libzahl/zmodmul.c \
	libzahl/zmodpow.c \
	libzahl/zmodpowu.c \
	libzahl/zmodsqr.c \
	libzahl/zmul.c \
	libzahl/znot.c \
	libzahl/zor.c \
	libzahl/zperror.c \
	libzahl/zpow.c \
	libzahl/zpowu.c \
	libzahl/zptest.c \
	libzahl/zrand.c \
	libzahl/zrsh.c \
	libzahl/zsets.c \
	libzahl/zsetup.c \
	libzahl/zsqr.c \
	libzahl/zstr.c \
	libzahl/zstr_length.c \
	libzahl/zsub.c \
	libzahl/ztrunc.c \
	libzahl/zunsetup.c \
	libzahl/zxor.c

LIBUTIL=libutil.a
LIBUTILSRC= \
	libutil/clit.c \
	libutil/ealloc.c \
	libutil/eprintf.c \
	libutil/fshut.c \
	libutil/nal.c \
	libutil/reallocarray.c \
	libutil/strtonum.c

LIBTOO=libtoo.a
LIBTOOSRC= \
	libtoo/eratosthenes_bitarr.c \
	libtoo/eratosthenes_list.c

LIB=$(LIBZAHL) $(LIBUTIL) $(LIBTOO)

LIBZAHLOBJ=$(LIBZAHLSRC:.c=.o)
LIBUTILOBJ=$(LIBUTILSRC:.c=.o)
LIBTOOOBJ=$(LIBTOOSRC:.c=.o)
OBJ=$(BIN:=.o) $(LIBZAHLOBJ) $(LIBUTILOBJ) $(LIBTOOOBJ)

all: $(BIN)

$(BIN): $(LIB) $(@:=.o)
$(OBJ): $(HDR) $(CONF)

.o:
	$(CC) $(LDFLAGS) -o $@ $< $(LIB)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBZAHL): $(LIBZAHLOBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@
$(LIBUTIL): $(LIBUTILOBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@
$(LIBTOO): $(LIBTOOOBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@

clean:
	rm -f $(BIN) $(OBJ) $(LIB)

install: all
	mkdir -p $(PREFIX)/bin/
	cp $(BIN) $(PREFIX)/bin/
	cp $(MAN) $(PREFIX)/share/man/man1/
	cd $(PREFIX)/bin/ && chmod 755 $(BIN)
	cd $(PREFIX)/share/man/man1/ && chmod 644 $(MAN)

uninstall:
	cd $(PREFIX)/bin/ && rm -f $(BIN)
	cd $(PREFIX)/share/man/man1/ && rm -f $(MAN)

.PHONY: all clean install uninstall
