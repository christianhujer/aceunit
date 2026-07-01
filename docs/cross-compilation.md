# Cross-Compilation

AceUnit supports cross-compiling and testing for multiple target architectures. This is useful when your embedded target has different alignment, endianness, or word size than your development machine.

## Requirements

- `clang` (supports many targets without separate toolchain installs)
- `qemu-user` (to run cross-compiled binaries)
- GCC cross-compiler packages for specific targets

## How It Works

The `Makefile` in `lib/` is designed to be invoked from other directories. You pass `CC=<cross-compiler>` to build and test for a different target.

```sh
make CC=aarch64-linux-gnu-gcc
```

The `test/cross-hosted/` directory shows this pattern fully.

## Known Broken Targets

The following targets are excluded from the default cross-compilation suite:

| Target | Reason |
|--------|--------|
| `avr` | Compiles but no `qemu-user` support |
| `hppa64-linux-gnu` | Known broken (qemu/gcc bug) |
| `m68k-linux-gnu` | Known broken (qemu/gcc bug) |
| `sh4-linux-gnu` | Needs investigation |
| `sparc64-linux-gnu` | Known broken (qemu/gcc bug) |

When using `CC=clang`, additional targets are excluded:

| Target | Reason |
|--------|--------|
| `alpha-linux-gnu` | Clang does not support Alpha AXP |
| `hppa-linux-gnu` | Clang does not support HP/PA-RISC |
| `hppa64-linux-gnu` | Clang does not support HP/PA-RISC 64-bit |
| `sh4-linux-gnu` | Clang does not support SH4 |

!!! note "m68k on Ubuntu"
    m68k is supported in Clang/LLVM 13 and 15 but **not** in Clang/LLVM 14 on Ubuntu.

## Example: Testing for Multiple Targets in Parallel

```sh
cd test/cross-hosted
make                    # GCC default targets
make CC=clang           # Clang targets
```

## Using AceUnit in a Cross-Compilation Project

When testing firmware for an embedded target, you typically run the tests on the host machine (not on the target). The key is to build your production code for the target and your test code for the host, then link against the host AceUnit library.

Pattern:

```makefile
CROSS_CC=arm-none-eabi-gcc
HOST_CC=gcc

# Build production code for target
module.target.o: module.c
	$(CROSS_CC) -c $< -o $@

# Build test code for host
module_test.o: module_test.c
	$(HOST_CC) -I$(ACEUNIT_HOME)/include -c $< -o $@

# Generate and run tests on host
testcases.c: module_test.o
	$(ACEUNIT_HOME)/bin/aceunit $^ >$@

module_test: module.o module_test.o testcases.o
	$(HOST_CC) $^ -L$(ACEUNIT_HOME)/lib -laceunit-fork -o $@
```

This tests your C logic on the host while building the final firmware for the target.
