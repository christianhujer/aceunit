# Migration Guide

This guide helps users of AceUnit v1 and v2 migrate to v3.

## What Changed

### Generator

| | v1 / v2 | v3 |
|-|---------|----|
| Generator | Java program parsing source files | Shell script reading object file symbol tables |
| Discovery | Fake annotations (`A_Test`, `A_Before`, etc.) | Naming convention (`test*`, `beforeEach`, etc.) |
| Dependency | Java runtime required | `bash`/`ksh`/`zsh` + `nm`/`objdump`/`readelf` |

### Naming

| v1 / v2 | v3 |
|---------|----|
| `A_Before` | `beforeEach` |
| `A_BeforeClass` | `beforeAll` |
| `A_After` | `afterEach` |
| `A_AfterClass` | `afterAll` |
| `A_Test` | `test` prefix (no annotation) |

### Runner

v3 has a modular runner. Choose by linking against the appropriate library:

- `libaceunit-simple.a`
- `libaceunit-setjmp.a`
- `libaceunit-abort.a`
- `libaceunit-fork.a`

### Template

v1/v2 used JUnit 4 as the template. v3 is modelled after JUnit 5.

## Migration Steps

### Step 1: Rename Lifecycle Functions

Rename functions in all test files:

| Find | Replace with |
|------|--------------|
| Functions annotated `A_Before` | Rename to `beforeEach` |
| Functions annotated `A_BeforeClass` | Rename to `beforeAll` |
| Functions annotated `A_After` | Rename to `afterEach` |
| Functions annotated `A_AfterClass` | Rename to `afterAll` |
| Functions annotated `A_Test` | Add `test` prefix |

You do not need to remove the old annotations at this stage. After renaming, both v2 and v3 can run the tests in parallel — which is useful for a gradual migration.

### Step 2: Install v3

```sh
git clone https://github.com/christianhujer/aceunit
cd aceunit
make
sudo make install
```

### Step 3: Run Tests with v3

Point your build at the v3 `aceunit` binary and one of the new libraries. Verify all tests still pass.

### Step 4: Remove Old Annotations

Once v3 is working, remove the old `A_Test`, `A_Before`, etc. annotations from your test files. They are no longer needed or parsed.

### Step 5: Deactivate v2

Remove the v2 `aceunit` binary and library from your build.

## Benefits of Migrating

- Shell script is less fragile than Java source parsing — renames and comments no longer confuse the generator
- No Java runtime required in the build environment
- Modular runner lets you use `ForkRunner` on developer machines and `SetJmpRunner` on the target
- Active maintenance — v2 is EOL
