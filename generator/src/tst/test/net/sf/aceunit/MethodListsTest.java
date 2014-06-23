package test.net.sf.aceunit;

import net.sf.aceunit.MethodLists;
import net.sf.aceunit.annotations.MethodList;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static test.net.sf.aceunit.annotations.Assert.assertContainsOnly;

public class MethodListsTest {
    /** Tests that removing a method list from another works. */
    @Test
    public void testRemoveAll() {
        final MethodList tests = MethodLists.createTestMethodList();
        final MethodList ignore = MethodLists.createIgnoreMethodList();
        final String cSource = "void dummy1() {} A_Test void test1() {} void dummy2() {} A_Ignore A_Test void test2() {} void dummy3() {} A_Test A_Ignore void test3() {} void dummy4() {} A_Ignore void ignore1() {}";
        tests.findMethods(cSource);
        ignore.findMethods(cSource);

        assertContainsOnly(tests, "test1", "test2", "test3");
        assertContainsOnly(ignore, "test2", "test3", "ignore1");

        tests.removeAll(ignore);

        assertContainsOnly(tests, "test1");
        assertContainsOnly(ignore, "test2", "test3", "ignore1"); // ignore MUST NOT have been modified by removeAll()
    }

    /** Tests that the annotation is properly returned. */
    @Test
    public void testGetAnnotation() {
        final MethodList methodList1 = MethodLists.createTestMethodList();
        final MethodList methodList2 = MethodLists.createBeforeMethodList();
        assertEquals("A_Test", methodList1.getAnnotation());
        assertEquals("A_Before", methodList2.getAnnotation());
    }
}
