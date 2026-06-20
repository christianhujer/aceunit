#include <stddef.h>

#include "mock_puts.h"

extern int __real_main(int argc, char *const argv[]);

void test_hello(void) {
    __real_main(0, NULL);
    assert_puts("Hello, world!\n");
}
