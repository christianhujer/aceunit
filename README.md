AceUnit
=======

AceUnit (Advanced C and Embedded Unit): a comfortable C code unit test framework in the tradition of xUnit frameworks suitable even for extremely resource-constraint environments.

Attributes:
- JUnit 4.x-style using Pseudo-annotations (empty macros) and compile-time reflection (separate parser).
- Consumes only very little resources.
  Minimum possible configuration requires 4 bytes RAM and a few bytes stack.
- Works for hosted, freestanding and even exotic freestanding environments.
- Supports C89/C90 and C99 (even has basic support for C++ and C11).
- Highly configurable.
- Most configuration features are decoupled from the test code, i.e. test code can stay configuration-independent.

Supported Compilers / CPUs:
- gcc i686-pc-cygwin, x86-64-linux
- gcc x86-64-linux
- armcc arm

Untested Compilers:
- cl i386-pc-windows
- gcc other platforms

Planned Compilers:
- ucc Calm16
- ucc SecuCalm
- Keil Cx51 8051
- Keil C251 80251
- Keil C166 C166
- Open64 x86-64, ia64, x86, mips, arm
