#include <aceunit.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


void AceUnit_fail() {
    exit(EXIT_FAILURE);
}

static void nop() {}

/*
 * TODO:2023-02-28:christian.hujer:3:Change the fork runner to fork like this:
 * fork()
 *   beforeAll()
 *   loop over test cases
 *     fork()
 *       beforeEach()
 *       fork()
 *         testCase
 *       join()
 *       afterEach()
 *     join()
 *   end loop
 *   afterAll()
 * join()
 */

bool runCatching(void(*code)()) {
    pid_t childPid = fork();
    if (childPid) {
        int status;
        pid_t w = waitpid(childPid, &status, 0);
        assert(w == childPid);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status) == EXIT_SUCCESS;
        } else if (WIFSIGNALED(status)) {
            /* TODO:2023-02-17:christian.hujer:3:Print information about the failed test case. */
            return false;
        }
        assert(false);
    }
    (code ? code : nop)();
    exit(EXIT_SUCCESS);
}
