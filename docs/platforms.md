# Platforms & Compilers

## Tested Compilers

| Compiler | Version | Standards tested |
|----------|---------|-----------------|
| GCC | 13, x86_64 | c90, c99, c11, c17, c2x, gnu90, gnu99, gnu11, gnu17, gnu2x |
| GCC (cross) | 12 | Multiple targets (see below) |
| Clang | 17.0.0 (macOS AArch64) | — |
| Clang | 18.1.3 (Linux x86_64) | — |

## Tested Hosted Environments

| Target | Notes |
|--------|-------|
| `aarch64-linux-gnu` | |
| `alpha-linux-gnu` | |
| `amd64-unknown-openbsd7.2` | |
| `arm-linux-gnueabi` | |
| `hppa-linux-gnu` | |
| `m68k-amigaos` | |
| `mips64-linux-gnuabi64` | |
| `mips-linux-gnu` | |
| `powerpc64le-linux-gnu` | |
| `powerpc64-linux-gnu` | |
| `powerpc-linux-gnu` | |
| `riscv64-linux-gnu` | |
| `s390x-linux-gnu` | |
| `x86-dos` | bcc (Bruce's C Compiler), via dosbox. Use `-t nm -b nm86 -s _` |
| `x86_64-unknown-linux-gnu` | |
| `x86_64-apple-darwin` | Run `./configure.sh` first; see macOS note |
| `x86_64-unknown-freebsd13.1` | |
| `x86_64-unknown-haiku` | |
| `x86_64-unknown-netbsd9.0` | NetBSD 9.3 |

## Planned / In-Progress Compilers

- GCC for: hppa64, i686, m68k, mips, sh4, sparc64
- Clang for: aarch64, arm, avr, hexagon, mips, mips64, thumb, wasm32, wasm64
- Keil / ARM ARMCC on: ARM7, Cortex-M0, Cortex-M3, SC000, SC100, SC300
- Keil C51 and C251 for 8051 / 80251
- Keil C166 for Infineon C16x / STMicroelectronics ST10
- Samsung ucc on Calm16 / SecuCalm
- Open64

## macOS Notes

The system `bash` on macOS (`/bin/bash`) is extremely old and does not support constructs used by `aceunit`. Fix this in one of two ways:

1. **Run `./configure.sh`** — automatically detects your OS and patches `bin/aceunit` to use `zsh`
2. **Install bash 5 via Homebrew** — `brew install bash`

## FreeBSD Notes

`objdump` is not installed by default on FreeBSD. Install `binutils`:

```sh
pkg install binutils
```

Alternatively, use `-t nm` or `-t readelf` when calling `aceunit`.

## Cross-Compilation

See [Cross-Compilation](cross-compilation.md) for details on building and testing across multiple targets.
