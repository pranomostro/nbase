PREFIX=/usr/local

CC=musl-gcc

CFLAGS=-Wall -Wextra -std=c99 -pedantic -g
LDFLAGS=-static -lm

TARGET=raedler

LIB=deps/libzahl/libzahl.a
