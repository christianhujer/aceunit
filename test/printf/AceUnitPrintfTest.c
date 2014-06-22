/* Copyright (c) 2007 - 2011, Christian Hujer
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

/** Unit Test for AceUnit's own printf.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file
 */

#include <stdbool.h>
#include <stdio.h>

#define ACEUNIT_ASSERTION_STYLE ACEUNIT_ASSERTION_STYLE_RETURN

#include "AceUnitData.h"
#include "AceUnitPrintfTest.h"

/** Tests that #assertEquals() with equal values does not set recentError. */
A_Test void testPrintfSimple() {
    char *format = "foo";
    char *expected = "foo";


    assertEquals("assertEquals(msg, val1, val2) MUST NOT set recentError.", val1, val2);
    if (runnerData->recentError != NULL) {
        clearRecentError();
        fail("Expected recentError to be NULL.");
    }
}

/** Run the tests.
 * @note This is only here temporarily.
 * @note Command line arguments currently are ignored.
 * In future versions, this part will be auto-generated.
 * @return Exit status.
 * @retval 0 if all tests ran successfully.
 * @retval 1 if there were test errors or failures.
 */
int main(void) {
    int retVal = 0;
    runFixture(&AceUnitTestFixture);
    if (runnerData->testCaseFailureCount != 0) {
        fprintf(stderr, "Test Cases: %d  Errors: %d\n", runnerData->testCaseCount, runnerData->testCaseFailureCount);
        retVal = 1;
    }
    if (runnerData->testCaseCount != TEST_CASES_FOR_VERIFICATION) {
        fprintf(stderr, "Test Cases: %d but expected %d\n", runnerData->testCaseCount, TEST_CASES_FOR_VERIFICATION);
        retVal = 1;
    }
    if (myTestCaseCount != TEST_CASES_FOR_VERIFICATION) {
        fprintf(stderr, "Test Cases really executed: %d but expected %d\n", myTestCaseCount, TEST_CASES_FOR_VERIFICATION);
        retVal = 1;
    }
    return retVal;
}
