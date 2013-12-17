/* Copyright (c) 2008 - 2011, Christian Hujer
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

/** Unit Test for AceUnit's Loop feature.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file AceUnitLoopTest.c
 */

#include <stdbool.h>
#include <stdio.h>

#include "AceUnitData.h"

extern TestFixture_t AceUnitLoopTestFixture;
extern int loopCount1;
extern int loopCount2;
extern int loopCount3;

/** Main program.
* @return Return value, 0 if the test is successful, other value if wrong.
 */
int main(void) {
    int retVal = 0;
    runFixture(&AceUnitLoopTestFixture);
    if (runnerData->testCaseFailureCount != 0) {
        fprintf(stderr, "Test Cases: %d  Errors: %d\n", runnerData->testCaseCount, runnerData->testCaseFailureCount);
        retVal = 1;
    }
    if (loopCount1 != 5) {
        fprintf(stderr, "Loops #1 expected: 5, loops actual: %d\n", loopCount1);
        retVal = 1;
    }
    if (loopCount2 != 10) {
        fprintf(stderr, "Loops #2 expected: 10, loops actual: %d\n", loopCount2);
        retVal = 1;
    }
    if (loopCount3 != 3) {
        fprintf(stderr, "Loops #3 expected: 3, loops actual: %d\n", loopCount3);
        retVal = 1;
    }
    return retVal;
}
