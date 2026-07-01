# Getting Started

This guide gets you from zero to a passing test suite in about 5 minutes.

## Prerequisites

- `bash` 5, `ksh`, or `zsh`
- GNU `make` 3.81 or newer (often `gmake` on BSD)
- A C compiler (`gcc`, `clang`, or similar)
- `objdump`, `readelf`, or `nm` (usually part of `binutils`)

!!! note "macOS"
    `/bin/bash` on macOS is very old. Run `./configure.sh` to switch `aceunit` to `zsh`, or install a newer bash via Homebrew.

## Step 1: Build and Install AceUnit

```sh
git clone https://github.com/christianhujer/aceunit
cd aceunit
make
sudo make install          # installs to /usr/local/
```

To install elsewhere:

```sh
sudo make install PREFIX=/opt/aceunit/
```

## Step 2: Write a Module

Create the module you want to test.

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

## Step 3: Write Tests

Name your test functions starting with `test`. No registration needed.

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

## Step 4: Build and Run

```sh
# Compile
cc -c leapyear.c
cc -c leapyear_test.c

# Generate fixture table from object files
aceunit leapyear_test.o >testcases.c

# Compile fixture table
cc -c testcases.c

# Link with AceUnit runner
cc leapyear.o leapyear_test.o testcases.o -laceunit-fork -o leapyear_test

# Run
./leapyear_test
```

Expected output:

```
AceUnit: 2 test cases, 2 successful, 0 failed.
```

## Step 5: Add a Makefile

```makefile title="Makefile"
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

Now just run `make` to build and test.

## Next Steps

- Learn the [lifecycle and concepts](concepts.md)
- Choose the right [runner](runners/index.md) for your environment
- See the complete [leapyear example](examples/leapyear.md) with explanations
