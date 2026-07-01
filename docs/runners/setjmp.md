# SetJmpRunner

**Library:** `libaceunit-setjmp.a`

The SetJmpRunner wraps each test case with `setjmp()`/`longjmp()`. When a test case calls `AceUnit_fail()`, it performs a `longjmp()` back to the runner, which marks the test failed and continues to the next one.

## When to Use

- Embedded / freestanding environments that provide `<setjmp.h>`
- Any environment without POSIX `fork()`
- The default choice for embedded development

## How It Works

```
runner calls setjmp()
  → calls test case
    → test fails → AceUnit_fail() → longjmp() back to runner
  → runner marks test failed, moves to next test case
```

## Assertion Compatibility

Works with:

- `<aceunit.h> assert()` — the primary choice; calls `AceUnit_fail()` → `longjmp()`
- `<setjmp.h> longjmp()` — directly supported

Does **not** work with:

- `<assert.h> assert()` — calls `abort()`, not `longjmp()`; will terminate the process
- Signals (`SIGSEGV`, `SIGABRT`)

## Linking

```sh
cc *.o testcases.o -laceunit-setjmp -o tests
```

```makefile
LOADLIBES=-laceunit-setjmp
```
