#include <aceunit.h>
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>


jmp_buf *AceUnit_env;

void AceUnit_fail(void) {
    abort();
}

void AceUnit_abortHandler(int signum) {
    longjmp(*AceUnit_env, signum);
}

#if defined(__NetBSD__) && defined(__GNUC__) && defined(__ARM_ARCH) && __ARM_ARCH >= 8
__attribute__((optimize("O0")))
#endif
bool AceUnit_runCatching(void(*code)(void)) {
    if (code == NULL) return true;
    bool success = false;
    void (*oldHandler)(int) = signal(SIGABRT, AceUnit_abortHandler);
    jmp_buf env; AceUnit_env = &env;
    if (!setjmp(env)) {
        code();
        success = true;
    }
    signal(SIGABRT, oldHandler);
    AceUnit_env = NULL;
    return success;
}
