#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "mock_puts.h"

char mock_puts_buffer[4096];

int mock_puts(const char *text) {
    return sprintf(mock_puts_buffer, "%s\n", text);
}

void assert_puts(const char *expected) {
    assert(strcmp(expected, mock_puts_buffer) == 0);
}
