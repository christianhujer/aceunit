#include "leapyear.h"
#include <assert.h>
#include <stddef.h>

void testLeapYears() {
    assert(isLeapYear(0));
    assert(isLeapYear(4));
    assert(isLeapYear(400));
}

void testNonLeapYears() {
    assert(!isLeapYear(1));
    assert(!isLeapYear(100));
}
