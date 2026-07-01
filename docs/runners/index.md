# Runners

A **runner** is the part of AceUnit that calls test functions and handles failures. You select a runner by linking against the corresponding static library.

## Which Runner Should I Use?

```
Are you on a freestanding / bare-metal environment?
├─ Yes → Does your environment provide <setjmp.h>?
│        ├─ Yes → SetJmpRunner  (libaceunit-setjmp.a)
│        └─ No  → SimpleRunner  (libaceunit-simple.a)
└─ No (hosted) → Does your OS support fork()?
                 ├─ Yes (Linux, macOS, BSD, etc.) → ForkRunner   (libaceunit-fork.a)
                 └─ No  (Windows, AmigaOS, DOS)  → AbortRunner  (libaceunit-abort.a)
```

## Comparison

| Runner | Library | Continues after fail | Catches SIGABRT | Catches SIGSEGV | Requires POSIX |
|--------|---------|:---:|:---:|:---:|:---:|
| Simple | `libaceunit-simple.a` | ✗ | ✗ | ✗ | ✗ |
| SetJmp | `libaceunit-setjmp.a` | ✓ | ✗ | ✗ | ✗ |
| Abort | `libaceunit-abort.a` | ✓ | ✓ | ✗ | ✗ (needs `signal()`) |
| Fork | `libaceunit-fork.a` | ✓ | ✓ | ✓ | ✓ |

## Detailed Guides

- [SimpleRunner](simple.md)
- [SetJmpRunner](setjmp.md)
- [AbortRunner](abort.md)
- [ForkRunner](fork.md)
