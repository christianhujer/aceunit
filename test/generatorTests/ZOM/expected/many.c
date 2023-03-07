#include <aceunit.h>

extern void testFunction1(void);
extern void testFunction2(void);

const aceunit_func_t testcases_many[] = {
    testFunction1,
    testFunction2,
    NULL,
};

const AceUnit_Fixture_t fixture_many = {
    NULL,
    NULL,
    NULL,
    NULL,
    testcases_many,
};

const AceUnit_Fixture_t *fixtures[] = {
    &fixture_many,
    NULL,
};
