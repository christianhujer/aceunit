#include "AceUnitLogging.h"

#ifdef ACEUNIT_LOG_RUNNER
/** @see TestLogger_t.runnerStarted */
void logRunnerStarted()
{
}
#endif

#ifdef ACEUNIT_LOG_SUITE
/** @see TestLogger_t.suiteStarted */
void logSuiteStarted()
{
}
#endif

#ifdef ACEUNIT_LOG_FIXTURE
/** @see TestLogger_t.fixtureStarted */
void logFixtureStarted(const FixtureId_t fixture)
{
}
#endif

#ifdef ACEUNIT_LOG_TESTCASE
/** @see TestLogger_t.testCaseStarted */
void logTestCaseStarted(TestCaseId_t testCase)
{
}
#endif

/** @see TestLogger_t.testCaseCailed */
void logTestCaseFailed(const AssertionError_t *error)
{
}

#ifdef ACEUNIT_LOG_TESTCASE
/** @see TestLogger_t.testCaseEnded */
void logTestCaseEnded(TestCaseId_t testCase)
{
}
#endif

#ifdef ACEUNIT_LOG_FIXTURE
void logFixtureEnded(const FixtureId_t fixture)
{
}
#endif

#ifdef ACEUNIT_LOG_SUITE
/** @see TestLogger_t.suiteEnded */
void logSuiteEnded()
{
}
#endif

#ifdef ACEUNIT_LOG_RUNNER
/** @see TestLogger_t.runnerEnded */
void logRunnerEnded()
{
}
#endif

/** This Logger. */
AceUnitNewLogger(
    loggerStub, /* CHANGE THIS NAME!!! */
    logRunnerStarted,
    logSuiteStarted,
    logFixtureStarted,
    logTestCaseStarted,
    logTestCaseFailed,
    logTestCaseEnded,
    logFixtureEnded,
    logSuiteEnded,
    logRunnerEnded
);

TestLogger_t *globalLogger = &loggerStub; /* XXX Hack. Remove. */

