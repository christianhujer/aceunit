#include <aceunit.h>

extern void Prefix_beforeAll(void);
extern void Prefix_afterAll(void);
extern void Prefix_beforeEach(void);
extern void Prefix_afterEach(void);
extern void Prefix_test1(void);
extern void Prefix_test2(void);

void (*const testcases_prefixed[])(void) = {
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
