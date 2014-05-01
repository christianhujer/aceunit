/* Copyright (c) 2007 - 2014, Christian Hujer
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

/** Java-like exceptions for C.
 * This is part of AceUnit but can also be used without AceUnit.
 *
 * Example:
 * <pre>
 * \#define SomeException 1
 * int someMethod() throws(SomeException) {
 *     if (someCondition) {
 *         throw(SomeException);
 *     }
 * }
 *
 * int someCaller() {
 *     try {
 *         someMethod();
 *     } catch (SomeException) {
 *         // handle this exception
 *     } endtry;
 * }
 * </pre>
 *
 * Differences to Java
 * - Exceptions are only int values.
 * - endtry MUST not be omitted.
 * - Omitting the {} block at try or catch will eventually not be detected by the compiler but lead to extremely strange behaviour.
 * - throw has a slightly different syntax.
 * - throws has a slightly different syntax and currently no effect.
 * - there are no checked exceptions, i.e. exception handling cannot be enforced.
 *
 * Similarities with Java
 * - You can have more than one catch clause per try.
 * - You can have zero or more catch clauses per try. Yes, having zero catch clauses is allowed. But unlike Java this doesn't make sense in C.
 *
 * @author <a href="mailto:cher@riedquat.de">Christian Hujer</a>
 * @file ExceptionHandling.h
 */

#include <setjmp.h>
#include <string.h>

/** The exception buffer of the current thread.
 * If you work in a multi-threaded environment, make sure the scheduler allocates a jmp_buf for each thread and initializes currentExceptionBuffer for that thread with each conext switch.
 * If you don't, your system will get very upset about interrupted exceptions.
 *
 * Make sure that the scheduler starts each thread with an initialized jmp_buf (invoke setjmp() once!), otherwise your system will get very upset about uncaught exceptions.
 *
 * If you work in a single-threaded environment, still make sure that setjmp(*currentExceptionBuffer) is invoked at least once at the very beginning, otherwise your system will get very upset
 * about uncaught exceptions.
 */
extern jmp_buf *currentExceptionBuffer;

/** Start execution of code which might throw an exception that might be caught by the exception handlers that follow this try.
 * From #catch / #catchAll to #endtry, a local variable named <var>exception</var> will exist and contain the exception information (that is, #setjmp() return value).
 * @warning Never omit #endtry
 */
#define try \
    do { \
        int exception; \
        jmp_buf lbuf; \
        jmp_buf *prev = currentExceptionBuffer; \
        currentExceptionBuffer = &lbuf; \
        switch (exception = setjmp(lbuf)) { \
        case 0: do \

/** Define an exception handler.
 * @param X exception to catch, MUST be of type int.
 */
#define catch(X) \
            while (false); \
            break; \
        case (X): exception = 0; do \

/** Define a default exception handler. */
#define catchAll() \
            while (false); \
            break; \
        default: exception = 0; do \

/** End exception handling. */
#define endtry \
            while (false); \
        } \
        currentExceptionBuffer = prev; \
        if (exception) { \
            longjmp(*currentExceptionBuffer, exception); \
        } \
    } while(0)

/** Throw an exception.
 * @param X Exception to throw, MUST be of type int.
 */
#define throw(X) \
    do { \
        longjmp(*currentExceptionBuffer, (X)); \
    } while (false)

/** Rethrows the current exception.
 * This is a shorthand for #throw(exception).
 */
#define rethrow() \
    throw(exception)

/** Declare that a function throws an exception of this type.
 * This is currently unused but might be used in future by additional tools that could look for uncaught exceptions.
 * @param X Exception type to declare, MUST be of type int.
 */
#define throws(X)
