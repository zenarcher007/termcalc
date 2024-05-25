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

CV_FLAGS = -Wno-unused-value -lncurses
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

build: $(SOURCES)
	mkdir -p build
	for source in $^; do \
		outfile="$(BUILDDIR)/$$(basename "$$source" | cut -d '.' -f1)" ; \
		"$(COMPILER)" "$(RFLAGS)" "$$source" -o "$$outfile" ; \
	done
#for source in $(SOURCES); do \
#  outfile="$(BUILDDIR)/$$(basename "$$source" | cut -d '.' -f1)" ; \
#	[ -f "$$outfile" ] && [ "$$source" -nt "$$outfile" ] && "$(COMPILER)" "$(RFLAGS)" "$$source" -o "$$outfile" ; \
#done | parallel

run: build
	$(info ===== Running Tests On Last (or current) Compilation ===== )
	echo "\n\n===== Running Tests On Last (or current) Compilation at $$(date) =====" >> tests.log
	@for sfile in $(BUILDDIR)/*; do \
	  /bin/echo "Queueing $$sfile ..." 1>&2 ; \
	  /bin/echo "/bin/echo && /bin/echo '>Testing $$sfile ... ' && ./$$sfile 2>&1 && echo '>Passed' $$sfile " ; \
	done | bash -c "parallel --keep-order --group 2>&1 --halt-on-error soon,fail,10 2>&1 | tee >(cat 1>&2) >> tests.log" 2>&1 | bash -c "tee >(cat 1>&2)" | grep 'parallel: This job failed' >/dev/null && exit 1 || exit 0




clean:
	$(RM) $(BUILDDIR)/* ; \
	rm -f tests.log
