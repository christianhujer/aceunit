#include "ExceptionHandling.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

/*define VERBOSE_ASSERT*/

#ifdef VERBOSE_ASSERT
#define ASSERT(X) printf( #X "\n" ), assert(X)
#else
#define ASSERT(X) assert(X)
#endif

int main(void) {
    int count = 0;
    ASSERT(++count == 1); /* should be reached. */
    try {
        ASSERT(++count == 2); /* should be reached. */
        try {
            ASSERT(++count == 3); /* should be reached. */
            try {
                ASSERT(++count == 4); /* should be reached. */
                throw(1);
                ASSERT(false); /* should NOT be reached. */
            } catch (2) {
                ASSERT(false); /* should NOT be reached. */
            } endtry;
        } catch (1) {
            ASSERT(++count == 5); /* should be reached. */
        } endtry;
        ASSERT(++count == 6); /* should be reached. */
    } endtry;
    ASSERT(++count == 7); /* should be reached. */
    return 0;
}
