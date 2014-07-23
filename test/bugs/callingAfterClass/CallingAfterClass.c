#include <assert.h>
#include <stdbool.h>
#include "CallingAfterClass.h"

// Run with test id 32767
// Expected behavior: None of the methods is called.
// Actual behavior with bug: My_afterClass is called.

A_BeforeClass void My_beforeClass(void)
{
    assert(false);
}

A_Test void My_test(void)
{
    assert(false);
}

A_AfterClass void My_afterClass(void)
{
    assert(false);
}
