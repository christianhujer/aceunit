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

import org.jetbrains.annotations.NotNull;

import java.io.*;

import static java.util.logging.Logger.getAnonymousLogger;

/**
 * Utility class with methods for reading source files.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public final class SourceFiles {

    /**
     * FileFilter to get directories.
     */
    public static final FileFilter DIR_FILTER = File::isDirectory;
    /**
     * FileFilter to get C and C++ source files.
     */
    public static final FileFilter C_AND_CPP_SOURCE_FILTER = pathname -> pathname.isFile() && endsWith(pathname.getName(), ".c", ".cpp");

    /**
     * Utility class - do not instance.
     */
    private SourceFiles() {
    }

    private static boolean endsWith(final String text, final String... suffixes) {
        for (final String suffix : suffixes)
            if (text.endsWith(suffix))
                return true;
        return false;
    }

    /**
     * Reads a source file.
     *
     * @param file File of the source to read.
     * @return String with the contents of the specified file.
     * @throws IOException in case of I/O problems.
     */
    public static String readSource(@NotNull final File file) throws IOException {
        final Reader in = new FileReader(file);
        final StringBuilder sb = new StringBuilder();
        final char[] buf = new char[4096];
        for (int charsRead; (charsRead = in.read(buf)) != -1; ) {
            sb.append(buf, 0, charsRead);
        }
        in.close();
        return sb.toString();
    }

    /**
     * Reads a source file without comments.
     *
     * @param file File of the source to read.
     * @return String with the contents of the specified file.
     * @throws IOException in case of I/O problems.
     */
    public static String readSourceWithoutComments(@NotNull final File file) throws IOException {
        final Reader in = new CommentToWhitespaceReader(new BufferedReader(new FileReader(file)));
        final StringBuilder sb = new StringBuilder();
        final char[] buf = new char[4096];
        for (int charsRead; (charsRead = in.read(buf)) != -1; ) {
            sb.append(buf, 0, charsRead);
        }
        in.close();
        return sb.toString();
    }

    /**
     * Writes a String to a file if the String differs from the file's content.
     *
     * @param file  File to write to.
     * @param text  String to write to the file.
     * @param force Set this to true if a write protection from the file should be removed.
     * @throws IOException In case of I/O problems.
     */
    public static void writeIfChanged(@NotNull final File file, @NotNull final CharSequence text, final boolean force) throws IOException {
        if (!file.exists() || !text.equals(readSource(file))) {
            if (force && !file.canWrite()) {
                getAnonymousLogger().info("Removing write protection from " + file);
                if (!file.setWritable(true)) {
                    getAnonymousLogger().warning("Couldn't remove write protection from " + file);
                }
            }
            try (final PrintWriter out = new PrintWriter(new FileWriter(file))) {
                out.append(text);
            }
        }
    }

}
