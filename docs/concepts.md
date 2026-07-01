# Concepts

## Fixtures

A **fixture** is an object file (`.o`) that contains test cases and optionally lifecycle functions. AceUnit scans fixtures using `aceunit` to generate a fixture table.

There is no special source-level annotation. AceUnit uses naming conventions and reads the object file's symbol table.

## Test Cases

A **test case** is any function whose name starts with `test` (or a user-defined prefix). It takes no arguments and returns `void`.

```c
void testAddition(void) {
    assert(add(1, 2) == 3);
}
```

AceUnit runs all such functions in the fixture, in the order they appear in the symbol table.

## Lifecycle Functions

Each fixture may define at most one of each lifecycle function:

| Function | When called | Count |
|----------|-------------|-------|
| `beforeAll()` | Once before any test case in the fixture | 0 or 1 |
| `beforeEach()` | Before every test case | 0 or 1 |
| `afterEach()` | After every test case | 0 or 1 |
| `afterAll()` | Once after all test cases in the fixture | 0 or 1 |

```c
static int counter;

void beforeAll(void) { counter = 0; }

void beforeEach(void) { reset_state(); }

void testOne(void) { assert(counter++ == 0); }

void afterEach(void) { cleanup(); }

void afterAll(void) { assert(counter == 1); }
```

## Test Discovery

`aceunit` scans object files for symbols matching the lifecycle and test naming conventions. It generates a C source file with a fixture table — no manual registration required.

```sh
aceunit leapyear_test.o >testcases.c
```

The generated `testcases.c` contains an array of `AceUnit_Fixture_t` structures and a `main()` that runs them.

## Custom Prefixes

If your project uses a naming convention with a module prefix, you can tell `aceunit` about it:

```sh
aceunit -p 'HeapTest_' heap_test.o >testcases.c
```

This discovers functions like `HeapTest_beforeAll`, `HeapTest_test_allocate`, etc.

## Glossary

`AfterAll`
: A function AceUnit runs once after all test cases in a fixture.

`AfterEach`
: A function AceUnit runs after each test case.

`Assertion`
: Code that verifies an expectation; calls `AceUnit_fail()` on failure.

`BeforeAll`
: A function AceUnit runs once before any test case in a fixture.

`BeforeEach`
: A function AceUnit runs before each test case.

`Fixture`
: An object file containing test cases and optional lifecycle functions.

`Runner`
: The part of AceUnit that executes test functions. See [Runners](runners/index.md).

`Test Case`
: A function AceUnit executes as a test.

`Test Function`
: Any of: `beforeAll`, `beforeEach`, test case, `afterEach`, `afterAll`.
