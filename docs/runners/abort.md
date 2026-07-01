# AbortRunner

**Library:** `libaceunit-abort.a`

The AbortRunner extends SetJmpRunner with a `SIGABRT` signal handler. When a test case calls `abort()` (including through the system's `<assert.h>`), the signal handler performs a `longjmp()` back to the runner.

## When to Use

- Hosted environments without POSIX `fork()`: Windows, AmigaOS, MS-DOS
- When you want to use the system's `<assert.h>` and its output format
- Good general-purpose choice for hosted non-POSIX development

## How It Works

```
runner installs SIGABRT handler, calls setjmp()
  → calls test case
    → assert() from <assert.h> fails → abort() → SIGABRT
    → signal handler performs longjmp() back to runner
  → runner marks test failed, restores signal handler, moves to next test case
```

## Assertion Compatibility

Works with:

- `<aceunit.h> assert()` — calls `AceUnit_fail()` → `abort()` → caught
- `<assert.h> assert()` — calls `abort()` → caught
- `<stdlib.h> abort()` — caught

Does **not** work with:

- `<stdlib.h> exit()` — not a signal; process exits
- Signals other than `SIGABRT` (like `SIGSEGV`)

## Linking

```sh
cc *.o testcases.o -laceunit-abort -o tests
```

```makefile
LOADLIBES=-laceunit-abort
```
