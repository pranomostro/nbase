#paths
PREFIX=/usr/local

CC=cc
AR=ar
RANLIB=ranlib

CFLAGS=-std=c99 -O3 -flto -Wall -pedantic -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -DGOOD_RAND
LDFLAGS=-s -static
