#subs:=lib test examples #$(patsubst %/Makefile,%,$(wildcard */Makefile))

include recurse.mk

## all:		Build and test AceUnit (library, generator, and integration).
## clean:		Remove all generated files.
## lib-all:	Build and self-test the AceUnit library.

test-all examples-all: lib-all

versions:=c90 c99 c11 c17 c2x gnu90 gnu99 gnu11 gnu17 gnu2x
## compiler-test:	Test AceUnit with different versions of C.
compiler-test: $(versions:%=compiler-test-%)

compiler-test-%:
	$(MAKE) clean
	$(MAKE) CFLAGS+="-std=$*" CVERSION:=$*

PREFIX?=/usr/local/
MANDIR?=share/man
VERSION:=$(shell cat VERSION)
SKIP_EXAMPLES?=

FILES_TO_INSTALL:=\
    $(DESTDIR)$(PREFIX)/bin/aceunit \
    $(DESTDIR)$(PREFIX)/include/aceunit.h \
    $(DESTDIR)$(PREFIX)/include/aceunit.mk \
    $(DESTDIR)$(PREFIX)/lib/libaceunit-abort.a \
    $(DESTDIR)$(PREFIX)/lib/libaceunit-fork.a \
    $(DESTDIR)$(PREFIX)/lib/libaceunit-setjmp.a \
    $(DESTDIR)$(PREFIX)/lib/libaceunit-simple.a \
    $(DESTDIR)$(PREFIX)/share/aceunit/nm.ac \
    $(DESTDIR)$(PREFIX)/share/aceunit/objdump.ac \
    $(DESTDIR)$(PREFIX)/share/aceunit/readelf.ac \
    $(if $(SKIP_EXAMPLES),,$(addprefix $(DESTDIR)$(PREFIX)/,$(shell find share/doc/aceunit -type f))) \
    $(DESTDIR)$(PREFIX)/$(MANDIR)/man1/aceunit.1 \
    $(DESTDIR)$(PREFIX)/$(MANDIR)/man3/aceunit.3

.PHONY: build
## build	Build the AceUnit library without running any tests.
build:
	$(MAKE) -C lib libs

.PHONY: install
## install:	Install AceUnit for the local system (Unix/POSIX/Cygwin/MinGW).
install: $(FILES_TO_INSTALL)

INSTALL_SCRIPT:=$(or $(BSD_INSTALL_SCRIPT),install)
INSTALL_DATA:=$(or $(BSD_INSTALL_DATA),install -m 644)

$(DESTDIR)$(PREFIX)/bin/aceunit: bin/aceunit
	install -d $(dir $@)
	$(INSTALL_SCRIPT) $^ $@

$(DESTDIR)$(PREFIX)/%: %
	install -d $(dir $@)
	$(INSTALL_DATA) $^ $@

$(DESTDIR)$(PREFIX)/include/aceunit.mk: include/aceunit.mk
	install -d $(dir $@)
	sed -e 's#$${PREFIX}#$(PREFIX)#' <$< >$@

lib/%:
	$(MAKE) -C lib/ $*

.PHONY: uninstall
## uninstall:	Remove AceUnit from the local system (Unix/POSIX/Cygwin/MinGW).
uninstall:
	$(RM) $(FILES_TO_INSTALL)

.PHONY: dist
## dist:	Creates source and binary distribution archives.
dist: dist-src dist-bin

.PHONY: dist-src
## dist-src:	Creates source distribution archives.
dist-src: archive:=aceunit-$(VERSION)-src
dist-src:
	mkdir -p dist-src/
	git archive -o dist-src/$(archive).tar --prefix $(archive)/ HEAD .
	<dist-src/$(archive).tar gzip  -9 >dist-src/$(archive).tar.gz
	<dist-src/$(archive).tar bzip2 -9 >dist-src/$(archive).tar.bz2
	<dist-src/$(archive).tar xz    -9 >dist-src/$(archive).tar.xz

.PHONY: dist-bin
## dist-bin:	Creates a binary distribution archive.
dist-bin: os:=$(shell uname -s)
dist-bin: hw:=$(shell uname -m)
dist-bin: archive:=aceunit-$(VERSION)-bin-$(os)-$(hw)
dist-bin: TARCFLAGS:=$(if $(filter bsdtar,$(firstword $(shell tar --version))),--uid=0 --gid=0,--owner=0 --group=0 --mode='og-w')
dist-bin:
	mkdir -p dist-bin/$(archive)/
	$(MAKE) DESTDIR=dist-bin/$(archive)/ PREFIX=/usr/ install
	tar $(TARCFLAGS) -c -f dist-bin/$(archive).tar -C dist-bin/ $(archive)/
	<dist-bin/$(archive).tar gzip  -9 >dist-bin/$(archive).tar.gz
	<dist-bin/$(archive).tar bzip2 -9 >dist-bin/$(archive).tar.bz2
	<dist-bin/$(archive).tar xz    -9 >dist-bin/$(archive).tar.xz

.PHONY: lint
## lint:	Runs linters on the project.
lint:
	shellcheck -x bin/aceunit

.PHONY: help
## help:		Print this help text.
help:
	@sed -En 's/^## ?//p' $(MAKEFILE_LIST)

.PHONY: debug
.ONESHELL: debug
debug:
	echo subs=$(subs)
	echo targets=$(targets)
	echo recurse_template='$(recurse_template)'

-include .User.mk
