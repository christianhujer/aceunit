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

package net.sf.aceunit;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Formatter;
import java.util.List;

/**
 * The Fixture represents a single test fixture along with all its methods.
 * It is intentional that the Ids of the test methods are not globally unique.
 * Globally unique test method ids would lead to changes in fixtures if the number of test cases in previously scanned fixtures changes.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public class Fixture extends Suite<TestCase> {

    /**
     * The list of {@code @Test} methods.
     */
    private final MethodList testMethods = MethodList.createTestMethodList();
    /**
     * The list of {@code @Before} methods.
     */
    private final MethodList beforeMethods = MethodList.createBeforeMethodList();
    /**
     * The list of {@code @After} methods.
     */
    private final MethodList afterMethods = MethodList.createAfterMethodList();
    /**
     * The list of {@code @BeforeClass} methods.
     */
    private final MethodList beforeClassMethods = MethodList.createBeforeClassMethodList();
    /**
     * The list of {@code @AfterClass} methods.
     */
    private final MethodList afterClassMethods = MethodList.createAfterClassMethodList();
    /**
     * The list of {@code @Ignore} methods.
     */
    private final MethodList ignoreMethods = MethodList.createIgnoreMethodList();
    /**
     * The list of {@code @Loop} methods.
     */
    private final MethodList2 loopMethods = MethodList.createLoopMethodList();
    /**
     * The list of {@code @Group} methods.
     */
    private final MethodList2 groupMethods = MethodList.createGroupMethodList();
    /**
     * All method lists for easy iteration.
     */
    private final List<MethodList> methodLists = Arrays.asList(testMethods, beforeMethods, afterMethods, beforeClassMethods, afterClassMethods, ignoreMethods, loopMethods, groupMethods);
    /**
     * All method lists for used methods for easy iteration.
     */
    private final List<MethodList> usedMethodLists = Arrays.asList(testMethods, beforeMethods, afterMethods, beforeClassMethods, afterClassMethods);

    /**
     * Creates a Fixture with the specified id.
     *
     * @param file File to create fixture for.
     * @throws IOException In case of I/O problems.
     */
    public Fixture(@NotNull final File file) throws IOException {
        super(file.getName().replaceAll("\\.c(pp)?$", ""));
        findMethods(SourceFiles.readSourceWithoutComments(file));
    }

    /**
     * Creates a Fixture with the specified id.
     *
     * @param file   File to create fixture for.
     * @param source The source of this Fixture.
     */
    public Fixture(@Nullable final File file, @Nullable final String source) {
        super(file != null ? file.getName().replaceAll("\\.c$", "") : "dummy");
        if (source != null) {
            findMethods(source);
        }
    }

    private static String getHeader(final String baseName) {
        final Formatter out = new Formatter();
        out.format("/** AceUnit test header file for fixture %s.%n", baseName);
        out.format(" *%n");
        out.format(" * You may wonder why this is a header file and yet generates program elements.%n");
        out.format(" * This allows you to declare test methods as static.%n");
        out.format(" *%n");
        out.format(" * @warning This is a generated file. Do not edit. Your changes will be lost.%n");
        out.format(" * @file%n");
        out.format(" */%n");
        out.format("%n");
        return out.toString();
    }

    /**
     * Finds all methods of all method lists in the specified source.
     *
     * @param cSource C source to search.
     */
    private void findMethods(@NotNull final String cSource) {
        for (final MethodList methodList : methodLists) {
            methodList.findMethods(cSource);
        }
        testMethods.removeAll(ignoreMethods);
    }

    public boolean containsTests() {
        return testMethods.size() > 0;
    }

    @NotNull
    public String getCode(@NotNull final String baseName) {
        final Formatter out = new Formatter();
        out.format("%s", getHeader(baseName));

        final String uppercaseFixture = baseName.toUpperCase();
        out.format("#ifndef _%s_H%n", uppercaseFixture);
        out.format("/** Include shield to protect this header file from being included more than once. */%n");
        out.format("#define _%s_H%n", uppercaseFixture);
        out.format("%n");

        out.format("/** The id of this fixture. */%n");
        out.format("#define A_FIXTURE_ID %d%n", getId());
        out.format("%n");

        out.format("#include \"AceUnit.h\"%n");
        out.format("%n");

        out.format("/* The prototypes are here to be able to include this header file at the beginning of the test file instead of at the end. */%n");
        for (final MethodList methods1 : usedMethodLists) {
            for (final String method : methods1) {
                if (!method.contains("::")) {
                    out.format("%s void %s(void);%n", methods1.getAnnotation(), method);
                }
            }
        }
        out.format("%n");

        out.format("/** The test case ids of this fixture. */%n");
        out.format("static const TestCaseId_t testIds[] = {%n");
        final String formatString = String.format("    %%%dd, /* %%s */%%n", (int) (Math.log10(testMethods.size()) + 1));
        for (final TestCase testCase : getTests()) {
            out.format(formatString, testCase.getId(), testCase.getName());
        }
        out.format("};%n");
        out.format("%n");

        out.format("#ifndef ACEUNIT_EMBEDDED%n");
        out.format("/** The test names of this fixture. */%n");
        out.format("static const char *const testNames[] = {%n");
        for (final String method : testMethods) {
            out.format("    \"%s\",%n", method);
        }
        out.format("};%n");
        out.format("#endif%n");
        out.format("%n");

        out.format("#ifdef ACEUNIT_LOOP%n");
        out.format("/** The loops of this fixture. */%n");
        out.format("static const aceunit_loop_t loops[] = {%n");
        for (final String method : testMethods) {
            out.format("    %s,%n", loopMethods.getArg(method));
        }
        out.format("};%n");
        out.format("#endif%n");
        out.format("%n");
        out.format("#ifdef ACEUNIT_GROUP%n");
        out.format("/** The groups of this fixture. */%n");
        out.format("static const AceGroupId_t groups[] = {%n");
        for (final String method : testMethods) {
            out.format("    %s,%n", groupMethods.getArg(method));
        }
        out.format("};%n");
        out.format("#endif%n");
        out.format("%n");

        for (final MethodList methods : usedMethodLists) {
            out.format("/** The %s of this fixture. */%n", methods.getTitle());
            out.format("static const testMethod_t %s[] = {%n", methods.getSymName());
            for (final String method : methods) {
                out.format("    %s,%n", method);
            }
            out.format("    NULL%n");
            out.format("};%n");
            out.format("%n");
        }

        out.format("/** This fixture. */%n");
        out.format("#if defined __cplusplus%n");
        out.format("extern%n");
        out.format("#endif%n");
        out.format("const TestFixture_t %sFixture = {%n", getName());
        out.format("    %d,%n", getId());
        out.format("#ifndef ACEUNIT_EMBEDDED%n");
        out.format("    \"%s\",%n", baseName);
        out.format("#endif%n");
        out.format("#ifdef ACEUNIT_SUITES%n");
        out.format("    NULL,%n");
        out.format("#endif%n");
        out.format("    testIds,%n");
        out.format("#ifndef ACEUNIT_EMBEDDED%n");
        out.format("    testNames,%n");
        out.format("#endif%n");
        out.format("#ifdef ACEUNIT_LOOP%n");
        out.format("    loops,%n");
        out.format("#endif%n");
        out.format("#ifdef ACEUNIT_GROUP%n");
        out.format("    groups,%n");
        out.format("#endif%n");
        out.format("    testCases,%n");
        out.format("    before,%n");
        out.format("    after,%n");
        out.format("    beforeClass,%n");
        out.format("    afterClass%n");
        out.format("};%n");
        out.format("%n");

        out.format("#endif /* _%s_H */%n", uppercaseFixture);
        return out.toString();
    }

    @Override
    public String getGlobalVariableName() {
        return getName() + "Fixture";
    }

    /**
     * Creates a TestCase for each contained test method.
     */
    public void createTestCases() {
        for (final String method : testMethods) {
            add(new TestCase(method));
        }
    }

}
