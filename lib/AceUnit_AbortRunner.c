#include <aceunit.h>
#include <assert.h>
#include <setjmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>


jmp_buf *AceUnit_env;

void AceUnit_fail() {
    abort();
}

void AceUnit_abortHandler(int signum) {
    longjmp(*AceUnit_env, signum);
}

static void nop() {}

bool runCatching(void(*code)()) {
    bool success = false;
    void (*oldHandler)(int) = signal(SIGABRT, AceUnit_abortHandler);
    jmp_buf env; AceUnit_env = &env;
    if (!setjmp(env)) {
        (code ? code : nop)();
        success = true;
    }
    signal(SIGABRT, oldHandler);
    return success;
}
