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

#include "AceUnitLogging.h"

/* This file is a stub for a logger.
 * If you need just one logger in your AceUnit environment then this stub is ideal for you.
 * Copy it and fill the methods with your needs for logging.
 * E.g. if your testling (and thus your tests) run inside an embedded device, you might be interested in logging through a debug interface.
 */

#ifdef ACEUNIT_LOG_RUNNER
/** @see TestLogger_t.runnerStarted */
void AceUnitLoggerStub_runnerStarted()
{
}
#endif

#ifdef ACEUNIT_LOG_SUITE
/** @see TestLogger_t.suiteStarted */
void AceUnitLoggerStub_suiteStarted()
{
}
#endif

#ifdef ACEUNIT_LOG_FIXTURE
/** @see TestLogger_t.fixtureStarted */
void AceUnitLoggerStub_fixtureStarted(const FixtureId_t fixture)
{
}
#endif

#ifdef ACEUNIT_LOG_TESTCASE
/** @see TestLogger_t.testCaseStarted */
void AceUnitLoggerStub_testCaseStarted(TestCaseId_t testCase)
{
}
#endif

/** @see TestLogger_t.testCaseCailed */
void AceUnitLoggerStub_testCaseFailed(const AssertionError_t *error)
{
}

#ifdef ACEUNIT_LOG_TESTCASE
/** @see TestLogger_t.testCaseEnded */
void AceUnitLoggerStub_testCaseEnded(TestCaseId_t testCase)
{
}
#endif

#ifdef ACEUNIT_LOG_FIXTURE
void AceUnitLoggerStub_fixtureEnded(const FixtureId_t fixture)
{
}
#endif

#ifdef ACEUNIT_LOG_SUITE
/** @see TestLogger_t.suiteEnded */
void AceUnitLoggerStub_suiteEnded()
{
}
#endif

#ifdef ACEUNIT_LOG_RUNNER
/** @see TestLogger_t.runnerEnded */
void AceUnitLoggerStub_runnerEnded()
{
}
#endif

/** This Logger. */
AceUnitNewLogger(
    AceUnitLoggerStub_instance,
    AceUnitLoggerStub_runnerStarted,
    AceUnitLoggerStub_suiteStarted,
    AceUnitLoggerStub_fixtureStarted,
    AceUnitLoggerStub_testCaseStarted,
    AceUnitLoggerStub_testCaseFailed,
    AceUnitLoggerStub_testCaseEnded,
    AceUnitLoggerStub_fixtureEnded,
    AceUnitLoggerStub_suiteEnded,
    AceUnitLoggerStub_runnerEnded
);

TestLogger_t *globalLogger = &AceUnitLoggerStub_instance; /* XXX Hack. Remove. */
