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

/** Test executor for AceUnit unit test "basicEmbedded".
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file
 */

#include <stdio.h>

#include "AceUnitData.h"

extern const TestFixture_t AceUnitTestFixture;

/** The number of test cases contained in this fixture.
 * This is used to verify that the number of executed test cases is correct.
 */
#define TEST_CASES_FOR_VERIFICATION 12

/** The number of test cases that were executed.
 * This looks redundant with runnerData->testCaseCount but actually it is not.
 * It might be the case that the runner mistakenly executes the wrong methods, e.g. when the generator finds the wrong methods.
 */
extern int myTestCaseCount;

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
    runFixture(&AceUnitTestFixture, NULL);
    if (runnerData->testCaseFailureCount != 0) {
        fprintf(stderr, "Test Cases: %d  Errors: %d\n", (int) runnerData->testCaseCount, (int) runnerData->testCaseFailureCount);
        retVal = 1;
    }
    if (runnerData->testCaseCount != TEST_CASES_FOR_VERIFICATION) {
        fprintf(stderr, "Test Cases: %d but expected %d\n", (int) runnerData->testCaseCount, TEST_CASES_FOR_VERIFICATION);
        retVal = 1;
    }
    if (myTestCaseCount != TEST_CASES_FOR_VERIFICATION) {
        fprintf(stderr, "Test Cases really executed: %d but expected %d\n", (int) myTestCaseCount, TEST_CASES_FOR_VERIFICATION);
        retVal = 1;
    }
    return retVal;
}
