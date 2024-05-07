#
# A simple makefile for compiling a c++ project
#

# Compile paths:
SRC_DIR = .
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
BUILDDIR = build

# Header search paths
SYSTEM_HEADERS = /usr/local/include
HEADERS = 

CV_FLAGS = 
COMPILER = clang++
CFLAGS = --system-header-prefix=$(SYSTEM_HEADERS) $(HEADERS) -std=c++20 $(CV_FLAGS)
LAUNCHARGS = 
RM = rm -rf

# Release options (in addition to global CFLAGS):
RFLAGS = $(CFLAGS) -O3 -flto

#all: clean default test
all: build run
default: all

.PHONY: all build run

build:
	mkdir -p build
	for source in $(SOURCES); do \
	  outfile="$(BUILDDIR)/$$(basename "$$source" | cut -d '.' -f1)" ; \
		[ -f "$$outfile" ] && [ "$$source" -nt "$$outfile" ] && "$(COMPILER)" "$(RFLAGS)" "$$source" -o "$$outfile" ; \
	done | parallel

run: build
	$(info ===== Running Tests ===== )
	@fail=0 && for sfile in $(BUILDDIR)/*; do \
		/bin/echo -n "Testing $$sfile ... " ; \
		result="Failed" ; \
		$$sfile $(LAUNCHARGS) && result="Passed" || fail=1 ; \
		echo $$result ; \
	done ; \
	exit $$fail



clean:
	$(RM) $(BUILDDIR)/*
