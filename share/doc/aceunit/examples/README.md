# AceUnit Examples

AceUnit examples can help you understand how to use AceUnit in your own project.

The examples currently show the following things:
- `leapyear`: A very simple example that shows how to unit test in a situation where unit testing is easy.
  This is a good entry point to get started.
  There is a single module without `main()` function.
  And the function under test is a _pure_ _leaf_ function.
  It is _pure_ as in it does not have or depend on any side-effects.
  And it is _leaf_ as in it does not call any other function.
- `hello_world_mocked`: These examples unit-test Hello, world!
  The goal is to test without actually preparing the source code for testability.
  This means, the `hello.c` is a straight-forward Hello, world! program, and the build has to deal with it.
  This poses two challenges.
  - We're testing `main()`. So there needs to be a mechanism to override the `main()` function of `hello.c` with the one from the test runner in AceUnit while keeping the original `main()` function accessible for the test so it can still be invoked.
  - The function under test has an outgoing side-effect by calling the `puts()` function and thus has to replace `puts()` with a mock function so that the test can verify the side-effect.
  This example is provided in 4 different ways:
  - `hello_world_mocked_interpose`: Uses the interposer of the Darwin/macOS loader for redirecting the `puts()` call to a mock. `main()` is overridden using `ojbcopy`.
  - `hello_world_mocked_link`: Wraps `puts()` using the `ld` feature of the GNU/Clang toolchains (not Darwin/macOS).
  - `hello_world_mocked_macro`: Uses a compile-time macro to map `puts()` and `main()` to different functions.
  - `hello_world_mocked_obj`: Uses `objcopy` to override `puts()` with a mock and override `main()`.
