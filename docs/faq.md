# FAQ & Troubleshooting

## "declare: -g: invalid option"

```
./aceunit: line 3: declare: -g: invalid option
```

Your system `bash` is too old. AceUnit requires bash 5, ksh, or zsh.

**Fix on macOS:** Run `./configure.sh` to switch `aceunit` to `zsh`, or install bash 5:

```sh
brew install bash
```

**Fix on other systems:** Install bash 5 or ensure `ksh` or `zsh` is on your `PATH`.

## `objdump: command not found` on FreeBSD / BSD

`objdump` is not installed by default on BSD systems.

Option 1: Install binutils:

```sh
pkg install binutils       # FreeBSD
pkg_add binutils           # OpenBSD
```

Option 2: Use `nm` instead:

```sh
aceunit -t nm *_test.o >testcases.c
```

## My test functions are not discovered

Check that:

1. Function names start with `test` (lowercase): `testFoo`, `testBar`
2. Functions are compiled into the object file you passed to `aceunit`
3. Functions have external linkage (not `static`)
4. If using a custom prefix, you passed `-p PREFIX` to `aceunit`

Verify symbols are present:

```sh
nm leapyear_test.o | grep test
```

## Using a custom prefix

If your project uses a module prefix like `HeapTest_`:

```sh
aceunit -p 'HeapTest_' heap_test.o >testcases.c
```

AceUnit will discover functions like `HeapTest_beforeAll`, `HeapTest_testAllocate`, etc.

## Tests stop at first failure

You are probably using `SimpleRunner`. Switch to a runner that continues after failure:

- For POSIX hosts: link with `-laceunit-fork`
- For embedded: link with `-laceunit-setjmp`
- For Windows/non-POSIX hosts: link with `-laceunit-abort`

See [Runners](runners/index.md).

## `SIGSEGV` crashes the test runner

Use `ForkRunner` (`-laceunit-fork`). It runs each test case in a child process, so a crash terminates the child but not the runner. Other runners do not catch signals.

## Linking with a program that has its own `main()`

Use `__wrap_main()` and link with `--wrap=main`:

```sh
cc *.o testcases.o -laceunit-fork -Wl,--wrap=main -o tests
```

See [`__wrap_main()` in the API reference](api-reference.md).

## How do I test a function that calls `puts()` or other I/O?

See the [Hello World examples](examples/hello-world.md) — five different approaches to mocking or intercepting I/O side effects.

## Can I use `<assert.h>` instead of `<aceunit.h>`?

Yes, with AbortRunner or ForkRunner. The system `assert()` calls `abort()`, which both of those runners handle. SetJmpRunner and SimpleRunner will not catch it correctly — use `<aceunit.h>` with those.

## How do I install AceUnit into my project (not system-wide)?

```sh
make install PREFIX=/path/to/myproject/third_party/aceunit
```

Then in your Makefile:

```makefile
ACEUNIT_HOME=/path/to/myproject/third_party/aceunit
ACEUNIT=$(ACEUNIT_HOME)/bin/aceunit
ACEUNIT_LIBRARY=$(ACEUNIT_HOME)/lib/libaceunit-fork.a
CPPFLAGS+=-I$(ACEUNIT_HOME)/include
```

## Multiple fixtures — how do I combine them?

Pass all test object files to `aceunit` at once:

```sh
aceunit module1_test.o module2_test.o >testcases.c
```

`testcases.c` will contain a fixture entry for each object file.
