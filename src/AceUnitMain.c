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

#include <stdio.h>
#include "AceUnit.h"
#include "AceUnitData.h"

/** Main program for running AceUnit tests.
 * Invokes the runner.
 * It will only properly work if #ACEUNIT_SUITES is defined.
 * If #ACEUNIT_SUITES is not defined, this file will effectively be empty.
 *
 * It supports two configuration parameters:
 * <dl>
 *  <dt><code>TEST_FAILURES_FOR_VERIFICATION</code> (optional, default: 0)</dt>
 *  <dd>The number of test cases expected to fail. Defaults to 0.</dd>
 *  <dt><code>TEST_CASES_FOR_VERIFICATION</code> (optional, default: undef)</dt>
 *  <dd>The number of test cases expected to be executed.</dd>
 * </dl>
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file AceUnitMain.c
 */

#ifdef ACEUNIT_SUITES

#ifndef TEST_FAILURES_FOR_VERIFICATION
/** The number of test cases expected to fail.
 * Defaults to 0.
 */
#define TEST_FAILURES_FOR_VERIFICATION 0
#endif

/** This always is the first suite. */
extern const TestSuite_t suite1;

/** Main program.
 * @return 0 in case all tests ran successfully, otherwise 1.
 */
int main(void) {
    int retVal = 0;
    runSuite(&suite1);
    if (runnerData->testCaseFailureCount != TEST_FAILURES_FOR_VERIFICATION) {
        fprintf(stderr, "Error: %d test cases failed, expected %d test cases to fail.\n", (int) runnerData->testCaseFailureCount, (int) TEST_FAILURES_FOR_VERIFICATION);
        retVal = 1;
    }
#ifdef TEST_CASES_FOR_VERIFICATION
    if (runnerData->testCaseCount != TEST_CASES_FOR_VERIFICATION) {
        fprintf(stderr, "Test Cases: %d but expected %d\n", runnerData->testCaseCount, TEST_CASES_FOR_VERIFICATION);
        retVal = 1;
    }
#endif
    return retVal;
}
#endif
