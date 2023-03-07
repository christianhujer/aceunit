#include <aceunit.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 202000L)
#define A_Ignored [[maybe_unused]]
#elif defined(__GNUC__)
#define A_Ignored __attribute__((__unused__))
#else
#define A_Ignored
#endif

int main(A_Ignored int argc, char *argv[]) {
#if defined(__BCC__)
    AceUnit_Result_t result;
    result.testCaseCount = 0;
    result.successCount = 0;
    result.failureCount = 0;
#else
    AceUnit_Result_t result = { 0, 0, 0 };
#endif
    AceUnit_run(fixtures, &result);
    fprintf(stderr, "%s: %d test cases, %d successful, %d failed.\n", argv[0], result.testCaseCount, result.successCount, result.failureCount);
    return result.failureCount ? EXIT_FAILURE : EXIT_SUCCESS;
}
