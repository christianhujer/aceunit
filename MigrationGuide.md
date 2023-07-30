# Migration Guide

This guide is intended to help users of older versions of AceUnit to migrate to the current version.

## Major Differences
- The generator has been replaced with a shell script (bash, zsh) that uses a binary analyzer (readelf, objdump, nm) to find the test cases.
- Test cases are found via naming convention, not via fake annotations.

## Major Benefits
There are a few reasons why it might be interesting to migrate to the newer version of AceUnit.
- The shell scripts appear less fragile and more universal.
- While the shell scripts work with `readelf`, `objdump`, and `nm`, they are modular, and you can easily create a module of your own for supporting a different toolchain.
- The old version is EOL and no longer maintained.
- The new version has a modular runner, allowing you to get the best of all worlds.
  You could run the same tests using a simple or custom runner on an embedded device, and using a fork runner on a developer machine.

## Migration Steps

First, prepare all test case functions for the new version of AceUnit.
* Prefix all `A_Before` methods with `beforeEach`.
* Prefix all `A_BeforeClass` methods with `beforeAll`.
* Prefix all `A_After` methods with `afterEach`.
* Prefix all `A_AfterClass` methods with `afterAll`.
* Prefix all `A_Test` methods with `test`.
You do not need to remove the annotations at this stage.
After completing this step, it should be possible to use the old version and new version of AceUnit in parallel.

Second, get the new version of AceUnit running.

Finally, deactivate the old version of AceUnit.
