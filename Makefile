vpath %.c src/loggers/ src/
#CFLAGS+=-g -std=c11 -W -Wall -pedantic -Werror -Wno-unused-label -pg --coverage
CFLAGS+=-g -std=c11 -W -Wall -pedantic -Werror -Wno-unused-label
CPPFLAGS+=-Iinclude/ -DACEUNIT_SUITES

.PHONY: all
## Performs all self-checks.
all: prjcheck libaceunit.a
libaceunit.a: libaceunit.a(AceUnitMainHosted.o AceUnitData.o AceUnit.o FullPlainLogger.o)

.PHONY: prjcheck
prjcheck:
	! grep -Rn ' $$' src include generator --include="*.[ch]" --include="*.java" --include="Makefile" --include="*.mak"

.PHONY: clean
clean::
	$(RM) libaceunit.a


PREFIX:=/usr/local/
LIBDIR:=$(PREFIX)/lib/
INCDIR:=$(PREFIX)/include/

install: libaceunit.a
	install -m 644 libaceunit.a $(LIBDIR)
	install -d $(INCDIR)/aceunit/
	install -m 644 include/*.h $(INCDIR)/aceunit/
