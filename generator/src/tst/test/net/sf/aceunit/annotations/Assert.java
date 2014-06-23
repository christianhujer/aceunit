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

package test.net.sf.aceunit.annotations;

import net.sf.aceunit.annotations.MethodList;
import org.jetbrains.annotations.NotNull;

import static org.junit.Assert.assertEquals;

public class Assert {
    /** Asserts that a method list contains (at least) the specified method names.
     * @param methodList Method list to check.
     * @param methodNames Method names to check.
     */
    public static void assertContains(@NotNull final MethodList methodList, @NotNull final String... methodNames) {
        for (final String methodName : methodNames)
            if (!methodList.contains(methodName))
                org.junit.Assert.fail("Expected methodList " + methodList + " to contain " + methodName);
    }

    /** Asserts that a method list contains only the specified method names.
     * @param methodList Method list to check.
     * @param methodNames Method names to check.
     */
    public static void assertContainsOnly(@NotNull final MethodList methodList, @NotNull final String... methodNames) {
        assertEquals(methodNames.length, methodList.size());
        for (final String methodName : methodNames)
            if (!methodList.contains(methodName))
                org.junit.Assert.fail("Expected methodList " + methodList + " to contain " + methodName);
    }

    /** Asserts that a method list does not contain the specified method names.
     * @param methodList Method list to check.
     * @param methodNames Method names to check.
     */
    public static void assertNotContains(@NotNull final MethodList methodList, @NotNull final String... methodNames) {
        for (final String methodName : methodNames)
            if (methodList.contains(methodName))
                org.junit.Assert.fail("Expected methodList " + methodList + " to not contain " + methodName);
    }
}
