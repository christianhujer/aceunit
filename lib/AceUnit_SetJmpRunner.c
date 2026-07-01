#include <aceunit.h>
#include <setjmp.h>


jmp_buf *AceUnit_env;

void AceUnit_fail(void) {
    longjmp(*AceUnit_env, 1);
}

bool AceUnit_runCatching(void(*code)(void)) {
    if (code == NULL) return true;
    bool success = false;
    jmp_buf env; AceUnit_env = &env;
    if (!setjmp(env)) {
        code();
        success = true;
    }
    AceUnit_env = NULL;
    return success;
}
