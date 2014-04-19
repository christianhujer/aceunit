AceUnit
=======

AceUnit (Advanced C and Embedded Unit): a comfortable C code unit test framework suitable even for extremely resource-constraint environments.

Attributes:
- JUnit 4.x-style using Pseudo-annotations (empty macros) and compile-time reflection (separate parser).
- Consumes only very little resources.
  Minimum possible configuration is 4 bytes RAM and a few bytes Stack.

Supported Compilers:
- gcc
- armcc
- cl (Microsoft Visual Studio)
- Planned support: ucc (CalmSHINE16, SecuCalm), C51 and C251 (Keil Compilers for 8051 and 80251), C166 (Keil Compiler for C16x family)
