# Makefile Integration

AceUnit is designed to integrate naturally with GNU Make. This page shows common patterns.

## Minimal Makefile

```makefile
ACEUNIT_LIBRARY=-laceunit-fork
CPPFLAGS+=-W -Wall -pedantic

.PHONY: all
all: test

leapyear_test: leapyear.o leapyear_test.o testcases.o
	$(CC) $^ $(ACEUNIT_LIBRARY) -o $@

testcases.c: leapyear_test.o
	aceunit $^ >$@

.PHONY: test
test: leapyear_test
	./$^

.PHONY: clean
clean:
	$(RM) *.o leapyear_test testcases.c
```

## Using `aceunit.mk`

AceUnit ships with `include/aceunit.mk` which provides reusable variables and patterns. After installation it is available at `$(PREFIX)/include/aceunit.mk`.

```makefile
include /usr/local/include/aceunit.mk

CPPFLAGS+=-W -Wall -pedantic
ACEUNIT_LIBRARY=$(ACEUNIT_SETJMP_LIBRARY)   # or FORK, ABORT, SIMPLE

.PHONY: all
all: test

mymodule_test: mymodule.o mymodule_test.o testcases.o $(ACEUNIT_LIBRARY)

testcases.c: mymodule_test.o
	$(ACEUNIT) $^ >$@

.PHONY: test
test: mymodule_test
	./$^
```

## Bundled AceUnit (in-project)

When AceUnit is not installed system-wide, point `ACEUNIT_HOME` at the source tree:

```makefile
ACEUNIT_HOME=../../aceunit
ACEUNIT=$(ACEUNIT_HOME)/bin/aceunit
ACEUNIT_LIBRARY=$(ACEUNIT_HOME)/lib/libaceunit-fork.a
CPPFLAGS+=-I$(ACEUNIT_HOME)/include

.PHONY: all
all: test

mymodule_test: mymodule.o mymodule_test.o testcases.o $(ACEUNIT_LIBRARY)

$(ACEUNIT_LIBRARY):
	$(MAKE) -C $(ACEUNIT_HOME)/lib

testcases.c: mymodule_test.o
	$(ACEUNIT) $^ >$@

.PHONY: test
test: mymodule_test
	./$^

.PHONY: clean
clean:
	$(RM) *.o mymodule_test testcases.c
```

## Multiple Fixtures

When you have many test object files, use pattern rules and `patsubst`:

```makefile
ACEUNIT_HOME=../../aceunit
ACEUNIT=$(ACEUNIT_HOME)/bin/aceunit
ACEUNIT_LIBRARY=$(ACEUNIT_HOME)/lib/libaceunit-fork.a
CPPFLAGS+=-I$(ACEUNIT_HOME)/include

sources=$(wildcard *.c)
objects=$(patsubst %.c,%.o,$(sources))
test_objects=$(filter %_test.o,$(objects))
prod_objects=$(filter-out %_test.o,$(objects))

testcases.c: $(test_objects)
	$(ACEUNIT) $^ >$@

unittest: $(prod_objects) $(test_objects) testcases.o $(ACEUNIT_LIBRARY)

.PHONY: test
test: unittest
	./unittest
```

## Recursive Builds

For projects with multiple subdirectories, AceUnit provides `recurse.mk`. See `recurse.mk` in the repository root for details.

## Cross-Compilation

See [Cross-Compilation](cross-compilation.md) for how to use AceUnit with different compilers and target architectures in the same build.
