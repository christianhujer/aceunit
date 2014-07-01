/* Copyright (c) 2007 - 2014, Christian Hujer
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

/** Main module of AceUnit.
 * Contains the runner.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file AceUnit.c
 */

#include "AceUnit.h"
#include "AceUnitLogging.h"
#include "AceUnitData.h"

#ifdef ACEUNIT_CODE_INCLUDE
#include ACEUNIT_CODE_INCLUDE
#endif

/** Records an error.
 * @param fixtureId    Id of the fixture that contained the test case with the failed assertion.
 * @param assertionId  Id of the assertion that failed.
 */
void recordError(const FixtureId_t fixtureId, const AssertionId_t assertionId)
{
    runnerData->recentError = &runnerData->recentErrorData;
    runnerData->recentError->fixtureId   = fixtureId;
    runnerData->recentError->assertionId = assertionId;
    runnerData->recentError->testId      = runnerData->currentTestId;
}

/** Returns if the specified test id is contained in a list of test ids.
 *
 * @note Always returns \c true if \p tests contains the value #ALL_TESTS or if \p tests is `NULL`.
 *
 * @param tests
 *      Tests in which to look for \p testId, terminated by #NO_TEST.
 *      If this is `NULL`, `true` is returned.
 * @param testId
 *      Test id for which to look.
 * @return Whether \p test is to be executed.
 * @retval true if \p tests is `NULL`.
 * @retval true if \p test is contained in \p tests.
 * @retval true if \p tests contains #ALL_TESTS.
 * @retval false otherwise
 */
static bool hasToRunTest(const AceTestId_t *tests, const AceTestId_t test)
{
    if (!tests)
        return true;
    for (;NO_TEST != *tests; tests++)
        if ((test == *tests) || (ALL_TESTS == *tests))
            return true;
    return false;
}

/** The Logger. */
extern TestLogger_t *globalLogger;

/* Define the PRE/POST macros as empty macros in case they are undefined to make further source code more readable. */
#ifndef ACEUNIT_PRE_BEFORECLASS
#define ACEUNIT_PRE_BEFORECLASS
#endif
#ifndef ACEUNIT_POST_BEFORECLASS
#define ACEUNIT_POST_BEFORECLASS
#endif
#ifndef ACEUNIT_PRE_BEFORE
#define ACEUNIT_PRE_BEFORE
#endif
#ifndef ACEUNIT_POST_BEFORE
#define ACEUNIT_POST_BEFORE
#endif
#ifndef ACEUNIT_PRE_TEST
#define ACEUNIT_PRE_TEST
#endif
#ifndef ACEUNIT_POST_TEST
#define ACEUNIT_POST_TEST
#endif
#ifndef ACEUNIT_PRE_AFTER
#define ACEUNIT_PRE_AFTER
#endif
#ifndef ACEUNIT_POST_AFTER
#define ACEUNIT_POST_AFTER
#endif
#ifndef ACEUNIT_PRE_AFTERCLASS
#define ACEUNIT_PRE_AFTERCLASS
#endif
#ifndef ACEUNIT_POST_AFTERCLASS
#define ACEUNIT_POST_AFTERCLASS
#endif


/** Runs all test cases from the supplied fixtures.
 * @param fixtures  Test fixtures to run (NULL terminated).
 */
void runFixtures(const TestFixture_t *fixtures[]
#ifdef ACEUNIT_GROUP
        , AceGroupId_t group
#endif
)
{
    for (; NULL != *fixtures; fixtures++)
        runFixture(*fixtures, NULL
#ifdef ACEUNIT_GROUP
                , group
#endif
        );
}

/** Runs the specified test cases from a test fixture.
 * @param fixture  Test fixture to run.
 * @param tests    Tests to run.
 * @param group Group to run.
 */
void runFixture(const TestFixture_t *const fixture, const AceTestId_t *const tests
#ifdef ACEUNIT_GROUP
        , AceGroupId_t group
#endif
        )
{
#define foreach(ptr, init) for (ptr = init; NULL != *ptr; ptr++)

#define invokeAll(X) foreach (secondary, fixture->X) {\
    (*secondary)();\
}
#define globalLog(X, Y) if ((NULL != globalLogger) && (NULL != globalLogger->X)) {\
    globalLogger->X(Y);\
}
    const testMethod_t *volatile secondary; /* beforeClass, before, after, afterClass */
    const testMethod_t *volatile testCase;
    const TestCaseId_t *volatile testId;
#ifdef ACEUNIT_LOOP
    const aceunit_loop_t *volatile loopMax;
    aceunit_loop_t volatile currentLoop;
#endif
#ifdef ACEUNIT_GROUP
    const AceGroupId_t *volatile groups;
#endif
    volatile bool ranBeforeClass = false;

#ifdef ACEUNIT_LOG_FIXTURE
    globalLog(fixtureStarted, fixture->id);
#endif
    for (
        testCase = fixture->testCase,
#ifdef ACEUNIT_LOOP
        loopMax = fixture->loops,
#endif
#ifdef ACEUNIT_GROUP
        groups = fixture->groups,
#endif
        testId = fixture->testIds;
        NULL != *testCase;
        testCase++,
#ifdef ACEUNIT_LOOP
        loopMax++,
#endif
#ifdef ACEUNIT_GROUP
        groups++,
#endif
        testId++
    ) {
        if (hasToRunTest(tests, *testId)) {
#ifdef ACEUNIT_GROUP
            if (*groups == group) {
#endif
                if (!ranBeforeClass) {
                    ACEUNIT_PRE_BEFORECLASS
                    invokeAll(beforeClass);
                    ACEUNIT_POST_BEFORECLASS
                    ranBeforeClass = true;
                }
                runnerData->currentTestId = *testId;
#ifdef ACEUNIT_LOG_TESTCASE
                globalLog(testCaseStarted, runnerData->currentTestId);
#endif
                ACEUNIT_PRE_BEFORE
                invokeAll(before);
                ACEUNIT_POST_BEFORE
                runnerData->recentError = NULL;
                ACEUNIT_PRE_TEST
#if ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_LONGJMP
                if (0 == setjmp(runnerData->jmpBuf)) {
#endif
#ifdef ACEUNIT_LOOP
                    for (currentLoop = 0; (currentLoop < *loopMax) && (NULL == runnerData->recentError); currentLoop++) {
#endif
                        (*testCase)();
#ifdef ACEUNIT_LOOP
                    }
#endif
#if ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_LONGJMP
                }
#endif
                ACEUNIT_POST_TEST
                runnerData->testCaseCount++;
                if (NULL != runnerData->recentError) {
                    globalLog(testCaseFailed, runnerData->recentError);
                    runnerData->testCaseFailureCount++;
                }
                ACEUNIT_PRE_AFTER
                invokeAll(after);
                ACEUNIT_POST_AFTER
#ifdef ACEUNIT_LOG_TESTCASE
                globalLog(testCaseEnded, runnerData->currentTestId);
#endif
                runnerData->currentTestId = TestCaseId_NULL;
#ifdef ACEUNIT_GROUP
            }
#endif
        }
    }
    ACEUNIT_PRE_AFTERCLASS
    invokeAll(afterClass);
    ACEUNIT_POST_AFTERCLASS
#ifdef ACEUNIT_LOG_FIXTURE
    globalLog(fixtureEnded, fixture->id);
#endif
#undef invokeAll
#undef globalLog
}

#ifdef ACEUNIT_SUITES
/** Runs all test cases from the supplied suite.
 * @param suite  Test suite to run.
 * @param group Group to run.
 */
void runSuite(const TestSuite_t *const suite
#ifdef ACEUNIT_GROUP
        , AceGroupId_t group
#endif
) reentrant {
#define globalLog(X, Y) if ((NULL != globalLogger) && (NULL != globalLogger->X)) {\
    globalLogger->X(Y);\
}

    const TestSuite_t *const *suites = suite->suites;
#ifdef ACEUNIT_LOG_SUITE
    globalLog(suiteStarted, suite->id);
#endif
    if (suites != NULL) {
        /* this is a not a Fixture */
        for (; NULL != *suites; suites++) {
            runSuite(*suites
#ifdef ACEUNIT_GROUP
                    , group
#endif
            );
        }
    } else {
        /* this is a Fixture */
        runFixture((TestFixture_t *) suite, NULL
#ifdef ACEUNIT_GROUP
                , group
#endif
        );
    }
#ifdef ACEUNIT_LOG_SUITE
    globalLog(suiteEnded, suite->id);
#endif
#undef globalLog
}
#endif

#ifdef ACEUNIT_SUITES
/** Runs all test cases from the supplied test suites.
 * @param suites Test suites to run (NULL terminated).
 */
void runSuites(const TestSuite_t *suites[]
#ifdef ACEUNIT_GROUP
        , AceGroupId_t group
#endif
) {
    while (NULL != *suites) {
        runSuite(*suites
#ifdef ACEUNIT_GROUP
                , group
#endif
        );
        suites++;
    }
}

/** This always is the first suite. */
extern const TestSuite_t suite1;

/** Runs the specified tests.
 *
 * @param suite Suite or fixture at which the test runner currently is at.
 * @param tests Tests to run, terminated by #NO_TEST.
 * @param group Group to run.
 */
void runTestsIfSpecified(const TestSuite_t *const suite, const AceTestId_t *const tests
#ifdef ACEUNIT_GROUP
        , AceUnitGroupid_t group
#endif
) reentrant {
    if (hasToRunTest(tests, suite->id)) {
        runSuite(suite);
    } else {
        const TestSuite_t *const *suites = suite->suites;
        if (suites != NULL) {
            /* this is not a Fixture. */
            for (; NULL != *suites; suites++) {
                runTestsIfSpecified(*suites, tests
#ifdef ACEUNIT_GROUP
                        ,group
#endif
                );
            }
        } else {
            /** this is a Fixture */
            runFixture((TestFixture_t *) suite, tests
#ifdef ACEUNIT_GROUP
                    , group
#endif
            );
        }
    }
}

/** Runs the specified tests.
 * All tests (test cases and suites - fixtures as well as packages) share the same number space.
 * With other words, the number for a test case is unique (within where you run AceUnit.jar).
 * That means you can specify test suites, fixtures or tests.
 *
 * @note Each test will be executed only zero or one times, even if \p tests contains duplicates.
 *       Duplicates may be explicit or implicit.
 *       Explicit duplicates means the same test id is specified more than once.
 *       Implicit duplicates means the same test id is specified indirectly twice.
 *       Indirect specification of a test id is not via its test id but via its fixture or suite id.
 *
 * @param tests tests to run, terminated with zero.
 */
void runTests(const AceTestId_t *const tests) {
    runTestsIfSpecified(&suite1, tests);
}
#endif

/* TODO: Add method to run specified test cases from a test fixture.
 * This should be done by a linear search through the list of test cases. */
