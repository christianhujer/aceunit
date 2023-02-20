#include <aceunit.h>

extern void beforeAll();
extern void afterAll();
extern void beforeEach();
extern void afterEach();
extern void testFunction1();
extern void testFunction2();

void (*const testcases_full_blown[])() = {
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
