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

package net.sf.aceunit.annotations;

import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.HashMap;
import java.util.Map;
import java.util.regex.MatchResult;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static java.util.regex.Pattern.DOTALL;
import static java.util.regex.Pattern.MULTILINE;
import static java.util.regex.Pattern.compile;

/**
 * Special variant of MethodList which supports a parametrized annotation.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public class ParametrizedMethodList extends MethodList {

    /**
     * The regular expression to use for finding annotated methods.
     */
    @NotNull
    private final Pattern pattern;
    /**
     * The arguments.
     */
    private final Map<String, String> args = new HashMap<>();
    /**
     * The default value returned by {@link #getArg(String)} in case no method was annotated with this annotation.
     */
    private final String defaultValue;

    /**
     * Create a MethodList.
     * The MethodList is initially empty.
     * Invoke {@link #findMethods(String)} to fill this MethodList.
     *
     * @param annotation   Annotation to find.
     * @param symName      Name to use for symbols related to this MethodList.
     * @param title        Title to use e.g. in comments.
     * @param defaultValue Default value to return by {@link #getArg(String)} for not annotated methods.
     */
    public ParametrizedMethodList(@NotNull final String annotation, @NotNull final String symName, @NotNull final String title, @Nullable final String defaultValue) {
        super(annotation, symName, title);
        pattern = compile("\\b" + annotation + "\\b\\s*\\((.*?)\\).*?(\\b\\S+?\\b)\\s*?\\(", MULTILINE | DOTALL);
        this.defaultValue = defaultValue;
    }

    /**
     * Finds all annotated methods in the specified C source.
     *
     * @param cSource C source to search.
     */
    @Override
    public void findMethods(@NotNull final String cSource) {
        methodNames.clear();
        args.clear();
        final Matcher matcher = pattern.matcher(cSource);
        while (matcher.find())
            processFoundMethodMatch(matcher);
    }

    private void processFoundMethodMatch(final MatchResult matchResult) {
        final String methodName = matchResult.group(2);
        final String arg = matchResult.group(1);
        addMethodEntry(methodName, arg);
    }

    private void addMethodEntry(final String methodName, final String arg) {
        methodNames.add(methodName);
        args.put(methodName, normalizeArg(arg));
    }

    private static String normalizeArg(String arg) {
        if (arg == null)
            arg = "";
        arg = arg.trim();
        if (arg.isEmpty())
            arg = "1";
        return arg;
    }

    /**
     * Returns the loop annotation argument of the specified method.
     *
     * @param methodName Method for which to get the loop argument.
     * @return Loop argument of the specified method.
     */
    @Nullable
    public String getArg(@NotNull final String methodName) {
        return args.containsKey(methodName) ? args.get(methodName) : defaultValue;
    }

}
