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

/** Full Logger implementation that logs plain text messages to `stderr`.
 * The format of the messages is suitable for processing in popular text editors like EMacs or Vim.
 * It is the same as that of error messages yielded by most popular compilers like gcc or javac.
 * The format is:
 * <p><code><var>filename</var>:<var>linenumber</var>: error: in <var>symbolnname</var>: <var>message</var></p>
 * For example:
 * <p><samp>foo.c:30: error: Expected X to be 15 but was 13.</samp></p>
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file FullPlainLogger.c
 */

#include <stdio.h>

#include "AceUnit.h"
#include "AceUnitLogging.h"

extern char *__progname;

/** Logs a message using this logger.
 * @param recentError Error to log.
 */
void FullPlainLoggerLog(const AssertionError_t *const recentError) {
#ifdef ACEUNIT_EMBEDDED
#error "FullPlainLogger does not support embedded AceUnit."
#else
    fprintf(stderr, "%s:%d: error: in %d: %s\n", recentError->assertionId.filename, (int) recentError->assertionId.lineNumber, (int) recentError->testId, recentError->assertionId.message);
#endif
}

void FullPlainLoggerRunnerStarted(void) {
    fprintf(stderr, "%s: info: Testing Started.\n", __progname);
}

void FullPlainLoggerSuiteStarted(SuiteId_t const suiteId) {
    fprintf(stderr, "%s: info: Suite %d started.\n", __progname, suiteId);
}

void FullPlainLoggerFixtureStarted(const FixtureId_t fixtureId) {
    fprintf(stderr, "%s: info: Fixture %d started.\n", __progname, fixtureId);
}

void FullPlainLoggerTestCaseStarted(TestCaseId_t testCaseId) {
    fprintf(stderr, "%s: info: Test Case %d started.\n", __progname, testCaseId);
}

void FullPlainLoggerTestCaseEnded(TestCaseId_t testCaseId) {
    fprintf(stderr, "%s: info: Test Case %d ended.\n", __progname, testCaseId);
}

void FullPlainLoggerFixtureEnded(FixtureId_t fixtureId) {
    fprintf(stderr, "%s: info: Fixture %d ended.\n", __progname, fixtureId);
}

void FullPlainLoggerSuiteEnded(SuiteId_t const suiteId) {
    fprintf(stderr, "%s: info: Suite %d ended.\n", __progname, suiteId);
}

void FullPlainLoggerRunnerEnded(void) {
    fprintf(stderr, "%s: info: Runner ended.\n", __progname);
}

/** This Logger. */
AceUnitNewLogger(
    FullPlainLogger,
    FullPlainLoggerRunnerStarted,
    FullPlainLoggerSuiteStarted,
    FullPlainLoggerFixtureStarted,
    FullPlainLoggerTestCaseStarted,
    FullPlainLoggerLog,
    FullPlainLoggerTestCaseEnded,
    FullPlainLoggerFixtureEnded,
    FullPlainLoggerSuiteEnded,
    FullPlainLoggerRunnerEnded
);

TestLogger_t *globalLogger = &FullPlainLogger; /* XXX Hack. Remove. */
