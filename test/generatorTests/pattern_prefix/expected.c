#include <aceunit.h>

extern void Fixture1_beforeAll();
extern void Fixture1_afterAll();
extern void Fixture1_beforeEach();
extern void Fixture1_afterEach();
extern void Fixture1_test1();
extern void Fixture1_test2();
extern void Fixture2_beforeAll();
extern void Fixture2_afterAll();
extern void Fixture2_beforeEach();
extern void Fixture2_afterEach();
extern void Fixture2_test1();
extern void Fixture2_test2();

void (*const testcases_fixture1[])() = {
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


void (*const testcases_fixture2[])() = {
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
