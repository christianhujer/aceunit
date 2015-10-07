/* Copyright (c) 2007 - 2015, Christian Hujer
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

#ifndef ACEUNITTRY_H
/** Include shield to protect the header file from being included more than once. */
#define ACEUNITTRY_H

#if ACEUNIT_ASSERTION_STYLE != ACEUNIT_ASSERTION_STYLE_LONGJMP
#error AceUnitTry.h requires ACEUNIT_ASSERTION_STYLE_LONGJMPP
#endif

/** AceUnitTry header file.
 * Allows the interception of exceptions in test cases.
 * It works by intercepting `longjmp()`, including those triggered via `SIGABRT` by `assert()` from `<assert.h>` and `abort()` from `<stdlib.h>`.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file AceUnitTry.h
 */

/** `try` for AceUnit tests.
 * Intercepts `longjmp()` and on hosted environments also intercepts `assert()` and `abort()`.
 */
/*lint -emacro(545,717,A_try)*/
#define A_try \
    do { \
        jmp_buf jmpBuf; \
        jmp_buf *oldJmpBuf = runnerData->jmpBuf; \
        runnerData->jmpBuf = &jmpBuf; \
        if  (0 == setjmp(jmpBuf)) { \
            do \

/** `catch` for AceUnit tests. */
/*lint -emacro(717,A_catch)*/
#define A_catch \
            while (false); \
        } else { \
            runnerData->jmpBuf = oldJmpBuf; \
            do \

/** `endtry` for AceUnit tests. */
/*lint -emacro(717,A_endtry)*/
#define A_endtry \
            while (false); \
        } \
        runnerData->jmpBuf = oldJmpBuf; \
    } while (0)

#endif
