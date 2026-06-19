#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "mock_puts.h"

#define BUF_SIZE 4096

extern int __real_puts(const char *s);

char mock_puts_buffer[BUF_SIZE];

static bool mock_puts_enabled = false;

void mock_puts_setEnabled(bool enabled) {
    mock_puts_enabled = enabled;
}

int __wrap_puts(const char *text) {
    if (mock_puts_enabled) {
        return snprintf(mock_puts_buffer, BUF_SIZE, "%s\n", text);
    } else {
        return __real_puts(text);
    }
}
