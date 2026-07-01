#include <aceunit.h>
#include <stdlib.h>


void AceUnit_fail(void) {
    abort();
}

bool AceUnit_runCatching(void(*code)(void)) {
    if (code == NULL) return true;
    code();
    return true;
}
