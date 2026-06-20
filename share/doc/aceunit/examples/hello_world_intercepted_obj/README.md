# Unit Test hello, world
Yes, that's right.
A unit test for the hello, world program.

How does it work?
- The original object file `hello.o` is changed to `mocked_hello.o` using `objcopy`.
  With the help of `objcopy`:
  - `main` is renamed to `original_main`.
- The unit tests uses a pipe to intercept STDOUT for verification.
- `hello_test` calls `original_main()`, then reads the output from STDOUT and asserts it.
