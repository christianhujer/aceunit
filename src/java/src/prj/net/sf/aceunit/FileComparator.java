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

import java.io.File;
import java.text.Collator;
import java.util.Comparator;
import java.util.Locale;

/**
 * Comparator for Files.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public class FileComparator implements Comparator<File> {

    // Optimization Idea:
    // For multiple or large sort operations, many comparisons are done.
    // Thus many conversions from File to String would happen.
    // A WeakHashMap<File, String> could cache the File.toString() results.
    // If performance is an issue, this also could be a WeakHashMap<File, CollationKey>.

    /**
     * The Collator of this FileComparator.
     */
    private final Collator collator;

    /**
     * Creates a FileComparator w/o locale.
     * The natural ordering of files is used.
     */
    public FileComparator() {
        this((Collator) null);
    }

    /**
     * Creates a FileComparator.
     *
     * @param locale Locale for comparing file(name)s.
     */
    public FileComparator(final Locale locale) {
        this(Collator.getInstance(locale));
    }

    /**
     * Creates a FileComparator.
     *
     * @param collator Collator for comparing file(name)s.
     */
    public FileComparator(final Collator collator) {
        this.collator = collator;
    }

    public int compare(final File o1, final File o2) {
        if (collator == null) {
            return o1.compareTo(o2);
        } else {
            return collator.compare(o1.toString(), o2.toString());
        }
    }

}
