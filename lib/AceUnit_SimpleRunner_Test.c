#include <assert.h>
#include <stdlib.h>
#include <aceunit.h>

bool ran_tc1 = false;
void tc1(void) { ran_tc1 = true; }

bool ran_tc2 = false;
void tc2(void) { ran_tc2 = true; }

bool ran_tc3 = false;
void tc3(void) { ran_tc3 = true; }

static const aceunit_func_t zero_tests[] = {
    NULL,
};

static const aceunit_func_t one_test[] = {
    tc1,
    NULL,
};

static const aceunit_func_t many_tests[] = {
    tc2,
    tc3,
    NULL,
};

const AceUnit_Fixture_t zero_tests_fixture = { NULL, NULL, NULL, NULL, zero_tests };
const AceUnit_Fixture_t one_test_fixture = { NULL, NULL, NULL, NULL, one_test };
const AceUnit_Fixture_t many_tests_fixture = { NULL, NULL, NULL, NULL, many_tests };

const AceUnit_Fixture_t *fixtures[] = {
    &zero_tests_fixture,
    &one_test_fixture,
    &many_tests_fixture,
    NULL,
};

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
#include <assert.h>
    assert(result.testCaseCount == 3);
    assert(result.successCount == 3);
    assert(result.failureCount == 0);
    assert(ran_tc1);
    assert(ran_tc2);
    assert(ran_tc3);
    return EXIT_SUCCESS;
}
