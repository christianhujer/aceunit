# AceUnit Cross-Compilation Test Suite
Compile and test AceUnit with different compilers and on different CPUs.

Requires clang and qemu.

## Broken targets

For `make`, the following targets are known to be broken and excluded:
* `avr` (compiles but doesn't run due to lack of qemu-user support and lack of simulator setup)
* `hppa64-linux-gnu` (known to be broken, see https://github.com/christianhujer/cross-and-qemu-smoketest)
* `m68k-linux-gnu` (known to be broken, see https://github.com/christianhujer/cross-and-qemu-smoketest)
* `sh4-linux-gnu` (needs investigation)
* `sparc64-linux-gnu` (known to be broken, see https://github.com/christianhujer/cross-and-qemu-smoketest)

For `make CC=clang`, the following targets are excluded in addition to the above:
* `alpha-linux-gnu` because clang doesn't support Alpha AXP.
* `hppa-linux-gnu` because clang doesn't support HP/PA-RISC.
* `hppa64-linux-gnu` because clang doesn't support HP/PA-RISC 64-Bit.
* `sh4-linux-gnu` because clang doesn't support SH4.

Note that on Ubuntu, m68k is supported in Clang/LLVM 15 and Clang/LLVM 13 but not in Clang/LLVM 14.
