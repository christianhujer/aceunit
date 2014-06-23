# AceUnit Roadmap

This file describes the roadmap for AceUnit.
Here you can see which feature will be implemented in which release.
If you want to see which feature will be implemented in which release.


## Disclaimer

The author of AceUnit reserves the right to change the Roadmap at any time without further notice.


## Version Scheme

AceUnit versions are named after [Semantic Versioning 2.0.0](http://semver.org/).


## AceUnit 1.0.0

- Simplify the configuration.
- Change configuration from undef/def scheme to 0/1 scheme, which allows to distinguish between unspecified, specified off and specified on for configuration macros.
- Turn runFixture into a non-`void` function that returns whether one or more test cases failed.
- Use `__STDC_HOSTED__` as a default for `ACEUNIT_EMBEDDED`.
- Provide the option to use AceUnit as a static link library.
- Remove mandatory message, instead add a second set of macros that takes a formatted message, like void `fail(void)` vs. `void failm(const char *format, ...);`, `void assertTrue(bool)` vs. void `assertTrueM(bool, const char *format, ...)`.

- Simplify directory structure (done).
- Change the include file macros to be unstringified strings instead of stringified strings in order to work with compilers who cannot pass stringified strings on command line, such as Keil C251. (done)


## AceUnit 1.1.0

- Add support for `fork()` in the runner, just like [check](http://check.sourceforge.net/).


## AceUnit 2.0.0

- Implement `A_Parameters annotation`.
  The `A_Parameters` annotation declares parameters for a test case.
  There should be two versions of such parameter annotations.
  The first version should take a list of parameters.
  The second version should take a pointer to a `NULL`-terminated array of pointers of parameters.
  Multiple `A_Parameters` methods should be possible for the same method.
  `A_Parameters` should be possible with `A_Test`, `A_Before` and `A_BeforeClass` methods.
  Semantics would be
  `A_Parameters` with `A_BeforeClass`: The entire fixture is repeated for each parameter.
  `A_Parameters` with `A_Before`: Each test case is repeated for each parameter.
  `A_Parameters` with `A_Test`: This test case is repeated for each parameter.
  `A_Parameters` with `A_BeforeClass` and `A_Before` is very similar, just that the parameter is used only once overall when with `A_BeforeClass`, but once for every test case when with `A_Before`.


## Changes not planned for a specific version

- When a file is written, and writing is skipped because the content did not change, it should be checked whether the source is newer, otherwise this can confuse make.
- Add loggers with JUnit-compatible output.
- Allow a parameter for seeding the id generator.
  The purpose is to have reproducible, unique test ids per component in a system which consists of multiple components.
- Modularize unit test Makefiles in order to support multiple compilers.
- Directly support more compilers: gcc, armcc, Keil C51, Keil C251, Keil C166, Samsung UCC for CalmSHINE16 / SecureCALM
- Better separation between test case location information (AceUnit-geneated) and assertion location information (`__FILE__`, `__LINE__`, `__func__`).
- Create global `build.xml` or Makefile for Building releases.
- Improve website layout (make it similar to that of Japi, Gridarta etc.).
- Optional randomization of test order (at runtime, with a pseudo random number generator).
- Better distinction between public API and internal symbols even in header files.
- Add generation of `main()`.
- Add proper runner tree that makes makes use of every logger method.
- Support performance tests by measuring the time for tests.
- Support looping of tests for performance tests.
- Rename all symbols to have a pseudo-namespace.
- Add groups which are an orthogonal grouping system to the tree of suites with fixtures with testcases.
- Extend the runner to get information about what to run.
- Add a library for C to access the mapping table.
- Add a library for Java to access the mapping table.
- Use the modularization even for the output.
- Test the behavior of AceUnit with respect to LTO - Link Time Optimization.
- Improve support for C++, i.e. provide constructors for structs.
- Optionally auto-detect the version of C.
- Work with static link libraries.
- Auto-detect "embedded" by checking if `__STDC_HOSTED__` is defined.
- Possibility for overriding `__STDC_HOSTED__` for compilers which have a bogus definition, like armcc --c99.
- Add another mode for the include files which uses the C89 include files plus a proprietary definition of stdint and stdbool.
- Change documentation generation from Saxon to `xsltproc` (it is simple enough, XSLT 2.0 should not be required).
- The DTDs, if required, should be downloaded automatically instead of having them checked-in.


## Items from the original TODO list which are dropped

The following items have been on the TODO list in the past but have been dropped.
Usually they have been dropped in favor of better alternatives or due to lack of value.
They will probably not be implemented.

- Alternatively allow for naming schemes instead of annotations so users can go without the `A_Test` annotations.
