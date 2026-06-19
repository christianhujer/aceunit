#include <stdio.h>
#include <string.h>

#include "mock_puts.h"

#define BUF_SIZE 4096

char mock_puts_buffer[BUF_SIZE];

int mock_puts(const char *text) {
    return snprintf(mock_puts_buffer, BUF_SIZE, "%s\n", text);
}
