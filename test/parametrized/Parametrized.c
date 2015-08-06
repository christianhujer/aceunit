#include <stddef.h>

const int data[] = {
    20, 30,
};

#include "Parametrized.h"

int accumulator;

A_BeforeClass void resetAccumulator(void)
{
    accumulator = 0;
}

A_WithArray((int *, {5, 10}))
A_Test
void myTest(const int *expected)
{
    accumulator += 5;
    assertEquals(accumulator, *expected);
}

A_Parameterized((int *, data))
A_Test
void myTest2(const int *expected)
{
    accumulator += 10;
    assertEquals(accumulator, *expected);
}
