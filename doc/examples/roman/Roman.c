#include "Roman.h"
#include <string.h>

struct Numeral {
    const char *roman;
    int arabic;
};

static const struct Numeral numerals[] = {
    {  "M", 1000 },
    { "CM",  900 },
    {  "D",  500 },
    { "CD",  400 },
    {  "C",  100 },
    { "XC",   90 },
    {  "L",   50 },
    { "XL",   40 },
    {  "X",   10 },
    { "IX",    9 },
    {  "V",    5 },
    { "IV",    4 },
    {  "I",    1 },
};

static void Numeral_add(struct Numeral *this, const struct Numeral *other)
{
    this->arabic += other->arabic;
    this->roman += strlen(other->roman);
}

static void Numeral_addAllWhileMatching(struct Numeral *this, const struct Numeral *other)
{
    while (strstr(this->roman, other->roman) == this->roman)
        Numeral_add(this, other);
}

static void Numeral_fromRoman(struct Numeral *this)
{
    unsigned int i;
    for (i = 0; i < sizeof(numerals) / sizeof(numerals[0]); i++)
        Numeral_addAllWhileMatching(this, &numerals[i]);
}

static int fromRomanNonNull(const char *roman)
{
    struct Numeral outputNumeral = { NULL, 0 };
    outputNumeral.roman = roman;

    Numeral_fromRoman(&outputNumeral);

    return outputNumeral.arabic;
}

int fromRoman(const char *roman)
{
    if (roman == NULL) return 0;
    return fromRomanNonNull(roman);
}

void toRoman(char *buffer, size_t bufferLength, int number)
{
    unsigned int i;

    if (bufferLength > 0) {
        buffer[0] = '\0';
        bufferLength--;

        for (i = 0; i < sizeof(numerals) / sizeof(numerals[0]); i++) {
            while (number >= numerals[i].arabic) {
                strncat(buffer, numerals[i].roman, bufferLength);
                number -= numerals[i].arabic;
            }
        }
    }
}
