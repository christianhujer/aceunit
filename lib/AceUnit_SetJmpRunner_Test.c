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

int main(void) {
    AceUnit_Result_t result = { 0, 0, 0 };
    AceUnit_run(fixtures, &result);
#include <assert.h>
    assert(result.testCaseCount == 2);
    assert(result.successCount == 1);
    assert(result.failureCount == 1);
    return EXIT_SUCCESS;
}
