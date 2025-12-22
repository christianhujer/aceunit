#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "mock_puts.h"

char mock_puts_buffer[4096];

int mock_puts(const char *text) {
    return sprintf(mock_puts_buffer, "%s\n", text);
}

typedef struct interpose_s {
    void *new_func;
    void *orig_func;
} interpose_t;

__attribute__((section("__DATA,__interpose")))
const interpose_t interposing_puts[] = {
    { (void *) mock_puts, (void *)puts },
};
