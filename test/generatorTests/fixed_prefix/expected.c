#include <aceunit.h>

extern void Prefix_beforeAll();
extern void Prefix_afterAll();
extern void Prefix_beforeEach();
extern void Prefix_afterEach();
extern void Prefix_test1();
extern void Prefix_test2();

void (*const testcases_prefixed[])() = {
    Prefix_test1,
    Prefix_test2,
    NULL,
};

const AceUnit_Fixture_t fixture_prefixed = {
    Prefix_beforeAll,
    Prefix_afterAll,
    Prefix_beforeEach,
    Prefix_afterEach,
    testcases_prefixed,
};

const AceUnit_Fixture_t *fixtures[] = {
    &fixture_prefixed,
    NULL,
};
