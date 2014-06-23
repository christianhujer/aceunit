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

import net.sf.aceunit.CommentToWhitespaceReader;
import org.jetbrains.annotations.NotNull;
import org.junit.Assert;
import org.junit.Test;

import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;

/**
 * Tests that NoCommentReader replaces comments with whitespace.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @see <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1864061&amp;group_id=207094&amp;atid=1000227">[ 1864061 ] Java Generator does not recognize comments -> linker problem</a>
 */
public class CommentToWhitespaceReaderTest {

    /**
     * Tests that for source code without comments, that source code is returned unmodified.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void simpleLF() throws IOException {
        final String orig = "void foo() {\n    bar();\n}\n";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that for source code without comments, that source code is returned unmodified.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void simpleCR() throws IOException {
        final String orig = "void foo() {\r    bar();\r}\r";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that for source code without comments, that source code is returned unmodified.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void simpleCRLF() throws IOException {
        final String orig = "void foo() {\r\n    bar();\r\n}\r\n";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that EOL comments are properly replaced by whitespace.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void eolCommentsLF() throws IOException {
        final String orig = "void foo() { // comment\n    bar(); // comment\n} // comment\n";
        final String exp = "void foo() {           \n    bar();           \n}           \n";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that EOL comments are properly replaced by whitespace.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void eolCommentsCR() throws IOException {
        final String orig = "void foo() { // comment\r    bar(); // comment\r} // comment\r";
        final String exp = "void foo() {           \r    bar();           \r}           \r";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that EOL comments are properly replaced by whitespace.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void eolCommentsCRLF() throws IOException {
        final String orig = "void foo() { // comment\r\n    bar(); // comment\r\n} // comment\r\n";
        final String exp = "void foo() {           \r\n    bar();           \r\n}           \r\n";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that multiline comments on a single line are properly replaced by whitespace.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void multilineCommentsLF() throws IOException {
        final String orig = "void foo() { /* comment */\n    bar(); /* comment */\n} /* comment */\n";
        final String exp = "void foo() {              \n    bar();              \n}              \n";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that multiline comments on a single line are properly replaced by whitespace.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void multilineCommentsCR() throws IOException {
        final String orig = "void foo() { /* comment */\r    bar(); /* comment */\r} /* comment */\r";
        final String exp = "void foo() {              \r    bar();              \r}              \r";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that multiline comments on a single line are properly replaced by whitespace.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void multilineCommentsCRLF() throws IOException {
        final String orig = "void foo() { /* comment */\r\n    bar(); /* comment */\r\n} /* comment */\r\n";
        final String exp = "void foo() {              \r\n    bar();              \r\n}              \r\n";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that a String that contains text like an EOL comment is retained as String.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void pseudoEolCommentInStringLF() throws IOException {
        final String orig = "void foo() {\n    printf(\"// pseudo comment\");\n}\n";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a String that contains text like an EOL comment is retained as String.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void pseudoEolCommentInStringCR() throws IOException {
        final String orig = "void foo() {\r    printf(\"// pseudo comment\");\r}\r";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a String that contains text like an EOL comment is retained as String.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void pseudoEolCommentInStringCRLF() throws IOException {
        final String orig = "void foo() {\r\n    printf(\"// pseudo comment\");\r\n}\r\n";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a String that contains text like a multiline comment is retained as String.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void pseudoMultilineCommentInStringLF() throws IOException {
        final String orig = "void foo() {\n    printf(\"/* pseudo comment */\");\n}\n";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a String that contains text like a multiline comment is retained as String.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void pseudoMultilineCommentInStringCR() throws IOException {
        final String orig = "void foo() {\r    printf(\"/* pseudo comment */\");\r}\r";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a String that contains text like a multiline comment is retained as String.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void pseudoMultilineCommentInStringCRLF() throws IOException {
        final String orig = "void foo() {\r\n    printf(\"/* pseudo comment */\");\r\n}\r\n";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a single slash at the end of a line is not removed.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void slashAtEndOfLineCR() throws IOException {
        final String orig = "someCode(); /\nfoo();\n";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a single slash at the end of a line is not removed.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void slashAtEndOfLineLF() throws IOException {
        final String orig = "someCode(); /\rfoo();\r";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a single slash at the end of a line is not removed.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void slashAtEndOfLineCRLF() throws IOException {
        final String orig = "someCode(); /\r\nfoo();\r\n";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a single slash at the end and start of line are not removed.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void slashAtEndAndStartOfLineLF() throws IOException {
        final String orig = "someCode(); /\n/ foo();\n";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a single slash at the end and start of line are not removed.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void slashAtEndAndStartOfLineCR() throws IOException {
        final String orig = "someCode(); /\r/ foo();\r";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a single slash at the end and start of line are not removed.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void slashAtEndAndStartOfLineCRLF() throws IOException {
        final String orig = "someCode(); /\r\n/ foo();\r\n";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a single slash at the end of a file is not removed.
     *
     * @throws IOException In case of I/O problems (unexpected).
     * @see <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1879533&amp;group_id=207094&amp;atid=1000227">[ 1879533 ] missing EOL at EOF makes Generator run out of heap space</a>
     */
    @Test
    public void slashAtEndOfFile() throws IOException {
        final String orig = "someCode(); /";
        assertReplacement(orig, orig);
    }

    /**
     * Tests that a multiline comment at the start of the text is replaced by whitespace.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void eolCommentAtStartLF() throws IOException {
        final String orig = "/* foo\n * bar\n *\n */\n\nextern void foo();\n";
        final String exp = "      \n      \n  \n   \n\nextern void foo();\n";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that a multiline comment at the start of the text is replaced by whitespace.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void eolCommentAtStartCR() throws IOException {
        final String orig = "/* foo\r * bar\r *\r */\r\rextern void foo();\r";
        final String exp = "      \r      \r  \r   \r\rextern void foo();\r";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that a multiline comment at the start of the text is replaced by whitespace.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void eolCommentAtStartCRLF() throws IOException {
        final String orig = "/* foo\r\n * bar\r\n *\r\n */\r\n\r\nextern void foo();\r\n";
        final String exp = "      \r\n      \r\n  \r\n   \r\n\r\nextern void foo();\r\n";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that consecutive single line comments at the start of the text are replaced by whitespace.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void multilineCommentAtStartLF() throws IOException {
        final String orig = "// foo\n// bar\n// bazz\nextern void foo();\n";
        final String exp = "      \n      \n       \nextern void foo();\n";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that consecutive single line comments at the start of the text are replaced by whitespace.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void multilineCommentAtStartCR() throws IOException {
        final String orig = "// foo\r// bar\r// bazz\rextern void foo();\r";
        final String exp = "      \r      \r       \rextern void foo();\r";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that consecutive single line comments at the start of the text are replaced by whitespace.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void multilineCommentAtStartCRLF() throws IOException {
        final String orig = "// foo\r\n// bar\r\n// bazz\r\nextern void foo();\r\n";
        final String exp = "      \r\n      \r\n       \r\nextern void foo();\r\n";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that an incomplete last line works.
     *
     * @throws IOException In case of I/O problems (unexpected).
     * @see <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1879533&amp;group_id=207094&amp;atid=1000227">[ 1879533 ] missing EOL at EOF makes Generator run out of heap space</a>
     */
    @Test
    public void incompleteLastLine() throws IOException {
        final String orig = "void foo() { }";
        final String exp = "void foo() { }";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that an incomplete last line with multiline comment works.
     *
     * @throws IOException In case of I/O problems (unexpected).
     * @see <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1879533&amp;group_id=207094&amp;atid=1000227">[ 1879533 ] missing EOL at EOF makes Generator run out of heap space</a>
     */
    @Test
    public void incompleteLastLineWithMultilineComment() throws IOException {
        final String orig = "/* foo */";
        final String exp = "         ";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that an incomplete last line with EOL comment works.
     *
     * @throws IOException In case of I/O problems (unexpected).
     * @see <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1879533&amp;group_id=207094&amp;atid=1000227">[ 1879533 ] missing EOL at EOF makes Generator run out of heap space</a>
     */
    @Test
    public void incompleteLastLineWithEOLComment() throws IOException {
        final String orig = "// foo";
        final String exp = "      ";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that an incomplete multiline comment works.
     *
     * @throws IOException In case of I/O problems (unexpected).
     * @see <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1879533&amp;group_id=207094&amp;atid=1000227">[ 1879533 ] missing EOL at EOF makes Generator run out of heap space</a>
     */
    @Test
    public void incompleteMultilineComment() throws IOException {
        final String orig = "/*  ";
        final String exp = "    ";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that an incomplete multiline comment works.
     *
     * @throws IOException In case of I/O problems (unexpected).
     * @see <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1879533&amp;group_id=207094&amp;atid=1000227">[ 1879533 ] missing EOL at EOF makes Generator run out of heap space</a>
     */
    @Test
    public void incompleteString() throws IOException {
        final String orig = "\"xxx";
        final String exp = "\"xxx";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that an incomplete multiline comment works.
     *
     * @throws IOException In case of I/O problems (unexpected).
     * @see <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1879533&amp;group_id=207094&amp;atid=1000227">[ 1879533 ] missing EOL at EOF makes Generator run out of heap space</a>
     */
    @Test
    public void incompleteChar() throws IOException {
        final String orig = "'x";
        final String exp = "'x";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that an incomplete multiline comment works.
     *
     * @throws IOException In case of I/O problems (unexpected).
     * @see <a href="https://sourceforge.net/tracker/index.php?func=detail&amp;aid=1879533&amp;group_id=207094&amp;atid=1000227">[ 1879533 ] missing EOL at EOF makes Generator run out of heap space</a>
     */
    @Test
    public void incompleteEscape() throws IOException {
        final String orig = "\\";
        final String exp = "\\";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that stars in multiline comments do not cause problems.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void starsInMultilineComment() throws IOException {
        final String orig = "foo/***/foo";
        final String exp = "foo     foo";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that a slash in the next line does not terminate a multiline comment.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void slashInNextLineDoesNotTerminateLF() throws IOException {
        final String orig = "foo/*\n/*/bar/**\n/*/";
        final String exp = "foo  \n   bar   \n   ";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that a slash in the next line does not terminate a multiline comment.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void slashInNextLineDoesNotTerminateCR() throws IOException {
        final String orig = "foo/*\r/*/bar/**\r/*/";
        final String exp = "foo  \r   bar   \r   ";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that a slash in the next line does not terminate a multiline comment.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void slashInNextLineDoesNotTerminateCRLF() throws IOException {
        final String orig = "foo/*\r\n/*/bar/**\r\n/*/";
        final String exp = "foo  \r\n   bar   \r\n   ";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that escapes in Strings work.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void escapeInString() throws IOException {
        final String orig = "foo\"\\\"\\/\"bar";
        final String exp = "foo\"\\\"\\/\"bar";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that escapes in Characters work.
     * This is not correct C but valid for a C preprocessor.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void escapeInCharacter() throws IOException {
        final String orig = "foo\'\\\'\\/\'bar";
        final String exp = "foo\'\\\'\\/\'bar";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that a backslash at the end of a end of line comment continues the comment.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void backslashAtEOLCommentContinuesLF() throws IOException {
        final String orig = "foo //comment\\\ncomment";
        final String exp = "foo           \n       ";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that a backslash at the end of a end of line comment continues the comment.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void backslashAtEOLCommentContinuesCR() throws IOException {
        final String orig = "foo //comment\\\rcomment";
        final String exp = "foo           \r       ";
        assertReplacement(orig, exp);
    }

    /**
     * Tests that a backslash at the end of a end of line comment continues the comment.
     *
     * @throws IOException In case of I/O problems (unexpected).
     */
    @Test
    public void backslashAtEOLCommentContinuesCRLF() throws IOException {
        final String orig = "foo //comment\\\r\ncomment";
        final String exp = "foo           \r\n       ";
        assertReplacement(orig, exp);
    }

    /**
     * Asserts that when reading the String <var>orig</var> through a {@link CommentToWhitespaceReader}, <var>exp</var> is returned.
     *
     * @param orig Original String, will be passed through a {@link CommentToWhitespaceReader}.
     * @param exp  Expected String, will be compared to the result of passing <var>orig</var> through a {@link CommentToWhitespaceReader}.
     * @throws IOException In case of I/O problems (unexpected).
     */
    public static void assertReplacement(@NotNull final String orig, @NotNull final String exp) throws IOException {
        assertReplacementSingle(orig, exp);
        assertReplacementBlock(orig, exp);
    }

    /**
     * Asserts that when reading the String <var>orig</var> through a {@link CommentToWhitespaceReader}, <var>exp</var> is returned.
     *
     * @param orig Original String, will be passed through a {@link CommentToWhitespaceReader}.
     * @param exp  Expected String, will be compared to the result of passing <var>orig</var> through a {@link CommentToWhitespaceReader}.
     * @throws IOException In case of I/O problems (unexpected).
     */
    public static void assertReplacementSingle(@NotNull final String orig, @NotNull final String exp) throws IOException {
        assertReplacement(orig, exp, CommentToWhitespaceReaderTest::readSingleChars);
    }

    /**
     * Asserts that when reading the String <var>orig</var> through a {@link CommentToWhitespaceReader}, <var>exp</var> is returned.
     *
     * @param orig Original String, will be passed through a {@link CommentToWhitespaceReader}.
     * @param exp  Expected String, will be compared to the result of passing <var>orig</var> through a {@link CommentToWhitespaceReader}.
     * @throws IOException In case of I/O problems (unexpected).
     */
    public static void assertReplacementBlock(@NotNull final String orig, @NotNull final String exp) throws IOException {
        assertReplacement(orig, exp, CommentToWhitespaceReaderTest::readBlockWiseChars);
    }

    private static void assertReplacement(final String orig, final String exp, final ReadChars readChars) throws IOException {
        Assert.assertEquals(exp, readChars.readChars(new CommentToWhitespaceReader(new StringReader(orig))));
    }

    private static String readSingleChars(final Reader reader) throws IOException {
        final StringBuilder sb = new StringBuilder();
        //noinspection StatementWithEmptyBody
        for (int c; (c = reader.read()) != -1; sb.append((char) c)) ;
        return sb.toString();
    }

    private static String readBlockWiseChars(final Reader reader) throws IOException {
        final StringBuilder sb = new StringBuilder();
        final char[] buf = new char[4096];
        //noinspection StatementWithEmptyBody
        for (int charsRead; (charsRead = reader.read(buf)) != -1; sb.append(buf, 0, charsRead)) ;
        return sb.toString();
    }

    private static interface ReadChars {
        String readChars(Reader reader) throws IOException;
    }

}
