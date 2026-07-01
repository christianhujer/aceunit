# Contributing

## General Guidelines

- Follow the [Code of Conduct](https://github.com/christianhujer/aceunit/blob/trunk/CODE_OF_CONDUCT.md).
- Make sure you are allowed to contribute. If you are employed and unsure, check with your employer or a lawyer.
- Make sure you understand and accept the [License](https://github.com/christianhujer/aceunit/blob/trunk/LICENSE).

## Quality Standards

**No regressions.** AceUnit has an extensive test suite. Run `make` before submitting a PR and ensure all tests pass.

**Bug fixes require a reproducing test.** Write a failing test that demonstrates the bug, then fix it.

**New features must be tested.** TDD is the expected workflow.

**Code style:** 1TBS with 4-space indentation, Unix line endings.

- No tabs in C files (tabs are fine in `Makefile` recipes)
- No CRLF
- Curly braces open at end of line (`{` on the same line as `if`, `for`, function signature)

**Follow the [SEI CERT C Coding Standard](https://wiki.sei.cmu.edu/confluence/display/c/SEI+CERT+C+Coding+Standard).**

If you are unsure about any quality requirement, submit the PR anyway. You will receive guidance.

## Development Setup

```sh
git clone https://github.com/christianhujer/aceunit
cd aceunit
make        # build and run all tests
```

## Running Tests

```sh
make        # builds everything and runs tests
make test   # runs tests only (if already built)
```

## Cross-Compilation Tests

To run the cross-hosted test suite (requires `clang` and `qemu`):

```sh
cd test/cross-hosted
make
```

## Reporting Bugs

Open an issue at: <https://github.com/christianhujer/aceunit/issues>

## Security Issues

AceUnit is a development-only tool and is not intended to be shipped in production systems. If you find a security vulnerability, treat it as a bug and report it via the issue tracker. See [SECURITY.md](https://github.com/christianhujer/aceunit/blob/trunk/SECURITY.md) for details.
