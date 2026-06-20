#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "mock_puts.h"

#define BUF_SIZE 4096

extern int __real_puts(const char *s);

char mock_puts_buffer[BUF_SIZE];

int __wrap_puts(const char *text) {
    return snprintf(mock_puts_buffer, BUF_SIZE, "%s\n", text);
}
