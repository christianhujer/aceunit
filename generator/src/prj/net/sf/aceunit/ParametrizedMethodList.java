/* Copyright (c) 2008 - 2011, Christian Hujer
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

import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
        pattern = Pattern.compile("\\b" + annotation + "\\b\\s*\\((.*?)\\).*?(\\b\\S+?\\b)\\s*?\\(", Pattern.MULTILINE | Pattern.DOTALL);
        this.defaultValue = defaultValue;
    }

    /**
     * Finds all annotated methods in the specified C source.
     *
     * @param cSource C source to search.
     */
    public void findMethods(@NotNull final String cSource) {
        methodNames.clear();
        args.clear();
        final Matcher matcher = pattern.matcher(cSource);
        while (matcher.find()) {
            final String methodName = matcher.group(2);
            methodNames.add(methodName);
            String arg = matcher.group(1);
            if (arg == null)
                arg = "";
            arg = arg.trim();
            if (arg.length() == 0)
                arg = "1";
            args.put(methodName, arg);
        }
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
