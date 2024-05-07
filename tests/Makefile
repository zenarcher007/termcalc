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
		echo "$(COMPILER) $(RFLAGS) $$source -o $(BUILDDIR)/$$(basename "$$source" | cut -d '.' -f1)" ; \
	done | parallel

run: build
	$(info ===== Running Tests ===== )
	@for source in $(BUILDDIR)/*; do \
		/bin/echo -n "Testing $$source ... " ; \
		$$source $(LAUNCHARGS) && echo Passed || echo Failed ; \
	done



clean:
	$(RM) $(BUILDDIR)/*
