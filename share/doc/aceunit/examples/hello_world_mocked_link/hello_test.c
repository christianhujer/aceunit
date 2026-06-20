#include <stddef.h>

#include "mock_puts.h"

extern int __real_main(void);

void test_hello(void) {
    __real_main();
    assert_puts("Hello, world!\n");
}
