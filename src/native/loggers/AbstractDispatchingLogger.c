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

/** A dispatching logger is a logger which forwards the events to any number of other loggers.
 * This is the base class for such loggers.
 * To subclass this logger, simply provide this during link time, which must be NULL-terminated array of pointers to `struct TestLogger`.
 * @code
 * const struct TestLogger *DispatchingLogger_loggers[] = ...;
 * @endcode
 *
 * @note
 * We're in C, and using an abstract (extern) runtime template variable.
 * Therefore this logger can be subclassed only once.
 *
 * @file
 * @ingroup logger
 */

void DispatchingLogger_runnerStarted(void)
{
    for (const struct TestLogger *logger = loggers; *logger; logger++)
        logger->runnerStarted();
}

void DispatchingLogger_suiteStarted(SuiteId_t const suiteId)
{
    for (struct TestLogger *logger = loggers; *logger; logger++)
        logger->suiteStarted(suiteId);
}

void DispatchingLogger_fixtureStarted(const FixtureId_t fixture)
{
    for (struct TestLogger *logger = loggers; *logger; logger++)
        logger->fixtureStarted(fixture);
}

void DispatchingLogger_testCaseStarted(TestCaseId_t testCase)
{
    for (struct TestLogger *logger = loggers; *logger; logger++)
        logger->testCaseStarted(testCase);
}

void DispatchingLogger_testCaseFailed(const AssertionError_t *error)
{
    for (struct TestLogger *logger = loggers; *logger; logger++)
        logger->testCaseFailed(error);
}

void DispatchingLogger_testCaseEnded(TestCaseId_t testCase)
{
    for (struct TestLogger *logger = loggers; *logger; logger++)
        logger->testCaseEnded(testCase);
}

void DispatchingLogger_fixtureEnded(FixtureId_t fixture)
{
    for (struct TestLogger *logger = loggers; *logger; logger++)
        logger->fixtureEnded(testCase);
}

void DispatchingLogger_suiteEnded(SuiteId_t const suiteId)
{
    for (struct TestLogger *logger = loggers; *logger; logger++)
        logger->suiteEnded(suiteId);
}

void DispatchingLogger_runnerEnded(void)
{
    for (struct TestLogger *logger = loggers; *logger; logger++)
        logger->runnerEnded();
}

/** This Logger. */
AceUnitNewLogger(
    DispatchingLogger,
    DispatchingLogger_runnerStarted,
    DispatchingLogger_suiteStarted,
    DispatchingLogger_fixtureStarted,
    DispatchingLogger_testCaseStarted,
    DispatchingLogger_testCaseFailed,
    DispatchingLogger_testCaseEnded,
    DispatchingLogger_fixtureEnded,
    DispatchingLogger_suiteEnded,
    DispatchingLogger_runnerEnded
);
