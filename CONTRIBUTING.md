# Contributing to AceUnit

## General
- Follow the [Code of Conduct](CODE_OF_CONDUCT.md).
- Make sure that you are allowed to contribute.
  If you're employed, and in doubt, check with your employer or a lawyer.
- Make sure you understand and accept the [License](LICENSE).

> If you are unsure about the general section of these guidelines, check with your employer or a lawyer.

## Quality
- Make sure there is no regression.
  There is an extensive suite of tests.
  Run `make` to build and run them; run `make compiler-test` to test against multiple C standard versions before submitting a pull request.
- If you fix a bug, prevent regression by reproducing it first with a test.
- If you add a new feature, make sure it's tested.
- AceUnit uses 1TBS style with 4 spaces indentation, Unix format.
  That means no tabs (except for recipes in `Makefile`s), no CRLF, curly braces open at the end of the line.
- Follow the [SEI CERT C Coding Standard](https://wiki.sei.cmu.edu/confluence/display/c/SEI+CERT+C+Coding+Standard).
- For local-only Makefile overrides (e.g. `CC`, `CFLAGS`), use a `.User.mk` file in the repository root; it's git-ignored and automatically included.

> If you are unsure about the quality section of these guidelines, you can still submit a pull request.
> You will receive help to meet the quality guidelines.
