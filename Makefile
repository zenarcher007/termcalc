#
# A simple makefile for compiling a c++ project
#

# Compile paths:
SOURCES = termcalc.cpp
DEBUGDIR = debug
TESTDIR = tests
RELEASEDIR = release
EXECUTABLE = termcalc
CPPSTANDARD = c++20

# Header search paths
HEADERS = 

# TODO: -l:tinyexpr.a: this syntax does not work on Darwin tested. This would otherwise be just -ltinyexpr
CV_FLAGS = -Wno-unused-value -DNCURSES_STATIC $(shell pkg-config --cflags --libs ncurses) -Ltinyexprlib -ltinyexpr
COMPILER := $(shell if command -v clang++ >/dev/null 2>&1; then echo clang++; else echo g++; fi)
C_COMPILER := "clang" #$(shell if [ "$(COMPILER)" == "clang++" ]; then echo clang ; else echo gcc ; fi )
#$(shell if command -v clang >/dev/null 2>&1; then echo clang; else echo gcc; fi)
#COMPILER = clang++
CFLAGS = $(HEADERS) -std=$(CPPSTANDARD) $(CV_FLAGS)
LAUNCHARGS = 
RM = rm -rf



# Debug options (in addition to global CFLAGS):
DFLAGS = $(CFLAGS) -gdwarf-4 -g3

# Release options (in addition to global CFLAGS):
RFLAGS = $(CFLAGS) -O3 -flto

all: clean release
default: all


release: buildlibraries *.h *.c *.cpp $(SOURCES)
	mkdir -p "$(RELEASEDIR)"
	# Note: $^ : A list of all the dependencies
	$(COMPILER) $(SOURCES) -o $(RELEASEDIR)/$(EXECUTABLE) $(RFLAGS)

debug: buildlibraries *.h *.c *.cpp $(SOURCES)
	mkdir -p "$(DEBUGDIR)"
	$(COMPILER) $(SOURCES)  -o  $(DEBUGDIR)/$(EXECUTABLE) $(DFLAGS)

#.PHONY: all clean debug release

cleanbuildtests:
	cd $(TESTDIR) && make clean build

# Why doesnt this work??
#mklibrarydir:
#	mkdir -p tinyexprlib
# mklibrarydir tinyexpr.c tinyexpr.h tinyexprlib/libtinyexpr.a
buildlibraries:
	echo "Using C compiler: $(C_COMPILER)"
	$(C_COMPILER) -O3 -flto -c tinyexpr.c -o tinyexprlib/tinyexpr.o
	ar rcs tinyexprlib/libtinyexpr.a tinyexprlib/tinyexpr.o
	rm tinyexprlib/tinyexpr.o

# The entire continuous integration test cycle
test: buildlibraries
	cd $(TESTDIR) && make clean build run

run:
	$(RELEASEDIR)/$(EXECUTABLE) $(LAUNCHARGS)

clean:
	$(RM) $(DEBUGDIR)/* $(RELEASEDIR)/* tinyexprlib/*
