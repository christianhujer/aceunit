#include "RomanTest.h"
#include "Roman.h"
#include <string.h>

A_Test void givenNull_returnsZero(void)
{
    assertEquals("", 0, fromRoman(NULL));
}

A_Test void givenEmptyString_returnsZero(void)
{
    assertEquals("", 0, fromRoman(""));
}

A_Test void givenI_returnsOne(void)
{
    assertEquals("", 1, fromRoman("I"));
}

A_Test void givenII_returnsTwo(void)
{
    assertEquals("", 2, fromRoman("II"));
}

A_Test void givenIII_returnsThree(void)
{
    assertEquals("", 3, fromRoman("III"));
}

A_Test void givenIV_thenReturnsFour(void)
{
    assertEquals("", 4, fromRoman("IV"));
}

A_Test void givenV_thenReturnsFive(void)
{
    assertEquals("", 5, fromRoman("V"));
}

A_Test void givenVI_thenReturnsSix(void)
{
    assertEquals("" , 6, fromRoman("VI"));
}

A_Test void givenIX_thenReturnsNine(void)
{
    assertEquals("", 9, fromRoman("IX"));
}

A_Test void givenX_thenRetunsTen(void)
{
    assertEquals("", 10, fromRoman("X"));
}

A_Test void givenMCMXCIX_thenRetuns1999(void)
{
    assertEquals("", 1999, fromRoman("MCMXCIX"));
}

A_Test void givenMMCDXLIV_thenReturns2444(void)
{
    assertEquals("", 2444, fromRoman("MMCDXLIV"));
}

A_Test void givenMMDCLXVI_thenReturns2666(void)
{
    assertEquals("", 2666, fromRoman("MMDCLXVI"));
}

#define BUF_LEN 100

A_Test void given0_thenReturnsEmptyString(void)
{
    char buffer[BUF_LEN];
    toRoman(buffer, BUF_LEN, 0);
    assertEquals("", 0, strcmp("", buffer));
}

A_Test void given1_thenReturnsI(void)
{
    char buffer[BUF_LEN];
    toRoman(buffer, BUF_LEN, 1);
    assertEquals("", 0, strcmp("I", buffer));
}
