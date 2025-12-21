#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "mock_puts.h"

extern int __real_puts(const char *s);

char mock_puts_buffer[4096];

static bool mock_puts_enabled = false;

void mock_puts_setEnabled(bool enabled) {
    mock_puts_enabled = enabled;
}

int __wrap_puts(const char *text) {
    if (mock_puts_enabled) {
        return sprintf(mock_puts_buffer, "%s\n", text);
    } else {
        return __real_puts(text);
    }
}
