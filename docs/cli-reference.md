# CLI Reference

## Synopsis

```
aceunit [OPTION]... [OBJECT_FILE]...
```

Scans object files for test cases and writes the generated fixtures table to stdout.

## Options

`-b BINARY`
: Use `BINARY` instead of the default binary for the selected tool.
  Example: `-b m68k-amigaos-objdump`

`-h`
: Display help text and exit.

`-n NAME`
: Use `NAME` instead of `fixtures` as the symbol name for the fixture table.

`-p PATTERN`
: Match test functions with the prefix `PATTERN`. `PATTERN` is passed to `grep`.
  Example: `-p '[^_\+]_'` to allow any module prefix followed by an underscore.

`-s PATTERN`
: Strip `PATTERN` from symbol names before processing. `PATTERN` is passed to `grep`.
  Example: `-s _` to strip a leading underscore (needed for some toolchains like `bcc`).

`-t TOOL`
: Use `TOOL` to display symbol tables. Defaults to `objdump`.
  Built-in options: `nm`, `objdump`, `readelf`.

`-v`
: Print version information and exit.

## Examples

Scan all test object files and write fixtures to `aceunit.c`:

```sh
aceunit -p '[^_]\+_' *_test.o >aceunit.c
```

Use `nm` with a cross-compiler binary, stripping leading underscores:

```sh
aceunit -t nm -b m68k-amigaos-nm -s _ *_test.o >aceunit.c
```

Use `readelf` with explicit object files:

```sh
aceunit -t readelf a.o b.o c.o >aceunit.c
```

For `bcc` (Bruce's C Compiler) targeting x86-DOS:

```sh
aceunit -t nm -b nm86 -s _ *_test.o >aceunit.c
```

## Dependencies

`aceunit` requires one of: `objdump`, `readelf`, or `nm`.

## Limitations

`aceunit` cannot read from `stdin`. This is a limitation of the downstream tools (`nm`, `objdump`, `readelf`) which require actual file paths.

## Shell Compatibility

The `aceunit` script requires `bash` 5, `ksh`, or `zsh`. On macOS, the system `bash` at `/bin/bash` is too old. Run `./configure.sh` to switch to `zsh`, or install a newer bash via Homebrew.
