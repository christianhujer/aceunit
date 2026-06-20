#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interceptor.h"

extern int original_main(void);

#define assertStrEquals(expected, actual) do { \
    const char *_act = (actual); \
    const char *_exp = (expected); \
    if (0 != strcmp(_act, _exp)) { \
        fprintf(stderr, \
                "%s:%d: Assertion Failed!\n" \
                "  Expected: \"%s\"\n" \
                "  Actual:   \"%s\"\n" \
                , __FILE__, __LINE__, _exp, _act); \
        abort(); \
    } \
} while (false)

void test_hello(void) {
    Interceptor *interceptor = Interceptor_start();

    int exitStatus = original_main();

    char stdoutBuffer[4096];
    char stderrBuffer[4096];
    Interceptor_stop(&interceptor, stdoutBuffer, sizeof(stdoutBuffer), stderrBuffer, sizeof(stderrBuffer));

    assert(0 == exitStatus);
    assertStrEquals("Hello, world!\n", stdoutBuffer);
    assertStrEquals("", stderrBuffer);
}
