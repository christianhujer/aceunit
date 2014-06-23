package test.net.sf.aceunit;

import net.sf.aceunit.annotations.MethodList;
import org.jetbrains.annotations.NotNull;
import org.junit.Assert;

import static org.junit.Assert.assertEquals;

public class AbstractMethodListTest<T extends MethodList> {

    /** The MethodList to test. */
    protected T methodList;

    /** Asserts that the method list contains (at least) the specified method names.
     * @param methodNames Method names to check.
     */
    protected void assertContains(@NotNull final String... methodNames) {
        assertContains(methodList, methodNames);
    }

    /** Asserts that a method list contains only the specified method names.
     * @param methodNames Method names to check.
     */
    protected void assertContainsOnly(@NotNull final String... methodNames) {
        assertContainsOnly(methodList, methodNames);
    }

    /** Asserts that a method list does not contain the specified method names.
     * @param methodNames Method names to check.
     */
    protected void assertNotContains(@NotNull final String... methodNames) {
        assertNotContains(methodList, methodNames);
    }

    /** Asserts that a method list contains (at least) the specified method names.
     * @param methodList Method list to check.
     * @param methodNames Method names to check.
     */
    protected static void assertContains(@NotNull final MethodList methodList, @NotNull final String... methodNames) {
        for (final String methodName : methodNames)
            if (!methodList.contains(methodName))
                Assert.fail("Expected methodList " + methodList + " to contain " + methodName);
    }

    /** Asserts that a method list contains only the specified method names.
     * @param methodList Method list to check.
     * @param methodNames Method names to check.
     */
    protected static void assertContainsOnly(@NotNull final MethodList methodList, @NotNull final String... methodNames) {
        assertEquals(methodNames.length, methodList.size());
        for (final String methodName : methodNames)
            if (!methodList.contains(methodName))
                Assert.fail("Expected methodList " + methodList + " to contain " + methodName);
    }

    /** Asserts that a method list does not contain the specified method names.
     * @param methodList Method list to check.
     * @param methodNames Method names to check.
     */
    protected static void assertNotContains(@NotNull final MethodList methodList, @NotNull final String... methodNames) {
        for (final String methodName : methodNames)
            if (methodList.contains(methodName))
                Assert.fail("Expected methodList " + methodList + " to not contain " + methodName);
    }
}
