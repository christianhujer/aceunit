In case llvm-objcopy isn't found, check where llvm is installed.
If you installed llvm with Homebrew, run `brew --prefix llvm`.
It may print something like this:
```
/opt/homebrew/opt/llvm
```
Append `/bin` and add that to your `PATH`.
In one step:
```sh
export PATH=$(brew --prefix llvm)/bin:$PATH
```

# Unit Test hello, world
Yes, that's right.
A unit test for the hello, world program.

How does it work?
- The original object file `hello.o` is changed to `mocked_hello.o` using `objcopy`.
  With the help of `objcopy`:
  - `main` is renamed to `original_main`.
  - `puts` is renamed to `mocked_puts`.
- `mock_puts` provides a function `mock_puts` that works as the replacement for `puts`, and `assert_puts` which compares the expectation with the contents of a buffer filled by calls of `mocked_puts`.
- `hello_test` calls `original_main()` and then `assert_puts()`.
