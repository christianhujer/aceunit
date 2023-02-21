# AceUnit-3

Welcome to AceUnit, the Advanced C and Embedded Unit test framework.
AceUnit is a comfortable (test discovery!) unit test framework for C, in the best tradition of xUnit frameworks (like JUnit).
Its target audience are developers using the C programming language to develop firmware, drivers, operating systems, and other C programs, like command line programs.
It is tiny and thus suitable even for extremely resource-constraint environments.

AceUnit can also be used to study or teach Test-Driven Development.
Although, you don't really need a framework for that in C, did you know that?
A framework just helps making your life more comfortable.

The purpose of AceUnit is to be portable, small, and usable in resource-constraint environments as well as on PCs.

This is the third version of AceUnit, and a complete rewrite from scratch.
The "template" for this version of AceUnit is no longer JUnit 4 but JUnit 5.

```C
#include "leapyear.h"
#include <assert.h>

void testLeapYears() {
    assert(isLeapYear(0));
    assert(isLeapYear(4));
    assert(isLeapYear(400));
}

void testNonLeapYears() {
    assert(!isLeapYear(1));
    assert(!isLeapYear(100));
}
```

## Attributes and Design Goals
* JUnit 5.x-style naming.
* Consumes only very little resources.
* Works for hosted, freestanding,  and even exotic freestanding environments.
* Supports C89/C90, C99, C11, C17, and C23.
* Configurable.
* Can be run with pure C89/C90 and thus can be used in environments for which C++ is not available or used (i.e. 80x51).
* Minimal framework noise in the test code.
  Especially, no macro noise and no fixture management noise.
* Make use of existing C features from the hosted environment and POSIX, but _without requiring_ a hosted environment or POSIX.
  It will also work just fine on the freestanding environment of an embedded controller.

## Compilers

This new version of AceUnit has been tested extensively using the following compilers:
* GCC 11 w/ the following settings on `x86_64`: c90 c99 c11 c17 c2x gnu90 gnu99 gnu11 gnu17 gnu2x
* clang 14.0.6

The following compilers are planned to be tested soon:
* GCC for aarch64, alpha, arm, hppa, hppa64, i686, m68k, mips, mips64, powerpc, powerpc64, powerpc64le, riscv64, s390x, sh4, sparc64
* Clang for aarch64, arm, avr, hexagon, mips, mips64, thumb, wasm32, wasm64
* Keil / ARM ARMCC on ARM7, Cortex-M0, Cortex-M3, SC000, SC100, SC300
* Keil C51 and C251 for 8051 and 80251
* Keil C166 for Infineon C16x and STMicroelectronics ST10
* Samsung ucc on Calm16 and SecuCalm
* Open64

## How to Build
To build AceUnit, you need a GNU `bash` shell, GNU `make`, and a C compiler with `objdump`, `readelf`, or `nm`.
To build it, simply run `make`.
This builds and tests AceUnit.

## How to Install
If you want to use AceUnit for testing on your POSIX system, simply run `make && sudo make install`.
This will install AceUnit into `/usr/local/`.

### How to build with a different compiler.
By default, AceUnit will be built with/for the C compiler that your `make` tool uses, usually whatever `cc` is found on the `PATH`.
If you want to build and test with a different compiler, you can use `make CC=compilername`, for example, `make CC=clang`.

## Runners
AceUnit provides different runners for different needs.
Out of the box, AceUnit comes with 4 runners: Simple, SetJmp, Abort, and Fork.
AceUnit is well-documented, it should be easy to create your own runner if necessary.

### SimpleRunner
The SimpleRunner just executes the tests without any special handling.
If a test case fails, the runner stops.

The SimpleRunner is good to get started and for learning and practicing TDD.

For real-life projects, the SimpleRunner is less suited.
As it will stop at the first error, there will be no information about the total number of test cases and errors.
But do not fret, there are other runners.

### SetJmpRunner
The SetJmpRunner uses `setjmp()` / `longjmp()` to intercept failed assertion.
The `assert()` macro is defined to call `AceUnit_fail()` when the condition fails.
And `AceUnit_fail()` performs a `longjmp()` back.

This runner works in freestanding environments _as long as `setjmp()`/`longjmp()` are available_.
According to the C standard, freestanding environments are not required to provide `<setjmp.h>`.
However, most freestanding environments do so.

### AbortRunner
The AbortRunner is like the SetJmpRunner and additionally has a signal handler to catch the `abort()` signal.
If a test case fails by raising `SIGABRT`, the runner will catch it.

### ForkRunner
The ForkRunner uses `fork()` to execute test cases in child processes.
A test case is marked failed if the child ended due to a signal, or if it exited with an exit value other than `EXIT_SUCCESS` (0).

### Writing your own Runner
If the runners provided out of the box do not suit you, you can simply write your own.
Just look at the source code of the existing runners to get inspired.
They're simple and should be easy to understand.

## Assertion/Failure Features
There are multiple ways how you can make a test-case fail.

<table>
<tr><th>Assertion</th>                              <th>SimpleRunner</th><th>SetJmpRunner</th><th>AbortRunner</th><th>ForkRunner</th></tr>
<tr><td><code>&lt;stdlib.h&gt; longjmp()</code></td><td>no</td>          <td>yes</td>         <td>yes</td>        <td>no (not required)</td></tr>
<tr><td><code>&lt;assert.h&gt; assert()</code></td> <td>stop</td>        <td>no</td>          <td>yes</td>        <td>yes</td></tr>
<tr><td><code>&lt;stdlib.h&gt; abort()</code></td>  <td>stop</td>        <td>no</td>          <td>yes</td>        <td>yes</td></tr>
<tr><td><code>&lt;stdlib.h&gt; exit()</code></td>   <td>stop</td>        <td>no</td>          <td>no</td>         <td>yes</td></tr>
<tr><td><code>&lt;AceUnit.h&gt; assert()</code></td><td>yes</td>         <td>yes</td>         <td>yes</td>        <td>yes</td></tr>
</table>

## Test Fixtures

## What is different from previous versions?
The whole code has been rewritten from scratch, test-driven and with ease-of-use on mind.
The nomenclature has been updated to match that of JUnit5.
The generator has been changed from a Java program to a shell script.
Also, the generator no loner works on the source file, which is fragile.
Instead, the generator uses tools like `objdump`, `nm`, or `readelf` to extract the symbol table and thus introspect the code to discover fixtures and test cases.

## Glossary

<dl>
<dt>AfterAll</dt><dd>A function that AceUnit shall run once after it runs any of the test cases of a fixture.</dd>
<dt>AfterEach<dt><dd>A function that AceUnit shall run after each of the test cases of a fixture.</dd>
<dt>Assertion</dt><dd>A piece of code that verifies expectations inside a test function, and if the expectation isn't met, aborts the test case and reports back to the runner.</dd>
<dt>BeforeAll</dt><dd>A function that AceUnit shall run once before it runs any of the test cases of a fixture.</dd>
<dt>BeforeEach<dt><dd>A function that AceUnit shall run before each of the test cases of a fixture.</dd>
<dt>Fixture</dt><dd>An object file with test cases.</dd>
<dt>Runner</dt><dd>The part of AceUnit that executes test functions by calling them.</dd>
<dt>Test Case</dt><dd>A function that AceUnit should execute as a test case.</dd>
<dt>Test Function<dt><dd>Any of these: AfterAll, AfterEach, BeforeAll, BeforeEach, Test Case.</dd>
</dl>

## Dropped Features
The previous versions of AceUnit had a number of features that have been deliberately dropped to keep things simple:
<dl>
<dt>Annotation-style processing</dt><dd>Previous versions of AceUnit used annootation-style processing like `A_Test`, `A_BeforeClass`, and so on. This was a bit fragile and required an extra parser. Annotations will come back once C has annotations. They're on the way, give it a few more years. This also made it possible to get rid of _Java_ for the generator and replace it with a simple shell script.</dd>
<dt>Multiple fixture methods</dt><dd>Previous versions of AceUnit allowed for multiple setup and teardown functions per fixture. I don't think this was really used. This has been dropped to save a bit of memory.</dd>
</dl>
