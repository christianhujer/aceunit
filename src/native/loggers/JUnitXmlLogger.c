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

/** The JUnitXmlLogger is a {@link TestLogger_t} implementation that writes a test log that is compatible with that of JUnit when using XML log format.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file JUnitXmlLogger.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "AceUnit.h"
#include "AceUnitLogging.h"

/** Returns the host name of the host this test is executed on.
 * @return Host name
 */
static char *getHostname() {
    char *hostname;
    hostname = getenv("HOSTNAME");
    if (NULL == hostname) {
        hostname = getenv("COMPUTERNAME");
    }
    if (NULL == hostname) {
        hostname = "unknown";
    }
    return hostname;
}

/** The name of the global file.
 * Do not change this without really thinking about: It is intentionally the same as that of JUnit / the JUnit Ant task.
 */
#define GLOBAL_FILE_NAME "TESTS-TestSuites.xml"

/** The file TESTS-TestSuites.xml which contains the accumulated log information of all test suites. */
static FILE *globalFile = NULL;

/** The global information recorded by this logger. */
static struct {
    char    *hostname;
    int     suiteId;
} globalInfo = {
    0
};

/** The information about the current suite. */
static struct {
    int     errors;
    int     failures;
    int     id;
    char    *name;
    char    *package;
    char    *fullname;
    int     tests;
    float   time;
    char    *timestamp;
} suiteInfo = {
    0,
};

/** Initializes all global variables and prepares global log file output.
 * @see TestLogger_t#runnerStarted()}
 */
static void runnerStarted() {
    globalFile = fopen(GLOBAL_FILE_NAME, "w");
    fprintf(globalFile, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
    fprintf(globalFile, "<testsuites>\n");
    fflush(globalFile);
    globalInfo.hostname = getHostname();
    globalInfo.suiteId = 0;
}

/** Initializes suite-specific variables.
 * @see TestLogger_t#suiteStarted()}
 */
static void suiteStarted(SuiteId_t const suiteId) {
    suiteInfo.errors = 0;
    suiteInfo.failures = 0;
    suiteInfo.id = globalInfo.suiteId++;
}

/** Initializes fixture-specific variables.
 * @see TestLogger_t#fixtureStarted()}
 */
static void fixtureStarted(const FixtureId_t fixture) {
    suiteInfo.package = NULL; /* TODO */
    suiteInfo.name = NULL; /* TODO */
    suiteInfo.tests = 0; /* TODO */
    suiteInfo.timestamp = NULL; /* TODO */
}

/** @see TestLogger_t#testCaseStarted()} */
static void testCaseStarted(TestCaseId_t testCase) {
}

/** @see TestLogger_t#testCaseFailed()} */
static void testCaseFailed(const AssertionError_t *assertion) {
}

/** @see TestLogger_t#testCaseEnded()} */
static void testCaseEnded(TestCaseId_t testCase) {
}

/** @see TestLogger_t#fixtureEnded()} */
static void fixtureEnded(FixtureId_t fixture) {
}

/** Prints the environment as properties XML element to the specified file.
 * @param file File to print to
 */
static void printEnvAsProperties(FILE *file) {
#ifdef ACEUNIT_JUNITXMLLOGGER_ENVIRONMENT
    extern char **environ;
    char **env = environ;
    size_t i;
    if (NULL == *env) {
#endif
        fprintf(globalFile, "    <properties/>\n");
#ifdef ACEUNIT_JUNITXMLLOGGER_ENVIRONMENT
    } else {
        fprintf(globalFile, "    <properties>\n");
        for (; NULL != *env; env++) {
            char *ptr = *env;
            fprintf(globalFile, "    <property name=\"");
            for (i = 0; i < strlen(ptr); i++) {
                if ('=' == ptr[i]) {
                    break;
                }
            }
            fwrite(*ptr, sizeof(char), i, globalFile);
            ptr += i + 1;
            fprintf(globalFile, "\" value=\"");
            fwrite(*ptr, sizeof(char), strlen(ptr), globalFile);
            fprintf(globalFile, "\" />\n");
        }
        fprintf(globalFile, "    </properties>\n");
    }
#endif
}

/** @see TestLogger_t#suiteEnded()} */
static void suiteEnded(SuiteId_t const suiteId) {
    int i;
    FILE *localFile;
    /* <testsuite errors="0" failures="0" hostname="riedquat" id="1" name="BasicCommandTest" package="test.net.sf.japi.io.args" tests="10" time="0.105" timestamp="2007-11-06T20:15:24"> */
    fprintf(globalFile, "  <testsuite errors=\"%d\" failures=\"%d\" hostname=\"%s\" id=\"%d\" name=\"%s\" package=\"%s\" tests=\"%d\" time=\"%f\" timestamp=\"%s\">\n", 0/*TODO*/, 0/*TODO*/, globalInfo.hostname, 0/*TODO*/, ""/*TODO*/, ""/*TODO*/, 0/*TODO*/, 0.0/*TODO*/, ""/*TODO*/);
    printEnvAsProperties(globalFile);
    for (i = 0; i < suiteInfo.tests; i++) {
      /*<testcase classname="test.net.sf.japi.io.args.BasicCommandTest" name="testHelp" time="0.0090" />*/
        fprintf(globalFile, "    <testcase classname=\"%s\" name=\"%s\" time=\"%f\" />\n", ""/*TODO*/, ""/*TODO*/, 0.0/*TODO*/);
    }
    fprintf(globalFile, "    <system-out/>\n");
    fprintf(globalFile, "    <system-err/>\n");
    fprintf(globalFile, "  </testsuite>\n");
    fflush(globalFile);

    localFile = fopen("TEST-test.net.sf.japi.io.args.ArgParserTest.xml", "w"); /* TODO: configure filename */
    /* <testsuite errors="0" failures="0" hostname="riedquat" name="test.net.sf.japi.io.args.ArgParserTest" tests="19" time="3.463" timestamp="2007-11-06T20:15:21"> */
    fprintf(localFile, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
    fprintf(localFile, "<testsuite errors=\"%d\" failures=\"%d\" hostname=\"%s\" name=\"%s\" tests=\"%d\" time=\"%f\" timestamp=\"%s\">\n", 0/*TODO*/, 0/*TODO*/, globalInfo.hostname, ""/*TODO*/, 0/*TODO*/, 0.0/*TODO*/, ""/*TODO*/);
    fprintf(localFile, "  <properties/>\n"); /* TODO: encode environment as properties? */
    for (i = 0; i < suiteInfo.tests; i++) {
        /* <testcase classname="test.net.sf.japi.io.args.ArgParserTest" name="testSimpleParseAndRun" time="0.0080" /> */
        fprintf(localFile, "    <testcase classname=\"%s\" name=\"%s\" time=\"%f\" />\n", ""/*TODO*/, ""/*TODO*/, 0.0/*TODO*/);
    }
    fprintf(localFile, "  <system-out/>\n");
    fprintf(localFile, "  <system-err/>\n");
    fprintf(localFile, "</testsuite>\n");
    fclose(localFile);
}

/** @see TestLogger_t#runnerEnded()} */
static void runnerEnded() {
    fprintf(globalFile, "</testsuites>\n");
    fclose(globalFile);
}

/** This Logger. */
AceUnitNewLogger(
    JUnitXmlLogger,
    runnerStarted,
    suiteStarted,
    fixtureStarted,
    testCaseStarted,
    testCaseFailed,
    testCaseEnded,
    fixtureEnded,
    suiteEnded,
    runnerEnded
);

TestLogger_t *globalLogger = &JUnitXmlLogger; /* XXX Hack. Remove. */
