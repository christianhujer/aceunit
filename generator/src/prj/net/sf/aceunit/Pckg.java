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

package net.sf.aceunit;

import org.jetbrains.annotations.NotNull;

import java.util.Formatter;

/**
 * A Pckg is a Suite that contains other Suites.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public class Pckg extends Suite<Suite<? extends Test>> {

    /**
     * Creates a Pckg with the specified id.
     *
     * @param name Name of this Pckg.
     */
    public Pckg(@NotNull final String name) {
        super(name);
    }

    public boolean containsTests() {
        boolean containsTests = false;
        for (final Suite<? extends Test> suite : getTests()) {
            containsTests = containsTests || suite.containsTests();
        }
        return containsTests;
    }

    /**
     * Adds a Suite to this Pckg.
     *
     * @param suite Suite to add
     */
    public void addSuite(@NotNull final Suite<? extends Test> suite) {
        add(suite);
    }

    @NotNull
    public String getCode(@NotNull final String baseName) {
        // TODO Can velocity or something similar make this nicer?
        final Formatter out = new Formatter();
        out.format("/** AceUnit test header file for package %s.%n", baseName);
        out.format(" *%n");
        out.format(" * @warning This is a generated file. Do not edit. Your changes will be lost.%n");
        out.format(" * @file%n");
        out.format(" */%n");
        out.format("%n");
        out.format("#include \"AceUnit.h\"%n");
        out.format("%n");
        out.format("#ifdef ACEUNIT_SUITES%n");
        out.format("%n");
        for (final Suite<? extends Test> suite : getTests()) {
            out.format("extern const TestSuite_t %s;%n", suite.getGlobalVariableName());
        }
        out.format("%n");
        out.format("const TestSuite_t *const suitesOf%d[] = {%n", getId());
        for (final Suite<? extends Test> suite : getTests()) {
            out.format("    &%s,%n", suite.getGlobalVariableName());
        }
        out.format("    NULL%n");
        out.format("};%n");
        out.format("%n");
        out.format("#if defined __cplusplus%n");
        out.format("extern%n");
        out.format("#endif%n");
        out.format("const TestSuite_t suite%d = {%n", getId());
        out.format("    %d,%n", getId());
        out.format("#ifndef ACEUNIT_EMBEDDED%n");
        out.format("    \"%s\",%n", baseName);
        out.format("#endif%n");
        out.format("    suitesOf%d%n", getId());
        out.format("};%n");
        out.format("%n");
        out.format("#endif%n");
        return out.toString();
    }

}
