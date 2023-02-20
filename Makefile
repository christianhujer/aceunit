#subs:=lib test examples #$(patsubst %/Makefile,%,$(wildcard */Makefile))

include recurse.mk

test-all examples-all install: lib-all

versions:=c90 c99 c11 c17 c2x gnu90 gnu99 gnu11 gnu17 gnu2x
compiler-test: $(versions:%=compiler-test-%)

compiler-test-%:
	$(MAKE) clean
	$(MAKE) CFLAGS+=-std=$*

PREFIX?=/usr/local/

FILES_TO_INSTALL:=\
    $(PREFIX)/share/man/man1/aceunit.1 \
    $(PREFIX)/share/man/man3/aceunit.3 \
    $(PREFIX)/bin/aceunit \
    $(PREFIX)/lib/libaceunit-simple.a \
    $(PREFIX)/lib/libaceunit-abort.a \
    $(PREFIX)/lib/libaceunit-setjmp.a \
    $(PREFIX)/lib/libaceunit-fork.a \
    $(PREFIX)/include/aceunit.h

.PHONY: install
install: $(FILES_TO_INSTALL)

$(PREFIX)/%: %
	install $^ $@

.PHONY: install
uninstall:
	$(RM) $(FILES_TO_INSTALL)
