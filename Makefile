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

CV_FLAGS = -lncurses -Wno-unused-value
COMPILER = clang++
CFLAGS = --system-header-prefix=$(SYSTEM_HEADERS) $(HEADERS) -std=c++20 $(CV_FLAGS)
LAUNCHARGS = 
RM = rm -rf



# Debug options (in addition to global CFLAGS):
DFLAGS = $(CFLAGS) -gdwarf-4 -g3

# Release options (in addition to global CFLAGS):
RFLAGS = $(CFLAGS) -O -flto

all: clean release
default: all


release: *.h *.c *.cpp $(SOURCES)
	mkdir -p "$(RELEASEDIR)"
	# Note: $^ : A list of all the dependencies
	$(COMPILER) $(RFLAGS) $(SOURCES) -o $(RELEASEDIR)/$(EXECUTABLE)

debug: *.h *.c *.cpp $(SOURCES)
	mkdir -p "$(DEBUGDIR)"
	$(COMPILER) $(DFLAGS) $(SOURCES)  -o  $(DEBUGDIR)/$(EXECUTABLE)

#.PHONY: all clean debug release

cleanbuildtests:
	cd $(TESTDIR) && make clean build

# The entire continuous integration test cycle
test: release
	cd $(TESTDIR) && make clean build run

run:
	$(RELEASEDIR)/$(EXECUTABLE) $(LAUNCHARGS)

clean:
	$(RM) $(DEBUGDIR)/* $(RELEASEDIR)/*
