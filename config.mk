#paths
PREFIX=/usr/local

CC=musl-gcc
AR=ar
RANLIB=ranlib

CFLAGS=-std=c99 -Wall -O2
LDFLAGS=-s -static
