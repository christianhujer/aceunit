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

import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * A MethodList finds and contains all methods of a certain annotation type.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public class MethodList implements Iterable<String> {

    /**
     * The names of the methods found to be annotated.
     */
    @NotNull
    protected final List<String> methodNames = new ArrayList<>();
    /**
     * The annotation to find.
     */
    @NotNull
    private final String annotation;
    /**
     * The regular expression to use for finding annotated methods.
     */
    @NotNull
    private final Pattern pattern;
    /**
     * The variable name to use for symbols related to this MethodList.
     */
    @NotNull
    private final String symName;
    /**
     * The title to use for this method list, used in comments.
     */
    @NotNull
    private final String title;
    /**
     * The unmodifiable view of {@link #methodNames}.
     */
    @NotNull
    private final Collection<String> unmodifiableMethodNames = Collections.unmodifiableCollection(methodNames);

    /**
     * Create a MethodList.
     * The MethodList is initially empty.
     * Invoke {@link #findMethods(String)} to fill this MethodList.
     *
     * @param annotation Annotation to find.
     * @param symName    Name to use for symbols related to this MethodList.
     * @param title      Title to use e.g. in comments.
     */
    public MethodList(@NotNull final String annotation, @NotNull final String symName, @NotNull final String title) {
        this.annotation = annotation;
        pattern = Pattern.compile("\\b" + annotation + "\\b.*?(?:A_Loop\\(.*?\\))?.*?(\\b\\S+?\\b)\\s*?\\(", Pattern.MULTILINE | Pattern.DOTALL);
        this.symName = symName;
        this.title = title;
    }

    /**
     * Creates a MethodList for A_Test.
     *
     * @return MethodList for A_Test
     */
    public static MethodList createTestMethodList() {
        return new MethodList("A_Test", "testCases", "test cases");
    }

    /**
     * Creates a MethodList for A_Before.
     *
     * @return MethodList for A_Before
     */
    public static MethodList createBeforeMethodList() {
        return new MethodList("A_Before", "before", "before methods");
    }

    /**
     * Creates a MethodList for A_After.
     *
     * @return MethodList for A_After
     */
    public static MethodList createAfterMethodList() {
        return new MethodList("A_After", "after", "after methods");
    }

    /**
     * Creates a MethodList for A_BeforeClass.
     *
     * @return MethodList for A_BeforeClass
     */
    public static MethodList createBeforeClassMethodList() {
        return new MethodList("A_BeforeClass", "beforeClass", "beforeClass methods");
    }

    /**
     * Creates a MethodList for A_AfterClass.
     *
     * @return MethodList for A_AfterClass
     */
    public static MethodList createAfterClassMethodList() {
        return new MethodList("A_AfterClass", "afterClass", "afterClass methods");
    }

    /**
     * Creates a MethodList for A_Ignore.
     *
     * @return MethodList for A_Ignore
     */
    public static MethodList createIgnoreMethodList() {
        return new MethodList("A_Ignore", "ignore", "ignored methods");
    }

    /**
     * Creates a MethodList for A_Loop.
     *
     * @return MethodList for A_Loop
     */
    public static MethodList2 createLoopMethodList() {
        return new MethodList2("A_Loop", "loop", "looping methods", "1");
    }

    /**
     * Creates a MethodList for A_Group.
     *
     * @return MethodList for A_Group
     */
    public static MethodList2 createGroupMethodList() {
        return new MethodList2("A_Group", "group", "groups of methods.", "0");
    }

    /**
     * Returns the annotation this MethodList was created for.
     *
     * @return The annotation this MethodList was created for.
     */
    @NotNull
    public String getAnnotation() {
        return annotation;
    }

    /**
     * Finds all annotated methods in the specified C source.
     *
     * @param cSource C source to search.
     */
    public void findMethods(@NotNull final String cSource) {
        methodNames.clear();
        final Matcher matcher = pattern.matcher(cSource);
        while (matcher.find()) {
            methodNames.add(matcher.group(1));
        }
    }

    /**
     * Returns whether this MethodList contains a method with the specified name.
     *
     * @param methodName Method name to look for.
     * @return <code>true</code> if this MethodList contains a method with the specified name, otherwise <code>false</code>.
     */
    public boolean contains(@NotNull final String methodName) {
        return methodNames.contains(methodName);
    }

    @NotNull
    public Iterator<String> iterator() {
        return methodNames.iterator();
    }

    /**
     * Removes from this MethodList all methods that are in the specified list.
     *
     * @param list List with methods that should be removed from this MethodList.
     */
    public void removeAll(@NotNull final MethodList list) {
        methodNames.removeAll(list.methodNames);
    }

    /**
     * Returns a collection with all method names.
     *
     * @return A collection with all method names.
     */
    @NotNull
    public Collection<String> getMethodNames() {
        return unmodifiableMethodNames;
    }

    /**
     * Returns the number of methods in this method list.
     *
     * @return Number of methods in this method list.
     */
    public int size() {
        return methodNames.size();
    }

    /**
     * Returns the variable name to use for symbols related to this MethodList.
     *
     * @return the variable name to use for symbols related to this MethodList.
     */
    @NotNull
    public String getSymName() {
        return symName;
    }

    /**
     * Returns the title to use for this method list, used in comments.
     *
     * @return the title to use for this method list, used in comments.
     */
    @NotNull
    public String getTitle() {
        return title;
    }
}
