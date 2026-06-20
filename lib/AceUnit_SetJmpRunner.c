#include <aceunit.h>
#include <setjmp.h>


jmp_buf *AceUnit_env;

void AceUnit_fail(void) {
    longjmp(*AceUnit_env, 1);
}

static void nop(void) {}

bool runCatching(void(*code)(void)) {
    bool success = false;
    jmp_buf env; AceUnit_env = &env;
    if (!setjmp(env)) {
        (code ? code : nop)();
        success = true;
    }
    AceUnit_env = NULL;
    return success;
}
