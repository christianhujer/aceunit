#include <aceunit.h>

extern void testFunction();

void (*const testcases_one[])() = {
    testFunction,
    NULL,
};

const AceUnit_Fixture_t fixture_one = {
    NULL,
    NULL,
    NULL,
    NULL,
    testcases_one,
};

const AceUnit_Fixture_t *fixtures[] = {
    &fixture_one,
    NULL,
};
