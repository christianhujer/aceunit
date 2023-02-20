#include <aceunit.h>

extern void testFunction1();
extern void testFunction2();

void (*const testcases_many[])() = {
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
