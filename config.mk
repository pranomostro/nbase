PREFIX=/usr/local

CC=musl-gcc

CFLAGS=-Wall -std=c99 -pedantic -O2
LDFLAGS=-s -static

TARGET=leyland collatz

LIB=libzahl/libzahl.a libutil/libutil.a

UTILSRC=libutil/nal.c libutil/clit.c
ZAHLSRC=libzahl/src/allocator.c libzahl/src/internals.h libzahl/src/zadd.c libzahl/src/zand.c libzahl/src/zbset.c libzahl/src/zdivmod.c libzahl/src/zerror.c libzahl/src/zfree.c libzahl/src/zgcd.c libzahl/src/zload.c libzahl/src/zlsh.c libzahl/src/zmodmul.c libzahl/src/zmodpow.c libzahl/src/zmodpowu.c libzahl/src/zmodsqr.c libzahl/src/zmul.c libzahl/src/znot.c libzahl/src/zor.c libzahl/src/zperror.c libzahl/src/zpow.c libzahl/src/zpowu.c libzahl/src/zptest.c libzahl/src/zrand.c libzahl/src/zrsh.c libzahl/src/zsets.c libzahl/src/zsetup.c libzahl/src/zsqr.c libzahl/src/zstr.c libzahl/src/zstr_length.c libzahl/src/zsub.c libzahl/src/ztrunc.c libzahl/src/zunsetup.c libzahl/src/zxor.c
