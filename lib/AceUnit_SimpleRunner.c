#include <aceunit.h>
#include <assert.h>
#include <stdlib.h>


void AceUnit_fail(void) {
    abort();
}

static void nop(void) {}

bool runCatching(void(*code)(void)) {
    (code ? code : nop)();
    return true;
}
