#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "mock_puts.h"

#define BUF_SIZE 4096

char mock_puts_buffer[BUF_SIZE];

int mock_puts(const char *text) {
    return snprintf(mock_puts_buffer, BUF_SIZE, "%s\n", text);
}

typedef struct interpose_s {
    void *new_func;
    void *orig_func;
} interpose_t;

__attribute__((section("__DATA,__interpose")))
const interpose_t interposing_puts[] = {
    { (void *) mock_puts, (void *)puts },
};
