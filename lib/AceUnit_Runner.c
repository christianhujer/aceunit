#include <aceunit.h>
#include <assert.h>

void AceUnit_run(const AceUnit_Fixture_t **fixtures, AceUnit_Result_t *result) {
    const AceUnit_Fixture_t **fixture;
    assert(fixtures);
    assert(result);
    for (fixture = &fixtures[0]; *fixture != NULL; fixture++) {
        bool beforeAll = runCatching((*fixture)->beforeAll);
        void (*const *testcase)();
        for (testcase = &(*fixture)->testcases[0]; *testcase != NULL; testcase++) {
            result->testCaseCount++;
            /* execute testcase only if beforeEach was successful, but execute afterEach in any case. */
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wbitwise-instead-of-logical"
#endif
            if (beforeAll && ((runCatching((*fixture)->beforeEach) && runCatching(*testcase)) & runCatching((*fixture)->afterEach)))
                result->successCount++;
            else
                result->failureCount++;
#ifdef __clang__
#pragma clang diagnostic pop
#endif
        }
        if (!runCatching((*fixture)->afterAll))
            result->failureCount++;
    }
}
