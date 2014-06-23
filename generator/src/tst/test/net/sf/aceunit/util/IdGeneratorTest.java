package test.net.sf.aceunit.util;

import net.sf.aceunit.util.IdGenerator;
import org.junit.Assert;
import org.junit.Test;

import static java.util.Arrays.sort;

/** UnitTest for {@link IdGenerator}.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public class IdGeneratorTest {

    /** Tests that IdGenerator returns distinct ids. */
    @Test
    public void testDistinct() {
        final IdGenerator oUT = new IdGenerator();
        final int[] testArray = new int[1000];
        for (int i = 0; i < testArray.length; i++)
            testArray[i] = oUT.getNextId();
        sort(testArray);
        for (int i = 1; i < testArray.length; i++)
            Assert.assertNotSame("IdGenerator MUST return distinct ids.", testArray[i - 1], testArray[i]);
    }

}
