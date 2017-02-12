#paths
PREFIX=/usr/local

CC=musl-gcc
AR=ar
RANLIB=ranlib

CFLAGS=-g -std=c99 -Wall -DGOOD_RAND
LDFLAGS= -g -static
