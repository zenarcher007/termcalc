#
# A simple makefile for compiling a c++ project
#

# Compile paths:
SOURCES = termcalc.cpp
DEBUGDIR = debug
TESTDIR = tests
RELEASEDIR = release
EXECUTABLE = termcalc

# Header search paths
HEADERS = 

CV_FLAGS = -Wno-unused-value -DNCURSES_STATIC $(shell pkg-config --cflags --libs ncurses)
COMPILER := $(shell if command -v clang++ >/dev/null 2>&1; then echo clang++; else echo g++; fi)
#COMPILER = clang++
CFLAGS = $(HEADERS) -std=c++20 $(CV_FLAGS)
LAUNCHARGS = 
RM = rm -rf



# Debug options (in addition to global CFLAGS):
DFLAGS = $(CFLAGS) -gdwarf-4 -g3

# Release options (in addition to global CFLAGS):
RFLAGS = $(CFLAGS) -O3 -flto

all: clean release
default: all


release: *.h *.c *.cpp $(SOURCES)
	mkdir -p "$(RELEASEDIR)"
	# Note: $^ : A list of all the dependencies
	$(COMPILER) $(SOURCES) -o $(RELEASEDIR)/$(EXECUTABLE) $(RFLAGS)

debug: *.h *.c *.cpp $(SOURCES)
	mkdir -p "$(DEBUGDIR)"
	$(COMPILER) $(SOURCES)  -o  $(DEBUGDIR)/$(EXECUTABLE) $(DFLAGS)

#.PHONY: all clean debug release

cleanbuildtests:
	cd $(TESTDIR) && make clean build

# The entire continuous integration test cycle
test:
	cd $(TESTDIR) && make clean build run

run:
	$(RELEASEDIR)/$(EXECUTABLE) $(LAUNCHARGS)

clean:
	$(RM) $(DEBUGDIR)/* $(RELEASEDIR)/*
