#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <aceunit.h>

bool ran_tc_ok = false;

void tc_failing() {
    assert(false);
}

void tc_ok() {
    ran_tc_ok = true;
}

static void (*const failing_test[])() = {
    tc_failing,
    tc_ok,
    NULL,
};

const AceUnit_Fixture_t failing_test_fixture = { NULL, NULL, NULL, NULL, failing_test };

const AceUnit_Fixture_t *fixtures[] = {
    &failing_test_fixture,
    NULL,
};

int main(void) {
    AceUnit_Result_t result = { 0, 0, 0 };
    AceUnit_run(fixtures, &result);
#include <assert.h>
    assert(result.testCaseCount == 2);
    assert(result.successCount == 1);
    assert(result.failureCount == 1);
    return EXIT_SUCCESS;
}
