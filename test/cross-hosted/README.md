# AceUnit Cross-Compilation Test Suite
Compile and test AceUnit with different compilers and on different CPUs.

Requires clang and qemu.

## Broken targets

The following targets are known to be broken and excluded:
* `avr` (compiles but doesn't run due to lack of qemu-user support and lack of simulator setup)
* `hppa64-linux-gnu` (known to be broken, see https://github.com/christianhujer/cross-and-qemu-smoketest)
* `m68k-linux-gnu` (known to be broken, see https://github.com/christianhujer/cross-and-qemu-smoketest)
* `sh4-linux-gnu` (needs investigation)
* `sparc64-linux-gnu` (known to be broken, see https://github.com/christianhujer/cross-and-qemu-smoketest)
