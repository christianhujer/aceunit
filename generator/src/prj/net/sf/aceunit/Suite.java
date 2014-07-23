/* Copyright (c) 2007 - 2011, Christian Hujer
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

package net.sf.aceunit;

import net.sf.aceunit.util.IdGenerator;
import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * A Suite is a collection of Test Cases.
 * A Suite can either be a Fixture that really contains Test Cases,
 * or a Pckg which is a Suite that contains other Suites.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public abstract class Suite<T extends Test> extends Test implements Iterable<T> {

    /**
     * The Tests contained in this Suite.
     */
    private final List<T> tests = new ArrayList<>();

    /**
     * Creates a Suite.
     *
     * @param name Name of this Suite.
     */
    protected Suite(@NotNull final String name) {
        super(name);
    }

    /**
     * Returns the global variable name of this Suite.
     *
     * @return The global variable name of this Suite.
     */
    public String getGlobalVariableName() {
        return "suite" + getId();
    }

    /**
     * Returns whether this suite contains tests.
     *
     * @return {@code true} if this fixture contains test cases, otherwise {@code false}.
     */
    public abstract boolean containsTests();

    @Override
    public void setId(@NotNull final IdGenerator generator) throws IllegalStateException {
        super.setId(generator);
        // XXX:2009-08-16:christianhujer:For packages the id is set other than for fixtures.
        //     Of course it would be nicer to have it clean, and that's the plan.
        //     See the XXX comments in GenTest.java for more information.
        //     Until then, the ugly instanceof is kept - the smell shouldn't be covered by a OO perfume.
        if (this instanceof Fixture) {
            for (final T test : tests) {
                test.setId(generator);
            }
        }
    }

    /**
     * Returns a String with the C-Source code for this Suite.
     *
     * @param baseName Base name of this Suite.
     * @return String with the C-Source for this Suite.
     */
    @NotNull
    public abstract String getCode(@NotNull final String baseName);

    /**
     * Returns a list of contained tests.
     *
     * @return A list of contained tests.
     */
    public List<T> getTests() {
        return Collections.unmodifiableList(tests);
    }

    /**
     * Adds a Test to this Suite.
     *
     * @param test Test to add.
     */
    public void add(@NotNull final T test) {
        tests.add(test);
    }

    @Override
    public Iterator<T> iterator() {
        return tests.iterator();
    }
}
