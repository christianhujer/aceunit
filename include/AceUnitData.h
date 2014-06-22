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

#ifndef ACEUNITDATA_H
/** Include shield to protect the header file from being included more than once. */
#define ACEUNITDATA_H 1

#include "AceUnit.h"

/** AceUnitData header file.
 * This is only needed when you need to access information used by the runner.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file AceUnitData.h
 */

/** Structure with test execution information, used by the Runner and the Assertions. */
typedef struct {

    /** The most recent error will be remembered here.
     * This variable will be set by #recordError()} and read by {@link #runFixture().
     * It is set to NULL before each test case.
     * If it is not NULL after a test case, the test case failed.
     */
    AssertionError_t *recentError;

    /** This is the most recent error. */
    AssertionError_t recentErrorData;

    /** The id of the currently executed test case.
     * This variable will be set by #runFixture()} and read by {@link #recordError().
     */
    TestCaseId_t currentTestId;

    /** The number of test cases that were executed. */
    uint16_t testCaseCount;

    /** The number of test cases that failed. */
    uint16_t testCaseFailureCount;

#if ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_LONGJMP
    /** Jump Buffer for AceUnit to abort a test case and jump back to the runner. */
    jmp_buf jmpBuf;
#endif

#ifdef ACEUNIT_EXPLICIT_MESSAGES
    /** The temporary buffer for message formatting. */
#ifdef ACEUNIT_EXPLICIT_MESSAGES_INLINE_BUFFER
    char explicitMsgBuf[ACEUNIT_EXPLICIT_MSG_BUF_SIZE];
#else
    char *explicitMsgBuf;
#endif
#endif
#ifdef ACEUNIT_RUNNERDATA_EXTENSION
    /* Extension hook to add your own fields to AceUnitRunnerData_t. */
    ACEUNIT_RUNNERDATA_EXTENSION
#endif

} AceUnitRunnerData_t;

/** The test execution information, used by the Runner and the Assertions. */
extern AceUnitRunnerData_t *runnerData;

#endif /* ACEUNITDATA_H */
