# SimpleRunner

**Library:** `libaceunit-simple.a`

The SimpleRunner executes test cases without any error interception. If a test case fails (via `AceUnit_fail()`), which internally calls `abort()`, execution stops immediately.

## When to Use

- Learning TDD for the first time
- Environments with no `<setjmp.h>` and no POSIX
- Quick prototyping where stopping on first failure is acceptable

## Limitations

- Stops at the first failure — no summary of total test count vs. failures
- Does not catch `SIGSEGV`, `SIGABRT`, or any other signal
- Not suitable for production CI where you want full failure reports

## Linking

```sh
cc *.o testcases.o -laceunit-simple -o tests
```

```makefile
LOADLIBES=-laceunit-simple
```
