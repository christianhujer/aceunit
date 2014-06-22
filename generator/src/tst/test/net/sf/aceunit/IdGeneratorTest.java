package test.net.sf.aceunit;

import net.sf.aceunit.IdGenerator;
import org.junit.Test;
import org.junit.Assert;

import java.util.Arrays;

/** UnitTest for {@link IdGenerator}.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public class IdGeneratorTest {

    /** Tests that IdGenerator returns distinct ids. */
    @Test
    public void testDistinct() {
        final IdGenerator oUT = new IdGenerator();
        final int[] testArray = new int[1000];
        for (int i = 0; i < testArray.length; i++) {
            testArray[i] = oUT.getNextId();
        }
        Arrays.sort(testArray);
        for (int i = 1; i < testArray.length; i++) {
            Assert.assertNotSame("IdGenerator MUST return distinct ids.", testArray[i - 1], testArray[i]);
        }
    }

} // class IdGeneratorTest
