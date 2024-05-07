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
SYSTEM_HEADERS = /usr/local/include
HEADERS = 

CV_FLAGS = -lncurses
COMPILER = clang++
CFLAGS = --system-header-prefix=$(SYSTEM_HEADERS) $(HEADERS) -std=c++20 $(CV_FLAGS)
LAUNCHARGS = 
RM = rm -rf



# Debug options (in addition to global CFLAGS):
DFLAGS = $(CFLAGS) -gdwarf-4 -g3

# Release options (in addition to global CFLAGS):
RFLAGS = $(CFLAGS) -O3 -flto

all: clean release
default: all

debug:
	mkdir -p debug
	$(COMPILER) $(DFLAGS) $(SOURCES) -o $(DEBUGDIR)/$(EXECUTABLE)



release: $(SOURCES)
	mkdir -p release
	$(COMPILER) $(RFLAGS) $^ -o $(RELEASEDIR)/$(EXECUTABLE)

#.PHONY: all clean debug release


test: release
	cd $(TESTDIR) && make run

run:
	$(RELEASEDIR)/$(EXECUTABLE) $(LAUNCHARGS)

clean:
	$(RM) $(DEBUGDIR)/* $(RELEASEDIR)/*
