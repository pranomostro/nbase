include config.mk

.SUFFIXES:
.SUFFIXES: .o .c

HDR =\
	arg.h\
	zahl.h\
	util.h

LIBZAHL = libzahl.a
LIBZAHLSRC =\
	libzahl/zadd.c\
	libzahl/zand.c\
	libzahl/zbset.c\
	libzahl/zdivmod.c\
	libzahl/zerror.c\
	libzahl/zfree.c\
	libzahl/zgcd.c\
	libzahl/zload.c\
	libzahl/zlsh.c\
	libzahl/zmodmul.c\
	libzahl/zmodpow.c\
	libzahl/zmodpowu.c\
	libzahl/zmodsqr.c\
	libzahl/zmul.c\
	libzahl/znot.c\
	libzahl/zor.c\
	libzahl/zperror.c\
	libzahl/zpow.c\
	libzahl/zpowu.c\
	libzahl/zptest.c\
	libzahl/zrand.c\
	libzahl/zrsh.c\
	libzahl/zsets.c\
	libzahl/zsetup.c\
	libzahl/zsqr.c\
	libzahl/zstr.c\
	libzahl/zstr_length.c\
	libzahl/zsub.c\
	libzahl/ztrunc.c\
	libzahl/zunsetup.c\
	libzahl/zxor.c\
	libzahl/allocator.c

LIBUTIL = libutil.a
LIBUTILSRC =\
	libutil/clit.c\
	libutil/nal.c

LIB = $(LIBZAHL) $(LIBUTIL)

BIN =\
	collatz\
	leyland

LIBZAHLOBJ = $(LIBZAHLSRC:.c=.o)
LIBUTILOBJ = $(LIBUTILSRC:.c=.o)
OBJ = $(BIN:=.o) $(LIBZAHLOBJ) $(LIBUTILOBJ)
SRC = $(BIN:=.c)
MAN= $(BIN:=.1)

all: $(BIN)

$(BIN): $(LIB) $(@:=.o)

$(OBJ): $(HDR) config.mk

.o:
	$(CC) $(LDFLAGS) -o $@ $< $(LIB)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(LIBZAHL): $(LIBZAHLOBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@

$(LIBUTIL): $(LIBUTILOBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@

install: all
	mkdir -p $(PREFIX)/bin
	cp -f $(BIN) $(PREFIX)/bin
	cd $(PREFIX)/bin && chmod 755 $(BIN)
	mkdir -p $(PREFIX)/man/man1
	cp -f $(MAN) $(PREFIX)/man/man1
	cd $(PREFIX)/man/man1 && chmod 644 $(MAN)

uninstall:
	cd $(PREFIX)/bin && rm -f $(BIN)
	cd $(PREFIX)/man/man1 && rm -f $(MAN)

clean:
	rm -f $(BIN) $(OBJ) $(LIB)

.PHONY:
	all install uninstall clean
