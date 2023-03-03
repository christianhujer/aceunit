#include <aceunit.h>

extern void beforeAll(void);
extern void afterAll(void);
extern void beforeEach(void);
extern void afterEach(void);
extern void test1(void);
extern void test2(void);
extern void test3(void);

void (*const testcases_fixture[])(void) = {
    test1,
    test2,
    test3,
    NULL,
};

const AceUnit_Fixture_t fixture_fixture = {
    beforeAll,
    afterAll,
    beforeEach,
    afterEach,
    testcases_fixture,
};

const AceUnit_Fixture_t *fixtures[] = {
    &fixture_fixture,
    NULL,
};
