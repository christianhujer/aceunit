#include "RomanTest.h"
#include "Roman.h"
#include <string.h>
#include <stdio.h>

A_Test void givenNull_returnsZero(void)
{
    assertEquals(0, fromRoman(NULL));
}

A_Test void givenEmptyString_returnsZero(void)
{
    assertEquals(0, fromRoman(""));
}

A_Test void givenI_returnsOne(void)
{
    assertEquals(1, fromRoman("I"));
}

A_Test void givenII_returnsTwo(void)
{
    assertEquals(2, fromRoman("II"));
}

A_Test void givenIII_returnsThree(void)
{
    assertEquals(3, fromRoman("III"));
}

A_Test void givenIV_thenReturnsFour(void)
{
    assertEquals(4, fromRoman("IV"));
}

A_Test void givenV_thenReturnsFive(void)
{
    assertEquals(5, fromRoman("V"));
}

A_Test void givenVI_thenReturnsSix(void)
{
    assertEquals(6, fromRoman("VI"));
}

A_Test void givenIX_thenReturnsNine(void)
{
    assertEquals(9, fromRoman("IX"));
}

A_Test void givenX_thenRetunsTen(void)
{
    assertEquals(10, fromRoman("X"));
}

A_Test void givenMCMXCIX_thenRetuns1999(void)
{
    assertEquals(1999, fromRoman("MCMXCIX"));
}

A_Test void givenMMCDXLIV_thenReturns2444(void)
{
    assertEquals(2444, fromRoman("MMCDXLIV"));
}

A_Test void givenMMDCLXVI_thenReturns2666(void)
{
    assertEquals(2666, fromRoman("MMDCLXVI"));
}

#define BUF_LEN 100

static void assertArabicIsRoman(int arabic, const char *expectedRoman)
{
    char buffer[BUF_LEN];
    toRoman(buffer, BUF_LEN, arabic);
    assertEquals(0, strcmp(expectedRoman, buffer));
}

A_Test void givenEmptyBuffer_thenConvertsNothing(void)
{
    char buffer[BUF_LEN];
    memset(buffer, 0x5A, BUF_LEN);
    toRoman(buffer + 1, 0, 1);
    assertEquals(0x5A, buffer[0]);
    assertEquals(0x5A, buffer[1]);
    assertEquals(0x5A, buffer[2]);
}

A_Test void givenOneByteBuffer_thenConvertsToEmptyString(void)
{
    char buffer[BUF_LEN];
    memset(buffer, 0x5A, BUF_LEN);
    toRoman(buffer + 1, 1, 2);
    assertEquals(0x5A, buffer[0]);
    assertEquals(0x00, buffer[1]);
    assertEquals(0x5A, buffer[2]);
}

A_Test void given0_thenReturnsEmptyString(void)
{
    assertArabicIsRoman(0, "");
}

A_Test void given1_thenReturnsI(void)
{
    assertArabicIsRoman(1, "I");
}

A_Test void given2_thenReturnsII(void)
{
    assertArabicIsRoman(2, "II");
}

A_Test void given4_thenReturnsIV(void)
{
    assertArabicIsRoman(4, "IV");
}

A_Test void given5_thenReturnsV(void)
{
    assertArabicIsRoman(5, "V");
}

A_Test void given2444_thenReturnsMMCDXLIV(void)
{
    assertArabicIsRoman(2444, "MMCDXLIV");
}

A_Test void given2666_thenReturnsMMDCLXVI(void)
{
    assertArabicIsRoman(2666, "MMDCLXVI");
}
