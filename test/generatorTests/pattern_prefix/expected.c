#include <aceunit.h>

extern void Fixture1_beforeAll(void);
extern void Fixture1_afterAll(void);
extern void Fixture1_beforeEach(void);
extern void Fixture1_afterEach(void);
extern void Fixture1_test1(void);
extern void Fixture1_test2(void);
extern void Fixture2_beforeAll(void);
extern void Fixture2_afterAll(void);
extern void Fixture2_beforeEach(void);
extern void Fixture2_afterEach(void);
extern void Fixture2_test1(void);
extern void Fixture2_test2(void);

void (*const testcases_fixture1[])(void) = {
    Fixture1_test1,
    Fixture1_test2,
    NULL,
};

const AceUnit_Fixture_t fixture_fixture1 = {
    Fixture1_beforeAll,
    Fixture1_afterAll,
    Fixture1_beforeEach,
    Fixture1_afterEach,
    testcases_fixture1,
};


void (*const testcases_fixture2[])(void) = {
    Fixture2_test1,
    Fixture2_test2,
    NULL,
};

const AceUnit_Fixture_t fixture_fixture2 = {
    Fixture2_beforeAll,
    Fixture2_afterAll,
    Fixture2_beforeEach,
    Fixture2_afterEach,
    testcases_fixture2,
};

const AceUnit_Fixture_t *fixtures[] = {
    &fixture_fixture1,
    &fixture_fixture2,
    NULL,
};
