#include <aceunit.h>

extern void beforeAll1(void);
extern void afterAll1(void);
extern void beforeEach1(void);
extern void afterEach1(void);
extern void test1_1(void);
extern void test1_2(void);
extern void test1_3(void);
extern void beforeAll2(void);
extern void afterAll2(void);
extern void beforeEach2(void);
extern void afterEach2(void);
extern void test2_1(void);
extern void test2_2(void);
extern void test2_3(void);

void (*const testcases_fixture1[])(void) = {
    test1_1,
    test1_2,
    test1_3,
    NULL,
};

const AceUnit_Fixture_t fixture_fixture1 = {
    beforeAll1,
    afterAll1,
    beforeEach1,
    afterEach1,
    testcases_fixture1,
};


void (*const testcases_fixture2[])(void) = {
    test2_1,
    test2_2,
    test2_3,
    NULL,
};

const AceUnit_Fixture_t fixture_fixture2 = {
    beforeAll2,
    afterAll2,
    beforeEach2,
    afterEach2,
    testcases_fixture2,
};

const AceUnit_Fixture_t *fixtures[] = {
    &fixture_fixture1,
    &fixture_fixture2,
    NULL,
};
