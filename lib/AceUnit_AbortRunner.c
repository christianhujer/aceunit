#include <aceunit.h>
#include <setjmp.h>
/* ReSharper disable once CppUnusedIncludeDirective This is a macOS quirk as setjmp.h is included before signal.h. */
#include <signal.h>
#include <stdlib.h>


static jmp_buf *AceUnit_env;

void AceUnit_fail(void) {
    abort();
}

static void AceUnit_abortHandler(int signum) {
    longjmp(*AceUnit_env, signum);
}

#if defined(__NetBSD__) && defined(__GNUC__) && defined(__ARM_ARCH) && __ARM_ARCH >= 8
__attribute__((optimize("O0")))
#endif
bool AceUnit_runCatching(void(*code)(void)) {
    if (code == NULL) return true;
    bool success = false;
    void (*oldHandler)(int) = signal(SIGABRT, AceUnit_abortHandler);
    jmp_buf env;
    if (!setjmp(env)) {
        AceUnit_env = &env;
        code();
        success = true;
    }
    signal(SIGABRT, oldHandler);
    AceUnit_env = NULL;
    return success;
}
