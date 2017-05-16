PREFIX=/usr/local

CC=cc
AR=ar
RANLIB=ranlib

CFLAGS=-Wall -Wextra -std=c99 -pedantic -O2 -DGOOD_RAND
LDFLAGS=-s

BIN=collatz fact fib leyland
MAN=$(BIN:=.1)
CONF=config.mk
