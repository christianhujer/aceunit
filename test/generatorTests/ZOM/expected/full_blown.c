#include <aceunit.h>

extern void beforeAll(void);
extern void afterAll(void);
extern void beforeEach(void);
extern void afterEach(void);
extern void testFunction1(void);
extern void testFunction2(void);

const aceunit_func_t testcases_full_blown[] = {
    testFunction1,
    testFunction2,
    NULL,
};

const AceUnit_Fixture_t fixture_full_blown = {
    beforeAll,
    afterAll,
    beforeEach,
    afterEach,
    testcases_full_blown,
};

const AceUnit_Fixture_t *fixtures[] = {
    &fixture_full_blown,
    NULL,
};
