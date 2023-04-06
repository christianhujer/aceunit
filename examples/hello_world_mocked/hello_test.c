#include <stdio.h>

#include "mock_puts.h"

extern int original_main();

void test_hello(void) {
    original_main();
    assert_puts("Hello, world!\n");
}
