# Example: Leap Year

The leap year example is the simplest possible AceUnit project: a pure, side-effect-free function tested with no mocking needed.

Source: `examples/leapyear/` in the repository.

## The Module Under Test

```c title="leapyear.h"
#ifndef LEAPYEAR_H
#define LEAPYEAR_H
#include <stdbool.h>

extern bool isLeapYear(int year);
#endif
```

```c title="leapyear.c"
#include "leapyear.h"

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
```

## The Tests

```c title="leapyear_test.c"
#include "leapyear.h"
#include <assert.h>

void testLeapYears(void) {
    assert(isLeapYear(0));
    assert(isLeapYear(4));
    assert(isLeapYear(400));
}

void testNonLeapYears(void) {
    assert(!isLeapYear(1));
    assert(!isLeapYear(100));
}
```

No includes from AceUnit. Just `<assert.h>` and the header under test. AceUnit discovers `testLeapYears` and `testNonLeapYears` by their names.

## The Makefile

```makefile title="Makefile"
ACEUNIT_HOME=../..
ACEUNIT:=$(ACEUNIT_HOME)/bin/aceunit
CPPFLAGS:=-W -Wall -pedantic -I$(ACEUNIT_HOME)/include
ACEUNIT_LIBRARY:=$(ACEUNIT_HOME)/lib/libaceunit-fork.a

.PHONY: all
all: test

leapyear_test: leapyear_test.o leapyear.o testcases.o $(ACEUNIT_LIBRARY)

.PHONY: test
test: leapyear_test
	./$^

testcases.c: leapyear_test.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] leapyear_test testcases.c
```

## Running

```sh
cd examples/leapyear
make
```

Expected output:

```
AceUnit: 2 test cases, 2 successful, 0 failed.
```

## Key Takeaways

- Test functions need no registration — just name them `test*`
- You can use `<assert.h>` directly (with ForkRunner or AbortRunner)
- `testcases.c` is auto-generated; never edit it manually
- The `$(ACEUNIT_LIBRARY)` dependency ensures AceUnit is built before the test
