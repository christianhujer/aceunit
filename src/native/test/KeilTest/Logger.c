#include "AceUnitLogging.h"

#ifdef ACEUNIT_LOG_RUNNER
/** @see TestLogger_t.runnerStarted */
void logRunnerStarted()
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
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    logRunnerEnded
);

TestLogger_t *globalLogger = &loggerStub; /* XXX Hack. Remove. */

