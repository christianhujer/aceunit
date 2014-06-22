/* Copyright (c) 2008 - 2014, Christian Hujer
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the AceUnit developers nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** AceUnit implementation of printf.
 * This primitive implementation allows using printf-like operations even in extremely resource constrained embedded devices.
 *
 * @warning This is work in progress. Do not use!
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file AceUnitPrintf.c
 */

#include <stdarg.h>

#ifdef ACEUNIT_CODE_INCLUDE
#include ACEUNIT_CODE_INCLUDE
#endif

typedef enum {

    NORMAL,

    FMT_START,

    FMT_LENGTH

} fmt_state_t;

/** Character writer.
 * Used by aceunitPrintfImpl to perform the output.
 * @param c character to write
 */
typedef (void)(*aceunitPutchar_fptr_t)(int c);

/** Prints a formatted message.
 *
 * This is a minimalistic implementation of printf.
 * It is guaranteed to support the following subset of the formatting specified in C99:
 * - The only supported character set and encoding is US-ASCII-7.
 * - The only supported flag is <code>0</code>.
 * - Setting the field width is not supported. The field width is fixed to not given for conversions <code>s</code> and <code>%</code>, 8 for <code>x</code>, <code>X</code> and <code>p</code>.
 * - Precision is not supported.
 * - Length modifier is supported within the limited range 1..8.
 * - The only supported conversion specifiers are: <code>s</code>, <code>x</code>, <code>X</code>, <code>p</code> and <code>%</code>.
 * - The only supported argument types are <code>char *</code>, <code>void *</code> and <code>long int</code>.
 * More features may be supported by different implementations.
 *
 * @note You should not use this for regular test logging.
 *       Something worth logging is something worth checking, so instead of looking at the log to see whether what's going on is correct, you should programmatically verify your assumptions.
 *       That's what testing is about.
 *
 * @param format  Format string.
 *
 * @return The number of characters transmitted, or a negative value if an output or encoding error occurred.
 *
 * @see ISO/IEC 9899:1999 Programming languages - C, chapter 7.19.6.1 The fprintf function
 */
int aceunitPrintfImpl(aceunitPutchar_fptr_t putchar, const char * restrict format, ...)
{
    char fmtChar;
    int charsTransmitted;
    va_list args;
    fmt_state_t fmtState = NORMAL;

    bool printLeadingZeros = false;
    int length = 0;
    bool upperCase;

    va_start(args, format);

    while (fmtChar = *format++) {
        switch (fmtState) {
        case NORMAL:
            switch (fmtChar) {
            case '%':
                fmtState = FORMAT_START;
                break;
            default:
                aceunitPutchar(fmtChar);
            }
            break;
        case FORMAT_START:
            switch (fmtChar) {
            case '%':
                aceunitPutchar('%');
                state = NORMAL;
                break;
            case '0':
                printLeadingZeros = true;
                break;
            case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8':
                length = fmtChar - '0';
                break;
            case 'X':
                upperCase = true;
                /*-fallthrough*/
            case 'x':
            case 'p':
                {
                    uint32_t value = va_arg(args, uint32_t);
                    int i;
                    bool first = true;
                    for (i = 7; i >= 0; i--) {
                        uint8_t nibble = (uint8_t) ((value >> (i * 4)) & 0xF);
                        if (!first || (nibble != 0) || printLeadingZeros) {
                            aceunitPutchar(nibble + ((nibble <= 9) ? '0' : (upperCase ? 'A' : 'a') - 10));
                            first = false;
                        }
                    }
                }
                break;
            default:
                /* Unknown format or flag, simply ignore it. */
            }
        }
    }
    va_end(args);
}
