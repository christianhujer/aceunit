package test.net.sf.aceunit;

import net.sf.aceunit.annotations.MethodList;
import net.sf.aceunit.MethodLists;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class MethodListsTest {
    /** Tests that the annotation is properly returned. */
    @Test
    public void testGetAnnotation() {
        final MethodList methodList1 = MethodLists.createTestMethodList();
        final MethodList methodList2 = MethodLists.createBeforeMethodList();
        assertEquals("A_Test", methodList1.getAnnotation());
        assertEquals("A_Before", methodList2.getAnnotation());
    }
}
