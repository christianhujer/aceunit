#ifndef LEAPYEAR_H
#define LEAPYEAR_H

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#include <stdbool.h>
#elif !defined(__bool_true_false_are_defined)
#define bool int
#define true 1
#define false 0
#define __bool_true_false_are_defined 1
#endif

extern bool isLeapYear(int year);

#endif
