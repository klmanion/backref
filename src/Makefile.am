## src/Makefile.am

AM_CFLAGS = @AM_CFLAGS@
AM_CPPFLAGS = @AM_CPPFLAGS@

if IS_GCC
AM_CFLAGS += -std=gnu99 -O2
if IS_DEBUG
AM_CFLAGS += -Wall -pedantic
AM_CPPFLAGS += -DDEBUG
else
AM_CPPFLAGS += -DNDEBUG
endif
endif

bin_PROGRAMS = backref
backref_SOURCES = main.c encode.c decode.c backref.c
