# AceUnit

**Advanced C and Embedded Unit Test Framework**

AceUnit is a comfortable, portable unit test framework for C — in the best tradition of xUnit frameworks like JUnit 5.
Its target audience: developers writing firmware, drivers, operating systems, and other C programs who want test discovery without framework noise.

```c
#include <aceunit.h>

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

Run it:

```
AceUnit: 2 test cases, 2 successful, 0 failed.
```

No registration macros. No test lists to maintain. AceUnit discovers tests automatically from object files.

---

## Why AceUnit?

| Feature | AceUnit | Check | Unity | CUnit |
|---------|---------|-------|-------|-------|
| Test discovery (no registration) | ✓ | ✗ | ✗ | ✗ |
| No macro noise in test code | ✓ | ✗ | ✗ | ✗ |
| Freestanding / bare-metal support | ✓ | ✗ | ✓ | ✗ |
| C89 through C23 | ✓ | ✗ | ✓ | ✗ |
| Multiple runners (simple/setjmp/abort/fork) | ✓ | ✗ | ✗ | ✗ |
| No Java / external toolchain needed | ✓ (shell script) | ✓ | ✓ | ✓ |

## Key Features

- **JUnit 5-style naming** — `beforeAll`, `beforeEach`, `test*`, `afterEach`, `afterAll`
- **Automatic test discovery** — no `REGISTER_TEST` macros; `aceunit` reads object files via `nm`/`objdump`/`readelf`
- **Tiny footprint** — suitable for extremely resource-constrained environments
- **Four runners** — Simple, SetJmp, Abort, Fork; pick what fits your environment
- **C89–C23** — works with ancient compilers on ancient hardware
- **Broad compiler support** — GCC, Clang, Keil, and more
- **POSIX and bare-metal** — same tests, different runner

## Quick Install

```sh
git clone https://github.com/christianhujer/aceunit
cd aceunit
make
sudo make install
```

Then [get started →](getting-started.md)
