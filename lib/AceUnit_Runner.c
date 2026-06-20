#include <aceunit.h>
#include <assert.h>

void AceUnit_run(const AceUnit_Fixture_t **fixtures, AceUnit_Result_t *result) {
    const AceUnit_Fixture_t **fixture;
    assert(fixtures);
    assert(result);
    for (fixture = &fixtures[0]; *fixture != NULL; fixture++) {
        bool beforeAll = runCatching((*fixture)->beforeAll);
        void (*const *testcase)(void);
        for (testcase = &(*fixture)->testcases[0]; *testcase != NULL; testcase++) {
            bool beforeEachSuccess = beforeAll && runCatching((*fixture)->beforeEach);
            bool testcaseSuccess = beforeEachSuccess && runCatching(*testcase);
            bool afterEachSuccess = beforeAll && runCatching((*fixture)->afterEach);

            result->testCaseCount++;
            if (testcaseSuccess && afterEachSuccess)
                result->successCount++;
            else
                result->failureCount++;
        }
        if (!runCatching((*fixture)->afterAll))
            result->failureCount++;
    }
}
