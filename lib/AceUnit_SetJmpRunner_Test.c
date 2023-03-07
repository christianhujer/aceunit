#include <setjmp.h>
#include <stdlib.h>
#include <aceunit.h>

extern jmp_buf *AceUnit_env;

bool ran_tc_ok = false;

void test_failing(void) {
    assert(false);
}

void test_ok(void) {
    ran_tc_ok = true;
}

#undef assert
#include <assert.h>
int main(void) {
#if defined(__BCC__)
    AceUnit_Result_t result;
    result.testCaseCount = 0;
    result.successCount = 0;
    result.failureCount = 0;
#else
    AceUnit_Result_t result = { 0, 0, 0 };
#endif
    AceUnit_run(fixtures, &result);
    assert(result.testCaseCount == 2);
    assert(result.successCount == 1);
    assert(result.failureCount == 1);
    return EXIT_SUCCESS;
}
