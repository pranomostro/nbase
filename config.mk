PREFIX=/usr/local

CC=musl-gcc

CFLAGS=-Wall -Wextra -std=c99 -pedantic -O2
LDFLAGS=-s -static -lm

TARGET=craedler sraedler

LIB=deps/libzahl/libzahl.a deps/liblist/liblist.a
