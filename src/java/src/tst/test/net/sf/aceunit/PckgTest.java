/* Copyright (c) 2008 - 2011, Christian Hujer
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

package test.net.sf.aceunit;

import net.sf.aceunit.Pckg;
import net.sf.aceunit.Suite;
import net.sf.aceunit.Fixture;
import org.junit.Test;
import org.junit.Assert;
import org.jetbrains.annotations.NotNull;

/** Unit Test for {@link Pckg}.
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public class PckgTest extends SuiteTest {

    /** {@inheritDoc} */
    public Suite createSuite(@NotNull final String name) {
        return new Pckg(name);
    }

    /** Tests that {@link Pckg#addSuite(Suite)} works. */
    @Test
    public void testAdd() {
        final Pckg oUT = new Pckg("dummy");
        Assert.assertFalse("After creation, a package is empty.", oUT.containsTests());
        final Pckg pckg = new Pckg("dummy");
        oUT.addSuite(pckg);
        Assert.assertFalse("After adding an empty package, a package is still empty.", oUT.containsTests());
        final Fixture emptyFixture = new Fixture(null, "");
        pckg.addSuite(emptyFixture);
        Assert.assertFalse("After adding a fixture with no test cases, a package is still empty.", oUT.containsTests());
        final Fixture fixture = new Fixture(null, "A_Test void aTest() {\n}\n");
        pckg.addSuite(fixture);
        Assert.assertTrue("After adding a fixture with test cases, a package is no longer empty.", oUT.containsTests());
    }

} // class SuiteTest
