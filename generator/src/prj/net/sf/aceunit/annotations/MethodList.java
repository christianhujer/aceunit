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

package net.sf.aceunit.annotations;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static java.util.regex.Pattern.DOTALL;
import static java.util.regex.Pattern.MULTILINE;
import static java.util.regex.Pattern.compile;

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
        pattern = compile("\\b" + annotation + "\\b.*?(?:A_Loop\\(.*?\\))?.*?(\\b\\S+?\\b)\\s*?\\(", MULTILINE | DOTALL);
        this.symName = symName;
        this.title = title;
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
        while (matcher.find())
            methodNames.add(matcher.group(1));
    }

    /**
     * Returns whether this MethodList contains a method with the specified name.
     *
     * @param methodName Method name to look for.
     * @return {@code true} if this MethodList contains a method with the specified name, otherwise {@code false}.
     */
    public boolean contains(@NotNull final String methodName) {
        return methodNames.contains(methodName);
    }

    @Override
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
