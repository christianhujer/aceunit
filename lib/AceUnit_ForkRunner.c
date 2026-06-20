#include <aceunit.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


void AceUnit_fail(void) {
    exit(EXIT_FAILURE);
}

static void nop(void) {}

static bool fork_runCatching(void(*code)(void)) {
    (code ? code : nop)();
    return true;
}

void AceUnit_run(const AceUnit_Fixture_t **fixtures, AceUnit_Result_t *result) {
    const AceUnit_Fixture_t **fixture;
    assert(fixtures);
    assert(result);

    for (fixture = &fixtures[0]; *fixture != NULL; fixture++) {
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("Failed to create pipe.");
            exit(EXIT_FAILURE);
        }

        pid_t fixturePid = fork();
        if (fixturePid == -1) {
            perror("Failed to fork fixture.");
            exit(EXIT_FAILURE);
        }

        if (fixturePid == 0) {
            close(pipefd[0]);

            AceUnit_Result_t fixtureResult = { 0, 0, 0 };
            void (*const *testcase)(void);

            fork_runCatching((*fixture)->beforeAll);

            for (testcase = &(*fixture)->testcases[0]; *testcase != NULL; testcase++) {
                fixtureResult.testCaseCount++;

                pid_t testPid = fork();
                if (testPid == -1) {
                    perror("Failed to fork testcase.");
                    exit(EXIT_FAILURE);
                }

                if (testPid == 0) {
                    close(pipefd[1]);

                    fork_runCatching((*fixture)->beforeEach);
                    fork_runCatching(*testcase);
                    fork_runCatching((*fixture)->afterEach);

                    exit(EXIT_SUCCESS);
                } else {
                    int status;
                    waitpid(testPid, &status, 0);

                    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
                        fixtureResult.successCount++;
                    else
                        fixtureResult.failureCount++;
                }
            }

            fork_runCatching((*fixture)->afterAll);

            write(pipefd[1], &fixtureResult, sizeof(AceUnit_Result_t));
            close(pipefd[1]);
            exit(EXIT_SUCCESS);
        } else {
            int status;
            AceUnit_Result_t childTelemetry;
            close(pipefd[1]);
            waitpid(fixturePid, &status, 0);
            if (read(pipefd[0], &childTelemetry, sizeof(AceUnit_Result_t)) == sizeof(AceUnit_Result_t)) {
                result->testCaseCount += childTelemetry.testCaseCount;
                result->successCount += childTelemetry.successCount;
                result->failureCount += childTelemetry.failureCount;
            } else {
                result->failureCount++;
            }
            close(pipefd[0]);
        }
    }
}
