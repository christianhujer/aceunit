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

#ifndef ACEUNITANNOTATIONS_H
/** Include shield to protect the header file from being included more than once. */
#define ACEUNITANNOTATIONS_H 1

/** AceUnit Annotations header file.
 * You do not need to include this header file in a fixture.
 * The generated header file for your fixture will automatically include it.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file AceUnitAnnotations.h
 */

/** The super type of annotations.
 * Annotations are either ignored by the compiler or you can declare them to create static methods.
 * To use the latter, define ACEUNIT_STATIC_ANNOTATIONS.
 */
#ifdef ACEUNIT_STATIC_ANNOTATIONS
#define ACEUNIT_ANNOTATION static
#else
#define ACEUNIT_ANNOTATION
#endif

/** A direct annotation is an annotation which turns an arbitrary method into a test fixture method.
 * A method can have only zero or one direct annotations, not more.
 * That means direct annotations cannot be combined.
 */
#define ACEUNIT_DIRECT_ANNOTATION ACEUNIT_ANNOTATION

/** A meta annotation is an annotation which cannot be used standalone but only provides additional information for another annotation.
 * A method can have multiple meta annotations, but only if it already was annotated with a direct annotation.
 */
#define ACEUNIT_META_ANNOTATION ACEUNIT_ANNOTATION

/** Test annotation, use for test cases. */
#define A_Test             ACEUNIT_DIRECT_ANNOTATION

/** Loop annotation, use for looping test cases.
 *
 * Define <code>ACEUNIT_LOOP</code> to enable this feature.
 * If this feature is enabled, a test case is looped <var>times</var> times by the runner.
 * The loop will only loop the test itself.
 * It will not loop its <code>A_Before</code> and <code>A_After</code> methods.
 *
 * @param times Number of times to loop.
 */
#define A_Loop(times)      ACEUNIT_META_ANNOTATION

/** Before annotation, use for methods that should be invoked before each test case in a fixture. */
#define A_Before           ACEUNIT_DIRECT_ANNOTATION

/** After annotation, use for methods that should be invoked after each test case in a fixture. */
#define A_After            ACEUNIT_DIRECT_ANNOTATION

/** BeforeClass annotation, use for methods that should be invoked once for the fixture before all of its test cases. */
#define A_BeforeClass      ACEUNIT_DIRECT_ANNOTATION

/** AfterClass annotation, use for methods that should be invoked once for the fixture after all of its test cases. */
#define A_AfterClass       ACEUNIT_DIRECT_ANNOTATION

/** Ignore annotation, use for test cases to ignore.
 * This annotation is only allowed for methods annotated as #A_Test.
 */
#define A_Ignore           ACEUNIT_META_ANNOTATION

/** Puts a test in a specific group.
 * This annotation is only allowed for methods annotated as #A_Test.
 *
 * A test group allows tests to be grouped.
 * When the runner runs, it will pick only those tests belonging to the group given to the runner.
 *
 * For C99 it is possible to put a test in an arbitrary number of groups.
 * For C89 a test can be put in only one group.
 *
 * The default group of a test is group 0 (zero).
 */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && defined(ACEUNIT_C99)
#define A_Group(...)       ACEUNIT_META_ANNOTATION
#else
#define A_Group(group)
#endif

/** Puts a fixture in a specific group.
 * This annotation is only allowed once per fixture source.
 * Though this annotation might appear anywhere in the source code, it is recommended to place after include directives but before "normal" code.
 *
 * Putting a fixture in a specific group overrides the default group for all tests in that fixture.
 */
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && defined(ACEUNIT_C99)
#define A_FixtureGroup(...)
#else
#define A_FixtureGroup(group)
#endif

/** Adds parameters to a test method.
 * Currently, this annotation is only allowed for test cases.
 */
#define A_WithArray(parameters)

#endif /* ACEUNITANNOTATIONS_H */
