#include <aceunit.h>
#include <assert.h>

void AceUnit_run(const AceUnit_Fixture_t **fixtures, AceUnit_Result_t *result) {
    const AceUnit_Fixture_t **fixture;
    assert(fixtures);
    assert(result);
    for (fixture = &fixtures[0]; *fixture != NULL; fixture++) {
        bool beforeAll = AceUnit_runCatching((*fixture)->beforeAll);
        void (*const *testcase)(void);
        for (testcase = &(*fixture)->testcases[0]; *testcase != NULL; testcase++) {
            bool beforeEachSuccess = beforeAll && AceUnit_runCatching((*fixture)->beforeEach);
            bool testcaseSuccess = beforeEachSuccess && AceUnit_runCatching(*testcase);
            bool afterEachSuccess = beforeAll && AceUnit_runCatching((*fixture)->afterEach);

            result->testCaseCount++;
            if (testcaseSuccess && afterEachSuccess)
                result->successCount++;
            else
                result->failureCount++;
        }
        if (!AceUnit_runCatching((*fixture)->afterAll))
            result->failureCount++;
    }
}
