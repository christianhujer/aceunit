vpath %.c src/loggers/ src/
CFLAGS+=-g -std=c11 -W -Wall -pedantic -Werror -Wno-unused-label -pg --coverage
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
