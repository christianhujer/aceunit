#include <aceunit.h>


const aceunit_func_t testcases_zero[] = {
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
