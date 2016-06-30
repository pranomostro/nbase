CONFIG = config.mk
include $(CONFIG)

HDR_SEMIPUBLIC =\
	zahl/inlines.h\
	zahl/internals.h\
	zahl/memory.h

HDR_PRIVATE =\
	src/internals.h

FUN =\
	zadd\
	zand\
	zbset\
	zdivmod\
	zerror\
	zfree\
	zgcd\
	zload\
	zlsh\
	zmodmul\
	zmodpow\
	zmodpowu\
	zmodsqr\
	zmul\
	znot\
	zor\
	zperror\
	zpow\
	zpowu\
	zptest\
	zrand\
	zrsh\
	zsets\
	zsetup\
	zsqr\
	zstr\
	zstr_length\
	zsub\
	ztrunc\
	zunsetup\
	zxor

INLINE_FUN =\
	zabs\
	zbits\
	zbtest\
	zcmp\
	zcmpi\
	zcmpmag\
	zcmpu\
	zdiv\
	zeven\
	zeven_nonzero\
	zinit\
	zlsb\
	zmod\
	zneg\
	zodd\
	zodd_nonzero\
	zsave\
	zset\
	zseti\
	zsetu\
	zsignum\
	zsplit\
	zswap\
	zzero

HDR_PUBLIC = zahl.h $(HDR_SEMIPUBLIC)
HDR        = $(HDR_PUBLIC) $(HDR_PRIVATE)
OBJ        = $(FUN:=.o) allocator.o
MAN3       = $(FUN:=.3) $(INLINE_FUN:=.3)
MAN7       = libzahl.7

VPATH = src

CPPFLAGS += $(BENCHMARK_CPP_$(BENCHMARK_LIB))

CFLAGS_WITHOUT_O = $$(printf '%s\n' $(CFLAGS) | sed '/^-O.*$$/d')


all: libzahl.a

.o: .c $(HDR) $(CONFIG)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

libzahl.a: $(OBJ)
	$(AR) rc $@ $?
	$(RANLIB) $@
clean:
	-rm -- *.o *.a

.PHONY: all check clean install uninstall
