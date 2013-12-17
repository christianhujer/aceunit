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

#ifndef ACEUNITLOGGING_H
/** Include shield to protect the header file from being included more than once. */
#define ACEUNITLOGGING_H 1

#include "AceUnit.h"

/** AceUnit Logging header file.
 * You do no tneed to include this header file in a fixture.
 * Test fixtures do not need this header file.
 * This header file is only needed by runners and loggers.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file AceUnitLogging.h
 */

/** Value for #ACEUNIT_LOGGING_STYLE for only logging failures.
 * This is primarily meant for embedded systems where everything should be as small and simple as possible.
 *
 * @see #ACEUNIT_LOGGING_STYLE
 */
#define ACEUNIT_LOGGING_STYLE_SIMPLE 1

/** Value for #ACEUNIT_LOGGING_STYLE for full logging with all events.
 *
 * @see #ACEUNIT_LOGGING_STYLE
 */
#define ACEUNIT_LOGGING_STYLE_FULL 2

#ifndef ACEUNIT_LOGGING_STYLE
/** Determines the style of logging to use.
 * Defaults to #ACEUNIT_LOGGING_STYLE_SIMPLE if #ACEUNIT_EMBEDDED is defined.
 * Defaults to #ACEUNIT_LOGGING_STYLE_FULL otherwise.
 *
 * @see #ACEUNIT_LOGGING_STYLE_SIMPLE
 * @see #ACEUNIT_LOGGING_STYLE_FULL
 */
#ifdef ACEUNIT_EMBEDDED
#define ACEUNIT_LOGGING_STYLE ACEUNIT_LOGGING_STYLE_SIMPLE
#else
#define ACEUNIT_LOGGING_STYLE ACEUNIT_LOGGING_STYLE_FULL
#endif
#endif

#if ACEUNIT_LOGGING_STYLE == ACEUNIT_LOGGING_STYLE_FULL
/** Determines that runner events are logged. */
#define ACEUNIT_LOG_RUNNER
#endif

#if ACEUNIT_LOGGING_STYLE == ACEUNIT_LOGGING_STYLE_FULL
/** Determines that suite events are logged. */
#define ACEUNIT_LOG_SUITE
#endif

#if ACEUNIT_LOGGING_STYLE == ACEUNIT_LOGGING_STYLE_FULL
/** Determines that fixture events are logged. */
#define ACEUNIT_LOG_FIXTURE
#endif

#if ACEUNIT_LOGGING_STYLE == ACEUNIT_LOGGING_STYLE_FULL
/** Determines that test case events are logged. */
#define ACEUNIT_LOG_TESTCASE
#endif

/* Note: Logging of failures cannot be turned off. */

/** A Logger logs events during test execution.
 *
 * @warning When you write a logger, you should not use this structure directly.
 * If you violate this rule, your logger will be much more dependant on changes to the structure than it should.
 * Instead, use the macro #AceUnitNewLogger() to declare an instance of this type.
 *
 * @see #AceUnitNewLogger()
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
typedef struct {

#ifdef ACEUNIT_LOG_RUNNER
    /** Informs this logger that the runner has started running.
     * Maybe #NULL in case this logger does not implement this function.
     */
    void(*runnerStarted)(void);
#endif

#ifdef ACEUNIT_LOG_SUITE
    /** Informs this logger that the runner has started a suite.
     * Maybe #NULL in case this logger does not implement this function.
     */
    void(*suiteStarted)(SuiteId_t const suiteId);
#endif

#ifdef ACEUNIT_LOG_FIXTURE
    /** Informs this logger that the runner has started a fixture.
     * Maybe #NULL in case this logger does not implement this function.
     * @param fixture Fixture that was started.
     */
    void(*fixtureStarted)(const FixtureId_t fixture);
#endif

#ifdef ACEUNIT_LOG_TESTCASE
    /** Informs this logger that the runner starts a test case.
     * Maybe #NULL in case this logger does not implement this function.
     * @param testCase Test case that was started.
     */
    void(*testCaseStarted)(TestCaseId_t testCase);
#endif

    /** Informs this logger that the runner failed a test case.
     * Maybe #NULL in case this logger does not implement this function.
     * @param error Assertion error with error information.
     */
    void(*testCaseFailed)(const AssertionError_t *error);

#ifdef ACEUNIT_LOG_TESTCASE
    /** Informs this logger that the runner ended a test case.
     * This will be invoked for failed test cases as well as for successful test cases.
     * Maybe #NULL in case this logger does not implement this function.
     * @param testCase Test case that was ended.
     */
    void(*testCaseEnded)(TestCaseId_t testCase);
#endif

#ifdef ACEUNIT_LOG_FIXTURE
    /** Informs this logger that the runner has ended a fixture.
     * Maybe #NULL in case this logger does not implement this function.
     * @param fixture Fixture that was ended.
     */
    void(*fixtureEnded)(FixtureId_t fixture);
#endif

#ifdef ACEUNIT_LOG_SUITE
    /** Informs this logger that the runner has ended a suite.
     * Maybe #NULL in case this logger does not implement this function.
     */
    void(*suiteEnded)(SuiteId_t const suiteId);
#endif

#ifdef ACEUNIT_LOG_RUNNER
    /** Informs this logger that the runner is about to end.
     * Maybe #NULL in case this logger does not implement this function.
     */
    void(*runnerEnded)(void);
#endif

} TestLogger_t;

/** Declare a logger.
 * Use this macro for declaring instance of #TestLogger_t.
 * Depending on the configuration / environment, this macro may or may not use all of its parameters.
 * @param name Name of the logger to declare, will create a variable with this name and of type #TestLogger_t.
 * @param runnerStarted   Delegates to #TestLogger_t.runnerStarted.
 * @param suiteStarted    Delegates to #TestLogger_t.suiteStarted.
 * @param fixtureStarted  Delegates to #TestLogger_t.fixtureStarted.
 * @param testCaseStarted Delegates to #TestLogger_t.testCaseStarted.
 * @param testCaseFailed  Delegates to #TestLogger_t.testCaseFailed.
 * @param testCaseEnded   Delegates to #TestLogger_t.testCaseEnded.
 * @param fixtureEnded    Delegates to #TestLogger_t.fixtureEnded.
 * @param suiteEnded      Delegates to #TestLogger_t.suiteEnded.
 * @param runnerEnded     Delegates to #TestLogger_t.runnerEnded.
 */
/* TODO if somebody knows a simplier way... */
#if   !defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    testCaseFailed\
}
#elif !defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded\
}
#elif !defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    fixtureStarted,\
    testCaseFailed,\
    fixtureEnded,\
}
#elif !defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    fixtureStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    fixtureEnded,\
}
#elif !defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    suiteStarted,\
    testCaseFailed,\
    suiteEnded,\
}
#elif !defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    suiteStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    suiteEnded\
}
#elif !defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    suiteStarted,\
    fixtureStarted,\
    testCaseFailed,\
    fixtureEnded,\
    suiteEnded\
}
#elif !defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    suiteStarted,\
    fixtureStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    fixtureEnded,\
    suiteEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    testCaseFailed,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    fixtureStarted,\
    testCaseFailed,\
    fixtureEnded,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) && !defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    fixtureStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    fixtureEnded,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    suiteStarted,\
    testCaseFailed,\
    suiteEnded,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) && !defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    suiteStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    suiteEnded,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) && !defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    suiteStarted,\
    fixtureStarted,\
    testCaseFailed,\
    fixtureEnded,\
    suiteEnded,\
    runnerEnded\
}
#elif  defined(ACEUNIT_LOG_RUNNER) &&  defined(ACEUNIT_LOG_SUITE) &&  defined(ACEUNIT_LOG_FIXTURE) &&  defined(ACEUNIT_LOG_TESTCASE)
#define AceUnitNewLogger(name, runnerStarted, suiteStarted, fixtureStarted, testCaseStarted, testCaseFailed, testCaseEnded, fixtureEnded, suiteEnded, runnerEnded) TestLogger_t name = {\
    runnerStarted,\
    suiteStarted,\
    fixtureStarted,\
    testCaseStarted,\
    testCaseFailed,\
    testCaseEnded,\
    fixtureEnded,\
    suiteEnded,\
    runnerEnded\
}
#else
#error Internal error, missing log combination.
#endif

#endif /* ACEUNITLOGGING_H */
