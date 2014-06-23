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

import net.sf.aceunit.annotations.ParametrizedMethodList;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class ParametrizedMethodListTest extends AbstractMethodListTest<ParametrizedMethodList> {
    /** Tests that a method is detected for A_Loop. */
    @Test
    public void testLoopMethod() {
        methodList = new ParametrizedMethodList("A_Loop", "loop", "looping methods", "1");
        final String cSource = "A_Test\nA_Loop(20)\nvoid loopMe(void)\n{\n}\n";
        methodList.findMethods(cSource);
        assertContainsOnly("loopMe");
        assertEquals("20", methodList.getArg("loopMe"));
    }

    /** Tests that commas in an annotation with arguments work. */
    @Test
    public void testCommasInAnnotationArgs() {
        methodList = new ParametrizedMethodList("A_WithParams", "params", "Parameters", null);
        final String cSource = "A_Test A_WithParams(\"foo\", \"bar\", \"qux\") void callMeWithArgs(const char *arg)\n{\n}\n";
        methodList.findMethods(cSource);
        assertContainsOnly("callMeWithArgs");
        assertEquals("\"foo\", \"bar\", \"qux\"", methodList.getArg("callMeWithArgs"));
    }
}
