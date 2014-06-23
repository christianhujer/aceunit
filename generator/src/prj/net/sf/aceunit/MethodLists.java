package net.sf.aceunit;

import net.sf.aceunit.annotations.MethodList;
import net.sf.aceunit.annotations.ParametrizedMethodList;

public class MethodLists {
    /**
     * Creates a MethodList for A_Test.
     *
     * @return MethodList for A_Test
     */
    public static MethodList createTestMethodList() {
        return new MethodList("A_Test", "testCases", "test cases");
    }

    /**
     * Creates a MethodList for A_Before.
     *
     * @return MethodList for A_Before
     */
    public static MethodList createBeforeMethodList() {
        return new MethodList("A_Before", "before", "before methods");
    }

    /**
     * Creates a MethodList for A_After.
     *
     * @return MethodList for A_After
     */
    public static MethodList createAfterMethodList() {
        return new MethodList("A_After", "after", "after methods");
    }

    /**
     * Creates a MethodList for A_BeforeClass.
     *
     * @return MethodList for A_BeforeClass
     */
    public static MethodList createBeforeClassMethodList() {
        return new MethodList("A_BeforeClass", "beforeClass", "beforeClass methods");
    }

    /**
     * Creates a MethodList for A_AfterClass.
     *
     * @return MethodList for A_AfterClass
     */
    public static MethodList createAfterClassMethodList() {
        return new MethodList("A_AfterClass", "afterClass", "afterClass methods");
    }

    /**
     * Creates a MethodList for A_Ignore.
     *
     * @return MethodList for A_Ignore
     */
    public static MethodList createIgnoreMethodList() {
        return new MethodList("A_Ignore", "ignore", "ignored methods");
    }

    /**
     * Creates a MethodList for A_Loop.
     *
     * @return MethodList for A_Loop
     */
    public static ParametrizedMethodList createLoopMethodList() {
        return new ParametrizedMethodList("A_Loop", "loop", "looping methods", "1");
    }

    /**
     * Creates a MethodList for A_Group.
     *
     * @return MethodList for A_Group
     */
    public static ParametrizedMethodList createGroupMethodList() {
        return new ParametrizedMethodList("A_Group", "group", "groups of methods.", "0");
    }
}
