PREFIX=/usr/local

CC=musl-gcc

CFLAGS=-Wall -Wextra -std=c99 -pedantic -O2 -Os
LDFLAGS=-s -static -lm

TARGET=raedler

LIB=deps/libzahl/libzahl.a
