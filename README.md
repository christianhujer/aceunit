[![Code Climate](https://codeclimate.com/github/christianhujer/aceunit/badges/gpa.svg)](https://codeclimate.com/github/christianhujer/aceunit)

# AceUnit

AceUnit (Advanced C and Embedded Unit): a comfortable C code unit test framework in the tradition of xUnit frameworks suitable even for extremely resource-constraint environments.

## Attributes

- JUnit 4.x-style using Pseudo-annotations (empty macros) and compile-time reflection (separate parser).
- Consumes only very little resources.
  Minimum possible configuration requires 4 bytes RAM and a few bytes stack.
- Works for hosted, freestanding and even exotic freestanding environments.
- Supports C89/C90 and C99, with basic support for C++ and C11.
- Highly configurable.
- Most configuration features are decoupled from the test code, i.e. test code can stay configuration-independent.
- Can be run with pure C89/C90 and thus can be used in environments for which C++ is not available or not used (i.e. 80x51).


## Design Goals

- "User-compatible" with JUnit 4.x - works and behaves like JUnit 4.x annotation based testing.
- No framework overhead in the test code.
  That's because of the JUnit compatible design but it's worth noting explicitly,
  as this is what distinguishes AceUnit from other frameworks for unit testing C code.
- No dependency on any header file.
- Runnable in hosted and freestanding environments, on normal OS or even without OS, on PC and on devices.
- Consume as few resources as possible.


## Requirements

Build-Environment:
- Java 8 is required to build and run the code generator.
- C89 or newer is required to compile and run the tests.
- If C99 is available, AceUnit can make use of it.

Execution Environment:
- AceUnit runs in both, hosted and freestanding environments!
- 4 bytes of free RAM on the device on which the tests shall run.
- ~50-200 bytes of stack, depending on the size of a `jmp_buf`.


## Compilers / CPUs

### Supported Compilers / CPUs

AceUnit has been tested and used on the following compilers, CPUs and environments:
- GCC (various versions, various flavors of Linux and Cygwin) on i686, x86-64 and APS3s
- Keil / ARM ARMCC on ARM7, Cortex-M0, Cortex-M3, SC000, SC100, SC300
- Keil C251 for 80251 (currently known issue: gives a linker warning about a type mismatch, which can safely be ignored)
- Microsoft Visual Studio 2005


### Other Compilers

Although not tested, AceUnit is expected to work with the following compilers out-of-the-box, without any modification:
- Keil Cx51 8051
- Keil C166 C166

Besides, it's planned to add support for the following compilers:
- ucc on Calm16 and SecuCalm
- Open64


## Directory Structure

doc/
    The source code of the documentation.

generator/
    The source code of GenTest, which is the code generator for the AceUnit
    test framework.

include/
    The header files needed to integrate with AceUnit.

src/
    The source code that you need for building programs with AceUnit.
    This also contains tests which can be used to test AceUnit with itself.
    Also, these tests are examples of how to use AceUnit.

test/
    Several unit tests where AceUnit is tested with itself.
    This is excellent examples of how to use AceUnit.
