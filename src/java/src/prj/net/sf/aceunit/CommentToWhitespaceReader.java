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
import org.jetbrains.annotations.Nullable;

import java.io.FilterReader;
import java.io.IOException;
import java.io.Reader;

/**
 * A NoCommentReader is a reader which replaces comments (C++, C99, Java) with whitespace.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 */
public class CommentToWhitespaceReader extends FilterReader {

    /**
     * The Sync Lock.
     */
    @NotNull
    private final Object syncLock = new Object();
    /**
     * The internal parser state, we begin with State.NORMAL.
     */
    @NotNull
    private State state = State.NORMAL;
    /**
     * The cached character is used to return a char that can only be returned when its following char was known.
     * If this is <code>null</code>, there is no cached character.
     */
    @Nullable
    private Integer cachedChar;

    /**
     * Creates a new NoCommentReader.
     *
     * @param in a Reader protected providing the underlying stream.
     * @throws NullPointerException if <code>in</code> is <code>null</code>
     */
    public CommentToWhitespaceReader(@NotNull final Reader in) {
        super(in);
    }

    /**
     * {@inheritDoc}
     */
    public int read() throws IOException {
        synchronized (syncLock) {
            final Integer cachedChar = this.cachedChar;
            if (cachedChar != null) {
                try {
                    return cachedChar;
                } finally {
                    if (cachedChar != -1) {
                        this.cachedChar = null;
                    }
                }
            }
            int rc;
            //noinspection StatementWithEmptyBody
            while ((rc = readImpl()) == -2) ;
            return rc;
        }
    }

    /**
     * Implementation of {@link #read()}.
     *
     * @return read character.
     * @throws IOException In case of I/O problems.
     * @retval -1 in case of end of file.
     * @retval -2 in case this function needs to be invoked again.
     */
    private int readImpl() throws IOException {
        final int c = super.read();
        int rc;
        switch (state) {
        case NORMAL:
            if (c == '/') {
                state = State.SLASH;
                rc = -2;
            } else if (c == '\\') {
                state = State.ESCAPE;
                rc = c;
            } else if (c == '"') {
                state = State.STRING;
                rc = c;
            } else if (c == '\'') {
                state = State.CHAR;
                rc = c;
            } else {
                state = State.NORMAL;
                rc = c;
            }
            break;
        case SLASH:
            if (c == '/') {
                state = State.EOL_COMMENT;
                cachedChar = (int) ' ';
                rc = ' ';
            } else if (c == '*') {
                state = State.ML_COMMENT;
                cachedChar = (int) ' ';
                rc = ' ';
            } else {
                state = State.NORMAL;
                cachedChar = c;
                rc = '/';
            }
            break;
        case EOL_COMMENT:
            if (c == '\n') {
                state = State.NORMAL;
                rc = c;
            } else if (c == '\r') {
                state = State.NORMAL;
                rc = c;
            } else if (c == '\\') {
                state = State.ESCAPE_IN_EOL_COMMENT;
                rc = ' ';
            } else {
                state = State.EOL_COMMENT;
                rc = c == -1 ? c : ' ';
            }
            break;
        case ML_COMMENT:
            if (c == '\n') {
                state = State.ML_COMMENT;
                rc = c;
            } else if (c == '\r') {
                state = State.ML_COMMENT;
                rc = c;
            } else if (c == '*') {
                state = State.MAYBE_END_OF_ML_COMMENT;
                rc = ' ';
            } else {
                state = State.ML_COMMENT;
                rc = c == -1 ? c : ' ';
            }
            break;
        case MAYBE_END_OF_ML_COMMENT:
            if (c == '\n') {
                state = State.ML_COMMENT;
                rc = c;
            } else if (c == '\r') {
                state = State.ML_COMMENT;
                rc = c;
            } else if (c == '*') {
                state = State.MAYBE_END_OF_ML_COMMENT;
                rc = ' ';
            } else if (c == '/') {
                state = State.NORMAL;
                rc = ' ';
            } else {
                state = State.ML_COMMENT;
                rc = ' ';
            }
            break;
        case ESCAPE:
            state = State.NORMAL;
            rc = c;
            break;
        case CHAR:
            if (c == '\'') {
                state = State.NORMAL;
                rc = c;
            } else if (c == '\\') {
                state = State.ESCAPE_IN_CHAR;
                rc = c;
            } else {
                state = State.CHAR;
                rc = c;
            }
            break;
        case ESCAPE_IN_CHAR:
            state = State.CHAR;
            rc = c;
            break;
        case STRING:
            if (c == '"') {
                state = State.NORMAL;
                rc = c;
            } else if (c == '\\') {
                state = State.ESCAPE_IN_STRING;
                rc = c;
            } else {
                state = State.STRING;
                rc = c;
            }
            break;
        case ESCAPE_IN_STRING:
            state = State.STRING;
            rc = c;
            break;
        case ESCAPE_IN_EOL_COMMENT:
            if (c == '\n') {
                state = State.EOL_COMMENT;
                rc = c;
            } else if (c == '\r') {
                rc = c;
            } else {
                state = State.EOL_COMMENT;
                rc = ' ';
            }
            break;
        default:
            throw new AssertionError("Missing case in above switch.");
        }
        return rc;
    }

    /**
     * {@inheritDoc}
     */
    public int read(@NotNull final char[] charBuffer, final int off, final int len) throws IOException {
        int i;
        for (i = 0; i < len; i++) {
            int c = read();
            if (c == -1) {
                if (i == 0) {
                    return -1;
                } else {
                    break;
                }
            }
            charBuffer[off + i] = (char) c;
        }
        return i;
    }

    /**
     * The internal states of the parser.
     */
    private enum State {

        /**
         * Nothing special, normal source.
         */
        NORMAL,

        /**
         * A slash was found, we might have a comment.
         */
        SLASH,

        /**
         * A second slash was found, we are in an EOL comment now.
         */
        EOL_COMMENT,

        /**
         * An escape was found in an EOL comment.
         */
        ESCAPE_IN_EOL_COMMENT,

        /**
         * An asterisk after a slash was found, we are in a multiline comment now.
         */
        ML_COMMENT,

        /**
         * An asterisk was found inside a multiline comment, we might have an end of the multiline comment.
         */
        MAYBE_END_OF_ML_COMMENT,

        /**
         * A backslash was found, we are in escape mode.
         */
        ESCAPE,

        /**
         * An apostrophe was found, we are inside a char literal.
         */
        CHAR,

        /**
         * A backslash was found inside a char literal, the next char will NOT end it even if it is an apostrophe.
         */
        ESCAPE_IN_CHAR,

        /**
         * A double quote was found, we are inside a string literal.
         */
        STRING,

        /**
         * A backslash was found inside a string literal, the next char will NOT end it even if it is a double quote.
         */
        ESCAPE_IN_STRING
    }

}
