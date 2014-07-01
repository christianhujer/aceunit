#include "DummyTest.h"

A_Test void failingTest(void)
{
    assertTrue("", false);
}

A_Test void succeedingTest(void)
{
    assertTrue("", true);
}
