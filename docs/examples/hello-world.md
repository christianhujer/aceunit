# Example: Hello World

Unit-testing `hello, world!` sounds trivial but poses real challenges:

1. The program has a `main()` function — which conflicts with the test runner's `main()`
2. `puts()` is a side-effect — the test must intercept or mock it

AceUnit includes five examples that solve these challenges in different ways. Source: `examples/hello_world_*/` in the repository.

## The Program Under Test

All five examples test this same program:

```c title="hello.c"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    puts("Hello, world!");
    return EXIT_SUCCESS;
}
```

---

## Variant 1: `hello_world_mocked_macro`

**How:** Compile-time macros redirect `main` and `puts` to different names.

- `-Dmain=original_main` renames `main` at compile time
- `-Dputs=mocked_puts` redirects `puts` to a mock at compile time

**Pros:** Simple, portable, no `objcopy` needed  
**Cons:** Requires recompiling the source with special flags (not always possible)

```c title="hello_test.c"
#include "mock_puts.h"

extern int original_main(void);

void test_hello(void) {
    original_main();
    assert_puts("Hello, world!\n");
}
```

---

## Variant 2: `hello_world_mocked_obj`

**How:** `objcopy` renames symbols in the compiled object file.

- `main` → `original_main`
- `puts` → `mocked_puts`

The mock provides `mocked_puts` (collects output into a buffer) and `assert_puts` (verifies the buffer).

**Pros:** No source modification needed; works on pre-compiled objects  
**Cons:** Requires GNU `objcopy`

---

## Variant 3: `hello_world_mocked_link`

**How:** GNU linker `--wrap` feature redirects `puts` at link time.

- `hello.o` is processed with `objcopy` to rename `main` → `real_main`
- `puts` is redirected to `__wrap_puts` via `-Wl,--wrap=puts`

**Pros:** No source modification; linker-level interception  
**Cons:** GNU/Clang toolchain only; does not work on macOS (Darwin linker)

---

## Variant 4: `hello_world_mocked_interpose`

**How:** Darwin/macOS `DYLD_INSERT_LIBRARIES` interposer overrides `puts` at runtime.

- `main` renamed with `objcopy`/`llvm-objcopy`
- `puts` intercepted at runtime via dyld interposer

**Pros:** macOS-native approach; no source changes  
**Cons:** macOS only; requires `llvm-objcopy`

!!! note "Finding llvm-objcopy on macOS"
    If `llvm-objcopy` is not found, check where LLVM is installed:
    ```sh
    export PATH=$(brew --prefix llvm)/bin:$PATH
    ```

---

## Variant 5: `hello_world_intercepted_obj`

**How:** Intercepts stdout/stderr using a pipe instead of mocking `puts`.

- `main` renamed with `objcopy`
- Test redirects stdout before calling `original_main()`, reads the output, asserts it

**Pros:** No mock needed; tests real I/O behavior  
**Cons:** More complex test code; pipe setup required

---

## Choosing a Variant

| Variant | Portability | Source changes needed | Toolchain requirement |
|---------|-------------|----------------------|-----------------------|
| `mocked_macro` | High | Yes (recompile with flags) | Any C compiler |
| `mocked_obj` | Medium | No | GNU `objcopy` |
| `mocked_link` | Medium | No | GNU/Clang linker |
| `mocked_interpose` | Low (macOS) | No | LLVM + Darwin loader |
| `intercepted_obj` | Medium | No | GNU `objcopy` |

For most Linux/embedded projects, `mocked_obj` or `mocked_macro` is the pragmatic choice.
