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
import org.junit.Before;
import org.junit.Test;

/** Unit Test for {@link MethodList}.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public class MethodListTest extends AbstractMethodListTest<MethodList> {

    /**
     * Creates a MethodList for A_Test.
     */
    @Before
    public void createTestMethodList() {
        methodList = new MethodList("A_Test", "testCases", "test cases");
    }

    /** Tests that a method list finds a single annotated methods. */
    @Test
    public void testFindSingleAnnotatedMethod() {
        final String cSource = "A_Test void test1() {}";
        methodList.findMethods(cSource);
        assertContainsOnly("test1");
    }

    /** Tests that a method list finds multiple annotated methods. */
    @Test
    public void testFindMultipleAnnotatedMethod() {
        final String cSource = "A_Test void test1() {} A_Test void test2() {} A_Test void test3() {}";
        methodList.findMethods(cSource);
        assertContainsOnly("test1", "test2", "test3");
    }

    /** Tests that a method list finds a single annotated methods even if surrounded by other methods. */
    @Test
    public void testFindSingleAnnotatedMethod2() {
        final String cSource = "void dummy1() {} A_Test void test1() {} void dummy2() {}";
        methodList.findMethods(cSource);
        assertContainsOnly("test1");
        assertNotContains("dummy1", "dummy2");
    }

    /** Tests that a method list finds multiple annotated methods even if surrounded by other methods. */
    @Test
    public void testFindMultipleAnnotatedMethod2() {
        final String cSource = "void dummy1() {} A_Test void test1() {} void dummy2() {} A_Test void test2() {} void dummy3() {} A_Test void test3() {} void dummy4() {}";
        methodList.findMethods(cSource);
        assertContainsOnly("test1", "test2", "test3");
        assertNotContains("dummy1", "dummy2", "dummy3", "dummy4");
    }

    /** Tests that the returned iterator works correctly. */
    @Test
    public void testIterator() {
        final String cSource = "void dummy1() {} A_Test void test1() {} void dummy2() {} A_Test void test2() {} void dummy3() {} A_Test void test3() {} void dummy4() {}";
        methodList.findMethods(cSource);
        assertContainsOnly("test1", "test2", "test3");
    }

    /** Tests that a method is also detected if it is missing its return type.
     * @see <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1887942&amp;group_id=207094&amp;atid=1000227">[ 1887942 ] Java Generator does not detect wrongly formatted test source</a>
     */
    @Test
    public void testMethodWithoutReturnType() {
        final String cSource = "A_Test test1() {}";
        methodList.findMethods(cSource);
        assertContainsOnly("test1");
    }

    /** Tests that a method is also detected if its prototype spans several lines.
     * @see <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1887942&amp;group_id=207094&amp;atid=1000227">[ 1887942 ] Java Generator does not detect wrongly formatted test source</a>
     */
    @Test
    public void testMethodWithMultilinePrototype() {
        final String cSource = "A_Test\nstatic\ninline\nvoid\ntest1\n(\n)\n\n{\n}";
        methodList.findMethods(cSource);
        assertContainsOnly("test1");
    }

}
