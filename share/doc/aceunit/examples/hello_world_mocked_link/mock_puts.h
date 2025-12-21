#ifndef MOCK_PUTS_H
#define MOCK_PUTS_H

#include <assert.h>
#include <string.h>

extern char mock_puts_buffer[];

extern int mock_puts(const char *text);

#define assert_puts(expected) \
    assert(strcmp(expected, mock_puts_buffer) == 0)

#endif
