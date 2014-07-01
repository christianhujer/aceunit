/* Copyright (c) 2014, Christian Hujer
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

/** Main program for running AceUnit tests, POSIX Getopt version.
 * Invokes the runner for suite1.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file
 * @ingroup AceUnit
 */

#include <err.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "AceUnit.h"
#include "AceUnitData.h"

/** This always is the first suite. */
extern const TestSuite_t suite1;

/** Runs the suites from the specified ids.
 * @param argc
 *      Id argument count.
 * @param argv
 *      Id arguments with `argv[argc] == NULL`.
 */
void runSuitesFromIds(int argc, char *argv[])
{
    AceTestId_t tests[argc + 1];
    int i;

    for (i = 0; i < argc; i++)
        tests[i] = atoi(argv[i]);

    tests[i] = 0;

    runTests(tests);
}

/** Main program.
 * @param argc
 *      Number of command line arguments.
 * @param argv
 *      Command line arguments.
 *      The first optional argument is a number of expected test cases to fail, which defaults to zero.
 *      The second optional argument is a number of expected test cases in total.
 * @return 0 in case all tests ran successfully, otherwise 1.
 */
int main(int argc, char *argv[])
{
    int expectedTestCaseFailureCount = 0;
    int expectedTestCaseCount = 0;
    int opt;

    while ((opt = getopt(argc, argv, "f:t:")) != -1) {
        switch (opt) {
        case 'f': expectedTestCaseFailureCount = atoi(optarg); break;
        case 't': expectedTestCaseCount = atoi(optarg) ; break;
        default:
            errx(EXIT_FAILURE, "Usage: %s [-f expectedTestCaseFailureCount] [-t expectedTestCaseCount] [TEST_IDs]\n", argv[0]);
        }
    }

    if (optind >= argc)
        runSuite(&suite1);
    else
        runSuitesFromIds(argc - optind, &argv[optind]);

    if (expectedTestCaseFailureCount != runnerData->testCaseFailureCount)
        errx(EXIT_FAILURE, "expected failed test cases: %d; actual failed test cases: %" PRId16, expectedTestCaseFailureCount, runnerData->testCaseFailureCount);
    if ((expectedTestCaseCount != 0) && (expectedTestCaseCount != runnerData->testCaseCount))
        errx(EXIT_FAILURE, "expected test cases: %d; actual test cases: %" PRId16, expectedTestCaseCount, runnerData->testCaseCount);

    return EXIT_SUCCESS;
}
