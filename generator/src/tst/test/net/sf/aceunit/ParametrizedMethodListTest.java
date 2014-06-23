package test.net.sf.aceunit;

import net.sf.aceunit.MethodLists;
import net.sf.aceunit.annotations.ParametrizedMethodList;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class ParametrizedMethodListTest extends AbstractMethodListTest<ParametrizedMethodList> {
    /** Tests that a method is detected for A_Loop. */
    @Test
    public void testLoopMethod() {
        methodList = MethodLists.createLoopMethodList();
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
