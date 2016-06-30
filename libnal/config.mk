# Please read INSTALL, section 'Configure libzahl'.

CC = cc
AR = ar
RANLIB = ranlib

CFLAGS   = -std=c99 -O3 -flto -Wall -pedantic
LDFLAGS  = -s -static

OBJ=nal.o
HDR=nal.h
