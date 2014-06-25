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

#include "AceUnit.h"
#include "AceUnitData.h"
#include <stdio.h>
#include <stdlib.h>
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#include <inttypes.h>
#else
#define PRId16 "hd"
#endif

/** Main program for running AceUnit tests.
 * Invokes the runner for suite1.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file
 * @ingroup AceUnit
 */

/** This always is the first suite. */
extern const TestSuite_t suite1;

/** Main program.
 * @param argc
 *      Number of command line arguments.
 * @param argv
 *      Command line arguments.
 *      The first optional argument is a number of expected test cases to fail.
 *      The second optional argument is a number of expected test cases in total.
 * @return 0 in case all tests ran successfully, otherwise 1.
 */
int main(int argc, char *argv[])
{
    int retVal = 0;
    int expectedTestCaseFailureCount = 0;
    int expectedTestCaseCount = 0;

    if (argc >= 2)
        expectedTestCaseFailureCount = atoi(argv[1]);
    if (argc >= 3)
        expectedTestCaseCount = atoi(argv[2]);

    runSuite(&suite1);
    if (runnerData->testCaseFailureCount != expectedTestCaseFailureCount) {
        fprintf(stderr, "Error: %" PRId16 " test cases failed, expected %d test cases to fail.\n", runnerData->testCaseFailureCount, expectedTestCaseFailureCount);
        retVal = 1;
    }
    if ((expectedTestCaseCount != 0) && (runnerData->testCaseCount != expectedTestCaseCount)) {
        fprintf(stderr, "Test Cases: %" PRId16 " but expected %d\n", runnerData->testCaseCount, expectedTestCaseCount);
        retVal = 1;
    }
    return retVal;
}
