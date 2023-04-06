#ifndef MOCK_PUTS_H
#define MOCK_PUTS_H

#include <assert.h>

extern int mock_puts(const char *text);

extern void assert_puts(const char *expected);

#endif
