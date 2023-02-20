#include <aceunit.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>


void AceUnit_fail() {
    abort();
}

static void nop() {}

bool runCatching(void(*code)()) {
    (code ? code : nop)();
    return true;
}
