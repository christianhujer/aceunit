#include <aceunit.h>


void (*const testcases_zero[])(void) = {
    NULL,
};

const AceUnit_Fixture_t fixture_zero = {
    NULL,
    NULL,
    NULL,
    NULL,
    testcases_zero,
};

const AceUnit_Fixture_t *fixtures[] = {
    &fixture_zero,
    NULL,
};
