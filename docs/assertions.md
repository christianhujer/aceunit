# Assertions

## How Assertions Work

AceUnit tests fail by calling `AceUnit_fail()`. The `assert()` macro provided by `<aceunit.h>` calls it automatically when a condition is false.

```c
#include <aceunit.h>

void testSomething(void) {
    assert(1 + 1 == 2);   // passes
    assert(1 + 1 == 3);   // calls AceUnit_fail()
}
```

On a hosted environment, `assert()` also prints the failing condition and location to `stderr` before failing.

## Assertion vs Runner Compatibility

Not every assertion mechanism works with every runner. This table shows what each runner supports:

| Assertion | SimpleRunner | SetJmpRunner | AbortRunner | ForkRunner |
|-----------|:---:|:---:|:---:|:---:|
| `<aceunit.h> assert()` | stop | ✓ | ✓ | ✓ |
| `<assert.h> assert()` | stop | ✗ | ✓ | ✓ |
| `<stdlib.h> abort()` | stop | ✗ | ✓ | ✓ |
| `<stdlib.h> exit()` | stop | ✗ | ✗ | ✓ |
| `<setjmp.h> longjmp()` | ✗ | ✓ | ✓ | ✗ |
| Abnormal termination (`SIGSEGV`, etc.) | ✗ | ✗ | ✗ | ✓ |

Legend:

- **✓** — Runner catches this; test is marked failed and execution continues.
- **stop** — Runner detects failure but does not continue to next test case.
- **✗** — Runner does not handle this; test execution aborts entirely.

## Choosing the Right Assertion Style

**Embedded / freestanding with `setjmp.h`:** Use `<aceunit.h>` assert with SetJmpRunner. `longjmp()` provides the non-local exit.

**Hosted POSIX:** Use `<assert.h>` with ForkRunner. Each test case runs in a child process; even `SIGSEGV` is caught.

**Hosted non-POSIX (Windows, AmigaOS, MS-DOS):** Use AbortRunner. `SIGABRT` is caught via a signal handler.

**Quick start / learning TDD:** SimpleRunner works fine. It stops on first failure, which is acceptable early on.

## `AceUnit_fail()`

You can call `AceUnit_fail()` directly to fail a test case unconditionally:

```c
void testUnreachable(void) {
    if (should_not_happen()) {
        AceUnit_fail();
    }
}
```

The exact mechanism used by `AceUnit_fail()` depends on the linked runner library:

- `libaceunit-simple.a` — calls `abort()`
- `libaceunit-setjmp.a` — calls `longjmp()`
- `libaceunit-abort.a` — calls `abort()` (caught by signal handler)
- `libaceunit-fork.a` — calls `abort()` (caught via child process exit status)
