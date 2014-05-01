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

#ifndef ACEUNIT_H
/** Include shield to protect the header file from being included more than once. */
#define ACEUNIT_H 1

/** AceUnit header file.
 * You do not need to include this header file in a fixture.
 * The generated header file for your fixture will automatically include it.
 *
 * The following options are supported:
 * <dl>
 *  <dt><code>ACEUNIT_EMBEDDED</code></dt>
 *  <dd>
 *      Define this macro if you want to use AceUnit in embedded mode.
 *      Using AceUnit in embedded mode will use test element ids that are <code>uint16_t</code> instead of <code>char*</code>.
 *      Memory consumption in embedded mode is significantly reduced.
 *      Some non-vital features are not available in embedded mode.
 *      TODO: describe which features are not available in embedded mode.
 *  </dd>
 *  <dt><code>ACEUNIT_C_MODE</code></dt>
 *  <dd>
 *      Set this macro to explicitely specify how AceUnit shall interact with the compiler environment regarding header files.
 *      The following options are possible:
 *      <dl>
 *          <dt><code>ACEUNIT_C_MODE_C99_INCLUDES</code> (default in a C99 environment)</dt>
 *          <dd>This tells AceUnit to include files like <code>&lt;stdint.h&gt;</code> and <code>&lt;stddef.h&gt;</code> to define required symbols like <code>uint16_t</code> or <code>NULL</code>.</dd>
 *          <dt><code>ACEUNIT_C_MODE_C89</code> (default in a C89 environment)</dt>
 *          <dd>This tells AceUnit that neither C99 include files nor replacement definitions are available, so AceUnit shall use its own definitions.<7dd>
 *          <dt><code>ACEUNIT_C_MODE_PROPRIETARY</code></dt>
 *          <dd>This tells AceUnit to assume that the required definitions for symbols like <code>uint16_t</code> or <code>NULL</code> are provided by header files already included by the user before the AceUnit header files.</dd>
 *      </dl>
 *      If you use non-C99 compilers, you should bug your compiler vendor to produce an ISO/IEC 9899/1999 (aka ISO C99) compiler.
 *      As you can correctly guess from this description or have read elsewhere, AceUnit works without problems on C89 compilers.
 *      But it's a shame that even today, about a decade after the release of C99, still only a small minority of compilers actually properly support that standard.
 *      <p>
 *      Note: this replaces ACEUNIT_INTERNAL_ISO_TYPES and ACEUNIT_SKIP_ISO_DEFINES from previous versions of AceUnit.
 *      <p>
 *      Note: If you do not set this macro, AceUnit will make the decision itself.
 *            The default is to assume ACEUNIT_C_MODE_C99_INCLUDES for a C99 environment, ACEUNIT_C_MODE_C89 otherwise.
 *  </dd>
 *  <dt><code>ACEUNIT_STATIC_ANNOTATIONS</code></dt>
 *  <dd>
 *      Define this macro to make AceUnit annotations (#A_Test, #A_Before, #A_After, #A_BeforeClass, #A_AfterClass, #A_Ignore) behave like the <code>static</code> keyword.
 *      That way you have easy and flexible control whether or not test methods are static.
 *      <p>
 *      Declaring test methods as static has a significant advantage.
 *      You will be able to use the same name in different fixtures and still build and run them all together.
 *      For logging, it is not required that test methods have unique names.
 *      Logging will always also include the associated fixture (e.g. filename + line number).
 *      So you will always uniquely identify which test case filed, even if the names of the test cases are not unique.
 *      <p>
 *      However, there are debuggers which will cause head ache if you try to debug functions which are static.
 *      Some tool chains (compilers / linkers) will not emit proper debug information for functions which are static.
 *      <p>
 *      The pros and cons for static test methods are both very significant.
 *      Whether or not you want to use static depends on your environment.
 *      Because of that, we've left the choice to you.
 *      <p>
 *      But we've prepared everything for you.
 *      Toggling between these two options is as simple as (not) defining this macro.
 *      Of course, toggling static off will only be that simple in the real world if the test method names are unique across all fixtures that you link together.
 *      <p>
 *      If you're unsure, a rule of thumb is define either <code>ACEUNIT_EMBEDDED</code> or <code>ACEUNIT_STATIC_ANNOTATIONS</code> but not both.
 *  </dd>
 *  <dt><code>ACEUNIT_CODE_INCLUDE</code></dt>
 *  <dd>
 *      Include this header file before AceUnit Code (only applies to framework, not to test cases / generated code).
 *      Use this if you need to specify section information for your compiler e.g. in an embedded environment.
 *      <p>
 *      Of course you could just modify the AceUnit source code to include the section information.
 *      But it is not recommended to modify the AceUnit source code because it will cause extra work for you if you want to upgrade to a newer version of AceUnit.
 *      Therefore we tried to design AceUnit in a way that you shouldn't need to modify AceUnit's source code to get AceUnit running in your environment.
 *  </dd>
 *  <dt><code>ACEUNIT_DATA_INCLUDE</code></dt>
 *  <dd>
 *      Include this header file before AceUnit Data (only applies to framework, not to test cases / generated code).
 *      Use this if you need to specify section information for your compiler e.g. in an embedded environment.
 *      <p>
 *      Of course you could just modify the AceUnit source code to include the section information.
 *      But it is not recommended to modify the AceUnit source code because it will cause extra work for you if you want to upgrade to a newer version of AceUnit.
 *      Therefore we tried to design AceUnit in a way that you shouldn't need to modify AceUnit's source code to get AceUnit running in your environment.
 *  </dd>
 *  <dt><code>ACEUNIT_DATA_ON_STACK</code></dt>
 *  <dd>
 *      Define this macro to use AceUnit Data on the Stack.
 *      You will then have to initialize #runnerData yourself.
 *      AceUnit doesn't automatically put it on the stack itself because you might want to access the results from where you invoked the runner.
 *  </dd>
 *  <dt><code>ACEUNIT_SUITES</code></dt>
 *  <dd>
 *      Define this macro to use AceUnit with support for Suites.
 *  </dd>
 *  <dt><code>ACEUNIT_PRE_BEFORECLASS</code></dt>
 *  <dd>
 *      If you want AceUnit to execute code before every beforeclass method, define this macro with that code.
 *  </dd>
 *  <dt><code>ACEUNIT_POST_BEFORECLASS</code></dt>
 *  <dd>
 *      If you want AceUnit to execute code after every beforeclass method, define this macro with that code.
 *  </dd>
 *  <dt><code>ACEUNIT_PRE_BEFORE</code></dt>
 *  <dd>
 *      If you want AceUnit to execute code before every before method, define this macro with that code.
 *  </dd>
 *  <dt><code>ACEUNIT_POST_BEFORE</code></dt>
 *  <dd>
 *      If you want AceUnit to execute code after every before method, define this macro with that code.
 *  </dd>
 *  <dt><code>ACEUNIT_PRE_TEST</code></dt>
 *  <dd>
 *      If you want AceUnit to execute code before every test method, define this macro with that code.
 *  </dd>
 *  <dt><code>ACEUNIT_POST_TEST</code></dt>
 *  <dd>
 *      If you want AceUnit to execute code after every test method, define this macro with that code.
 *  </dd>
 *  <dt><code>ACEUNIT_PRE_AFTER</code></dt>
 *  <dd>
 *      If you want AceUnit to execute code before every after method, define this macro with that code.
 *  </dd>
 *  <dt><code>ACEUNIT_POST_AFTER</code></dt>
 *  <dd>
 *      If you want AceUnit to execute code after every after method, define this macro with that code.
 *  </dd>
 *  <dt><code>ACEUNIT_PRE_AFTERCLASS</code></dt>
 *  <dd>
 *      If you want AceUnit to execute code before every afterclass method, define this macro with that code.
 *  </dd>
 *  <dt><code>ACEUNIT_POST_AFTERCLASS</code></dt>
 *  <dd>
 *      If you want AceUnit to execute code after every afterclass method, define this macro with that code.
 *  </dd>
 *  <dt><code>ACEUNIT_RUNNERDATA_EXTENSION</code></dt>
 *  <dd>
 *      If you want to add additional data to the data available to the runner, define this macro.
 *      The macro should expand to valid fields in a structure.
 *      These fields will be inserted at the end of #AceUnitRunnerData_t.
 *  </dd>
 *  <dt><code>ACEUNIT_CONFIG_FILE</code></dt>
 *  <dd>
 *      If you want to configure AceUnit more comfortably than with defines passed via make to your compiler, you can define this macro.
 *      The macro then must evaluate to a valid include file.
 *  </dd>
 *  <dt><code>ACEUNIT_SETJMP_INCLUDE</code></dt>
 *  <dd>
 *      If you want AceUnit to use setjmp / longjmp but want it to include a different file than <code>&lt;setjmp.h&gt;</code>, define this macro.
 *      The macro then must evaluate to a valid include file.
 *  </dd>
 *  <dt><code>ACEUNIT_SKIP_SETJMP_INCLUDE</code></dt>
 *  <dd>
 *      If you want AceUnit to use setjmp / longjmp but do not want AceUnit to automatically include any file for it, define this macro.
 *  </dd>
 *  <dt><code>ACEUNIT_LOOP</code></dt>
 *  <dd>
 *      This feature enables <code>A_Loop</code> annotation support.
 *      <code>A_Loop</code> support is independent of the generator.
 *      You may turn <code>A_Loop</code> support on and off during compile time without having to rerun the generator.
 *  </dd>
 *  <dt><code>ACEUNIT_EXPLICIT_MESSAGES</code></dt>
 *  <dd>
 *      This feature enables explicit message support.
 *      That means assertions which have an expected and an actual value will report those values.
 *      For this feature to work, a message buffer which can be used by snprintf is required.
 *      Currently, only snprintf is supported.
 *      sprintf and _snprintf are not yet supported.
 *  </dd>
 *  <dt><code>ACEUNIT_EXPLICIT_MESSAGES_INLINE_BUFFER</code></dt>
 *  <dd>
 *      This means that the structure #AceUnitRunnerData_t directly contains the buffer for message formatting.
 *      Otherwise the structure only contains a pointer which has to be initialized by the user.
 *  </dd>
 * </dl>
 *
 * @warning AceUnit can define types for itself for exotic compilation environments where standard includes are not available or shall not be used.
 *          But though AceUnit can do that, this is strongly deprecated.
 *          This will certainly cause a lot of problems:
 *          - AceUnit "guesses" the types by assuming <code>short int</code> to be 16 bit and <code>long int</code> to be 32 bit.
 *            Especially about the second assumption AceUnit could be wrong.
 *          - Tools like lint are very picky about type definitions.
 *            For lint it makes a difference if a type of size 16 bit is defined as <code>short int</code> or <code>int</code>.
 *            For sure lint will find something to complain about if you let AceUnit define its own types instead of providing consistent types from your compilation environment.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file AceUnit.h
 */

#ifdef ACEUNIT_CONFIG_FILE
#include ACEUNIT_CONFIG_FILE
#endif

/* Auto-definition of ACEUNIT_C_MODE if it is not defined. */
#if !defined(ACEUNIT_C_MODE)
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
/* C99 or better environment: Default to using C99. */
#define ACEUNIT_C_MODE ACEUNIT_C_MODE_C99_INCLUDES
#else
/* <C99: Use its own definitions. */
#define ACEUNIT_C_MODE ACEUNIT_C_MODE_C89
#endif
#endif

/** Value for #ACEUNIT_C_MODE for including C99 standard header files. */
#define ACEUNIT_C_MODE_C99_INCLUDES 1

/** Value for #ACEUNIT_C_MODE for using AceUnit's own replacement definitions. */
#define ACEUNIT_C_MODE_C89 2

/** Value for #ACEUNIT_C_MODE for providing proprietary replacement definitions by the user. */
#define ACEUNIT_C_MODE_PROPRIETARY 3

#if ACEUNIT_C_MODE == ACEUNIT_C_MODE_C99_INCLUDES
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#elif ACEUNIT_C_MODE == ACEUNIT_C_MODE_C89
#ifndef __int8_t_defined
#define __int8_t_defined
/** Replacement for stdint.h int8_t in case stdint.h is not available. */
typedef signed char int8_t;
/** Replacement for stdint.h int16_t in case stdint.h is not available. */
typedef signed short int int16_t;
/** Replacement for stdint.h int32_t in case stdint.h is not available. */
typedef signed long int int32_t;
/** Replacement for stdint.h uint8_t in case stdint.h is not available. */
typedef unsigned char uint8_t;
/** Replacement for stdint.h uint16_t in case stdint.h is not available. */
typedef unsigned short int uint16_t;
/** Replacement for stdint.h uint32_t in case stdint.h is not available. */
typedef unsigned long int uint32_t;
#endif
#ifndef _SIZE_T_DEFINED
#ifndef _SIZE_T_DEFINED_
/** Replacement for stddef.h size_t in case stddef.h is not available. */
typedef long unsigned int size_t;
#endif
#endif
#ifndef __bool_true_false_are_defined
/** Replacement for stdbool.h bool in case stdbool.h is not available. */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define bool _Bool
#elif !defined(__cplusplus)
typedef int bool;
#endif
/** Replacement for stdbool.h true in case stdbool.h is not available. */
#define true 1
/** Replacement for stdbool.h false in case stdbool.h is not available. */
#define false 0
/** Replacement for stdbool.h __bool_true_false_are_defined in case stdbool.h is not available. */
#define __bool_true_false_are_defined 1
#endif
#ifndef NULL
/** Replacement for stddef.h NULL in case stddef.h is not available. */
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *) 0)
#endif
#endif
#elif ACEUNIT_C_MODE == ACEUNIT_C_MODE_PROPRIETARY
/* no definitions for proprietary mode */
#else
#error Unknown value for ACEUNIT_C_MODE
#endif

#include "AceUnitAnnotations.h"

/** Value for #ACEUNIT_ASSERTION_STYLE for using <code>return</code> for assertions to abort test cases.
 * This is primarily meant for embedded systems where everything should be as small and simple as possible.
 * It is also currently used by AceUnit when AceUnit tests itself.
 *
 * @warning This assertion style has a severe disadvantage.
 * Assertions in this style will only work as expected if the assertion appears directly in the test case.
 * If an assertion is placed in a function invoked from a test case, the assertion error will be stored.
 * But the test case will not be aborted.
 * If another assertion occurs it will overwrite the previous assertion even before the assertion is logged.
 * Also if the remaining code of the test case would run wild if the assertion failed, it will as it is not aborted.
 * Therefore you SHOULD NOT use this assertion style unless you really explicitely want it.
 *
 * @see #ACEUNIT_ASSERTION_STYLE
 */
#define ACEUNIT_ASSERTION_STYLE_RETURN 1

/** Value for #ACEUNIT_ASSERTION_STYLE for using <code>assert</code> for assertions to abort test cases.
 * It will use <code>assert.h</code> from ISO C.
 * Because of that do not define <code>NDEBUG</code>.
 *
 * @warning If you define <code>NDEBUG</code> with this assertion style, assertions will not work as expected.
 * The test case will not be aborted.
 * If another assertion occurs it will overwrite the previous assertion even before the assertion is logged.
 * Therefore you MUST NOT define <code>NDEBUG</code> with this assertion style.
 *
 * @note If you use this assertion style, the first assertion will invoke <code>assert()</code> and therefore exit the test program.
 * Normal logging is useless in conjunction with this assertion style.
 * This assertion style is especially useful for debugging when <code>assert()</code> is useful in your debugging environment.
 *
 * @todo instead of exiting, optionally catch SIGABRT with a signal handler
 *
 * @see #ACEUNIT_ASSERTION_STYLE
 */
#define ACEUNIT_ASSERTION_STYLE_ASSERT 2

/** Value for #ACEUNIT_ASSERTION_STYLE for using <code>abort()</code> for assertions to abort.
 * It will use <code>stdlib.h</code> from ISO C.
 *
 * @note If you use this assertion style, the first assertion will invoke <code>abort()</code> and therefore exit the test program.
 * Normal logging is useless in conjunction with this assertion style.
 *
 * @todo instead of exiting, optionally catch SIGABRT with a signal handler
 *
 * @see #ACEUNIT_ASSERTION_STYLE
 */
#define ACEUNIT_ASSERTION_STYLE_ABORT 3

/** Value for #ACEUNIT_ASSERTION_STYLE for using <code>longjmp()</code> for assertions to abort.
 * It will use <code>setjmp.h</code> from ISO C.
 *
 * This is the preferred assertion style and therefore default for AceUnit.
 *
 * @see #ACEUNIT_ASSERTION_STYLE
 */
#define ACEUNIT_ASSERTION_STYLE_LONGJMP 4

/** Value for #ACEUNIT_ASSERTION_STYLE for using custom assertion aborts.
 * If you use this for #ACEUNIT_ASSERTION_STYLE, you also MUST define the macro #ACEUNIT_CUSTOM_ASSERT to the code you want to use to make assertions abort test cases.
 *
 * @see #ACEUNIT_ASSERTION_STYLE
 */
#define ACEUNIT_ASSERTION_STYLE_CUSTOM 5

#ifndef ACEUNIT_ASSERTION_STYLE
/** Determines the style of assertions to use.
 * Defaults to #ACEUNIT_ASSERTION_STYLE_CUSTOM if ACEUNIT_CUSTOM_ASSERT is defined.
 * Defaults to #ACEUNIT_ASSERTION_STYLE_LONGJMP otherwise.
 *
 * @see #ACEUNIT_ASSERTION_STYLE_RETURN
 * @see #ACEUNIT_ASSERTION_STYLE_ASSERT
 * @see #ACEUNIT_ASSERTION_STYLE_ABORT
 * @see #ACEUNIT_ASSERTION_STYLE_LONGJMP
 * @see #ACEUNIT_ASSERTION_STYLE_CUSTOM
 */
#ifdef ACEUNIT_CUSTOM_ASSERT
#define ACEUNIT_ASSERTION_STYLE ACEUNIT_ASSERTION_STYLE_CUSTOM
#else
#define ACEUNIT_ASSERTION_STYLE ACEUNIT_ASSERTION_STYLE_LONGJMP
#endif
#endif

#if ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_CUSTOM
#ifndef ACEUNIT_CUSTOM_ASSERT
#error You MUST define ACEUNIT_CUSTOM_ASSERT when using ACEUNIT_ASSERTION_STYLE_CUSTOM.
#endif
#endif

/* Abort style specific configuration. */
#if ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_RETURN
    /* nothing special */
#elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_ASSERT
    #include <assert.h>
#elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_ABORT
    #include <stdlib.h>
#elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_LONGJMP
    #ifdef ACEUNIT_SETJMP_INCLUDE
    #include ACEUNIT_SETJMP_INCLUDE
    #elif defined(ACEUNIT_SKIP_SETJMP_INCLUDE)
    #else
    #include <setjmp.h>
    #endif
#elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_CUSTOM
    /* nothing special */
#else
    #error Unknown value for ACEUNIT_ASSERTION_STYLE.
#endif

/** Code for aborting a test case in case of an assertion. */
#if ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_RETURN
    #define ACEUNIT_ABORT return
#elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_ASSERT
    #define ACEUNIT_ABORT assert(0)
#elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_ABORT
    #define ACEUNIT_ABORT abort()
#elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_LONGJMP
    #define ACEUNIT_ABORT longjmp(runnerData->jmpBuf, 1)
#elif ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_CUSTOM
    #define ACEUNIT_ABORT ACEUNIT_CUSTOM_ASSERT
#else
    #error Unexpected internal error.
#endif

/** TestId_t specifies a test. */
typedef uint16_t AceTestId_t;

/** Special value for #AceTestId_t that specifies no test.
 * The value is zero.
 * This value can be used to terminate vectors of #AceTestId_t values.
 */
#define NO_TEST ((AceTestId_t) 0)

/** Special value for #AceTestId_t that specifies all tests.
 * The value is all bits set.
 * This value can be used in #AceTestId_t values.
 */
#define ALL_TESTS ((AceTestId_t) -1)

/** GroupId_t specifies a group. */
typedef uint16_t AceGroupId_t;

/** SuiteId_t specifies a test suite.
 * On embedded systems, this is a 16 bit quantity that uniquely identifies the test suite.
 * On normal systems, this is the directory name of the suite.
 * @note Fixtures also are Suites.
 */
typedef AceTestId_t SuiteId_t;

/** FixtureId_t specifies a test fixture.
 * On embedded systems, this is a 16 bit quantity that uniquely identifies the test fixture.
 * On normal systems, this is the filename of fixture.
 */
typedef SuiteId_t FixtureId_t;

/** TestCaseId_t specifies a test case.
 * On embedded systems, this is a 16 bit quantity that uniquely identifies the test case within its fixture.
 * On normal systems, this is the function name of the test case.
 */
typedef AceTestId_t TestCaseId_t;

/** The value for something of type #TestCaseId_t for denoting no testcase. */
#define TestCaseId_NULL 0

/** The type to use for line numbers. */
#ifdef ACEUNIT_EMBEDDED
typedef uint16_t linenumber_t;
#else
typedef int linenumber_t;
#endif

/** AssertionId_t specifies an assertion failure within a test case.
 * On embedded systems, this is the line number.
 * On normal systems, this is the line number and the message text of the assertion.
 */
typedef struct {

    /** The line number at which the assertion occurred. */
    linenumber_t lineNumber;

#ifndef ACEUNIT_EMBEDDED
    /** The message of the assertion. */
    const char *message;
#endif

} AssertionId_t;

/** Creates a new assertion error.
 * @param message Message to create.
 */
#ifdef ACEUNIT_EMBEDDED
#define newAssertionError(message) { AssertionId_t assertion = { __LINE__ }; recordError(A_FIXTURE_ID, assertion); } ACEUNIT_ABORT
#else
#define newAssertionError(message) { AssertionId_t assertion = { __LINE__, message }; recordError(A_FIXTURE_ID, assertion); } ACEUNIT_ABORT
#endif

/** Assertion Error.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
typedef struct {

    /** The id of the fixture that contains the test case of the failed assertion. */
    FixtureId_t fixtureId;

    /** The id of the test case of the failed assertion. */
    TestCaseId_t testId;

    /** The assertion id. */
    AssertionId_t assertionId;

} AssertionError_t;

#include "AceUnitAssert.h"

/** Method signature for annotated test methods.
 * @see #A_Test
 * @see #A_Before
 * @see #A_After
 * @see #A_BeforeClass
 * @see #A_AfterClass
 * @see #A_Ignore
 */
typedef void(*testMethod_t)(void);

/** A Suite is a loose collection of test cases.
 * It consists of other suites and fixtures.
 */
typedef struct TestSuite_tt {

    /* Implementation note: Take care that the beginning of TestSuite_t is identical to that of TestFixture_t! */

    /** The Id of this suite. */
    SuiteId_t const id;

#ifndef ACEUNIT_EMBEDDED
    /** The name of this suite. */
    const char *name;
#endif

    /** The suites that are contained in this suite.
     * If this Suite is a Fixture, this value is NULL.
     */
    const struct TestSuite_tt *const *const suites;

} TestSuite_t;

#ifdef ACEUNIT_LOOP
/** Type for a loop in AceUnit. */
typedef uint16_t aceunit_loop_t;
#endif

/** A Fixture is a collection of test cases sharing the same before, after, beforeClass and afterClass methods.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
typedef struct {

    /* Implementation note: Take care that the beginning of TestFixture_t is identical to that of TestSuite_t! */

    /** The Id of this fixture. */
    FixtureId_t const id;

#ifndef ACEUNIT_EMBEDDED
    /** The name of this fixture. */
    const char *const name;
#endif

#ifdef ACEUNIT_SUITES
    /** The suites that are contained in this fixture.
     * This is a fixture, thus this value always is NULL.
     */
    const TestSuite_t *const *const suites;
#endif

    /** The ids of the test cases of this test fixture. */
    const TestCaseId_t *const testIds;

#ifndef ACEUNIT_EMBEDDED
    /** The names of the test cases of this test fixture. */
    const char *const *const testNames;
#endif

#ifdef ACEUNIT_LOOP
    /** The test cases that shall be looped. */
    const aceunit_loop_t *const loops;
#endif

#ifdef ACEUNIT_GROUP
    /** The test groups to which each test case belongs. */
    const AceGroupId_t *const groups;
#endif

    /** The test cases of this test fixture. */
    const testMethod_t *const testCase;

    /** The before methods of this test fixture. */
    const testMethod_t *const before;

    /** The after methods of this test fixture. */
    const testMethod_t *const after;

    /** The beforeClass methods of this test fixture. */
    const testMethod_t *const beforeClass;

    /** The afterClass methods of this test fixture. */
    const testMethod_t *const afterClass;

} TestFixture_t;

/** Records an error.
 * @param fixtureId    Id of the fixture that contained the test case with the failed assertion.
 * @param assertionId  Id of the assertion that failed.
 */
extern void recordError(const FixtureId_t fixtureId, const AssertionId_t assertionId);

/** Runs all test cases from a test fixture.
 * @param fixture  Test fixture to run.
 * @param group Group to run.
 *              This parameter is only available if #ACEUNIT_GROUP is defined.
 */
#if defined(ACEUNIT_GROUP) || defined(_doxygen)
extern void runFixture(const TestFixture_t *const fixture, AceGroupId_t group);
#else
extern void runFixture(const TestFixture_t *const fixture);
#endif

/** Runs all test cases from a test suite.
 * @param suite  Test suite to run.
 * @param group Group to run.
 *              This parameter is only available if #ACEUNIT_GROUP is defined.
 */
#if defined(ACEUNIT_GROUP) || defined(_doxygen)
extern void runSuite(const TestSuite_t *const suite, AceGroupId_t group);
#else
extern void runSuite(const TestSuite_t *const suite);
#endif

#ifdef ACEUNIT_SUITES
/** First suite - entry point. */
extern const TestSuite_t sutie1;
#endif

#if ACEUNIT_ASSERTION_STYLE == ACEUNIT_ASSERTION_STYLE_LONGJMP
#include "AceUnitData.h"
#endif

#endif /* ACEUNIT_H */
