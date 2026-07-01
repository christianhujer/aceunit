# ForkRunner

**Library:** `libaceunit-fork.a`

The ForkRunner executes each test function in a separate child process using POSIX `fork()`. A test is marked failed if the child process exits with a non-zero status or is terminated by a signal.

## When to Use

- POSIX environments: Linux, macOS, BSD, Haiku, Solaris
- Best isolation: a `SIGSEGV` in a test does not crash the runner
- When you want to detect crashes, infinite loops (with timeout), or calls to `exit()`

## How It Works

```
for each fixture function:
  fork() → child runs the function
  parent waits for child
  if child exited != 0 or killed by signal → mark failed
```

## Assertion Compatibility

Works with everything:

- `<aceunit.h> assert()` ✓
- `<assert.h> assert()` ✓
- `<stdlib.h> abort()` ✓
- `<stdlib.h> exit()` ✓
- Abnormal termination (`SIGSEGV`, `SIGBUS`, etc.) ✓

Does **not** need or use `longjmp()` — the child process provides isolation.

## Note on `longjmp()`

The ForkRunner does not support `longjmp()` as an assertion mechanism — and there is no need to. `longjmp()` exists in other runners as a workaround for lacking process isolation. With `fork()`, that isolation is native.

## Linking

```sh
cc *.o testcases.o -laceunit-fork -o tests
```

```makefile
LOADLIBES=-laceunit-fork
```
