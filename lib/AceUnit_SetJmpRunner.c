#include <aceunit.h>
#include <assert.h>
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>


jmp_buf *AceUnit_env;

void AceUnit_fail() {
    longjmp(*AceUnit_env, 1);
}

static void nop() {}

bool success = false;

bool runCatching(void(*code)()) {
    jmp_buf env; AceUnit_env = &env;
    success = false;
    if (!setjmp(env)) {
        (code ? code : nop)();
        success = true;
    }
    return success;
}
