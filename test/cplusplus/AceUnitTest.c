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

/** Unit Test for AceUnit.
 * Yes, AceUnit can be tested using itself.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file AceUnitTest.c
 */

#include <stdbool.h>
#include <stdio.h>

#include "AceUnitData.h"
#include "AceUnitTest.h"

/** The number of test cases that were executed.
 * This looks redundant with runnerData->testCaseCount but actually it is not.
 * It might be the case that the runner mistakenly executes the wrong methods, e.g. when the generator finds the wrong methods.
 */
int myTestCaseCount = 0;

/** Clears the current recent error. */
static void clearRecentError(void)
{
    if (runnerData->recentError != NULL) {
        runnerData->recentError = NULL;
    }
}

/** Holds whether or not the code continued after an assertion. */
static bool assertionContinued = false;

/** Helper method that asserts something that's then verified by a test case.
 * @param c Assertion case.
 */
static void helper(int c)
{
    assertionContinued = false;
    switch (c) {
    case 0:
        assertTrueM("assertTrueM(msg, true) MUST NOT set recentError.", true);
        break;
    case 1:
        assertTrueM("Test assertion, expected to fail.", false);
        break;
    case 2:
        assertTrueM("Test assertion, expected to fail.", false);
        break;
    case 3:
        assertFalseM("assertFalseM(msg, false) MUST continue the test case.", false);
        break;
    case 4:
        assertFalseM("Test assertion, expected to fail.", true);
        break;
    case 5:
        assertFalseM("Test assertion, expected to fail.", true);
        break;
    case 6:
        {
            int val1 = 10;
            int val2 = val1;
            assertEqualsM("assertEquals(msg, val, val) MUST continue the test case.", val1, val2);
        }
        break;
    case 7:
        {
            int val1 = 10;
            int val2 = 20;
            assertEqualsM("assertEquals(msg, val1, val2) MUST NOT continue the test case.", val1, val2);
        }
        break;
    case 8:
        {
            int val1 = 10;
            int val2 = 20;
            assertEqualsM("Test assertion, expected to fail.", val1, val2);
        }
        break;
    }
    assertionContinued = true;
}

/** Tests that #assertTrueM() with a true condition continues a test case. */
A_Test void testAssertTrueWithTrueContinues(void)
{
    myTestCaseCount++;
    helper(0);
    clearRecentError();
    if (!assertionContinued) {
        failM("Expected assertTrueM(msg, true) to continue.");
    }
}

/** Tests that #assertTrueM() with a false condition does not continue a test case. */
A_Test void testAssertTrueWithFalseReturns(void)
{
    myTestCaseCount++;
    helper(1);
    clearRecentError();
    if (assertionContinued) {
        failM("Expected assertTrueM(msg, false) to not continue.");
    }
}

/** Tests that #assertTrueM() with a true condition does not set recentError. */
A_Test void testAssertTrueWithTrueNoRecentError(void)
{
    myTestCaseCount++;
    clearRecentError();
    assertTrueM("assertTrueM(msg, true) MUST NOT set recentError.", true);
    if (runnerData->recentError != NULL) {
        clearRecentError();
        failM("Expected assertTrueM(msg, true) to not set recentError.");
    }
}

/** Tests that #assertTrueM() with a false condition sets recentError. */
A_Test void testAssertTrueWithFalseSetsRecentError(void)
{
    bool recentErrorSet = false;

    myTestCaseCount++;
    clearRecentError();
    helper(2);
    if (runnerData->recentError != NULL) {
        recentErrorSet = true;
    }
    clearRecentError();
    if (!recentErrorSet) {
        failM("Expected assertTrueM(msg, false) to set recentError.");
    }
}

/** Tests that #assertFalseM() with a true condition continues a test case. */
A_Test void testAssertFalseWithFalseContinues(void)
{
    myTestCaseCount++;
    helper(3);
    clearRecentError();
    if (!assertionContinued) {
        failM("Expected assertion to continue.");
    }
}

/** Tests that #assertFalseM() with a false condition does not continue a test case. */
A_Test void testAssertFalseWithTrueReturns(void)
{
    myTestCaseCount++;
    helper(4);
    clearRecentError();
    if (assertionContinued) {
        failM("Expected assertion to not continue.");
    }
}

/** Tests that #assertFalseM() with a true condition does not set recentError. */
A_Test void testAssertFalseWithFalseNoRecentError(void)
{
    myTestCaseCount++;
    clearRecentError();
    assertFalseM("assertFalseM(msg, false) MUST NOT set recentError.", false);
    if (runnerData->recentError != NULL) {
        clearRecentError();
        failM("Expected recentError to be NULL.");
    }
}

/** Tests that #assertFalseM() with a false condition sets recentError. */
A_Test void testAssertFalseWithTrueSetsRecentError(void)
{
    bool recentErrorSet = false;

    myTestCaseCount++;
    clearRecentError();
    helper(5);
    if (runnerData->recentError != NULL) {
        recentErrorSet = true;
    }
    clearRecentError();
    if (!recentErrorSet) {
        failM("Expected recentError to be set.");
    }
}

/** Tests that #assertEqualsM() with equal values continues a test case. */
A_Test void testAssertEqualsWithEqualContinues(void)
{
    myTestCaseCount++;
    helper(6);
    clearRecentError();
    if (!assertionContinued) {
        failM("Expected assertion to continue.");
    }
}

/** Tests that #assertEqualsM() with unequal values does not continue a test case. */
A_Test void testAssertEqualsWithUnequalReturns(void)
{
    myTestCaseCount++;
    helper(7);
    clearRecentError();
    if (assertionContinued) {
        failM("Expected assertion to not continue.");
    }
}

/** Tests that #assertEqualsM() with equal values does not set recentError. */
A_Test void testAssertEqualsWithEqualNoRecentError(void)
{
    int val1 = 10;
    int val2 = val1;

    myTestCaseCount++;
    clearRecentError();
    assertEqualsM("assertEqualsM(msg, val1, val2) MUST NOT set recentError.", val1, val2);
    if (runnerData->recentError != NULL) {
        clearRecentError();
        failM("Expected recentError to be NULL.");
    }
}

/** Tests that #assertEquals() with unequal values sets recentError.
 * The strange formatting is intentional for <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1887942&amp;group_id=207094&amp;atid=1000227">[ 1887942 ] Java Generator does not detect wrongly formatted test source</a>
 */
A_Test
void
testAssertEqualsWithUnequalSetsRecentError


(void)
{
    bool recentErrorSet = false;

    myTestCaseCount++;
    clearRecentError();
    helper(8);
    if (runnerData->recentError != NULL) {
        recentErrorSet = true;
    }
    clearRecentError();
    if (!recentErrorSet) {
        failM("Expected recentError to be set.");
    }
}
