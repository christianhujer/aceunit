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

        int fixtureStatus;
        pid_t fixturePid = fork();
        switch (fixturePid) {
        case -1:
            perror("Failed to fork fixture.");
            exit(EXIT_FAILURE);
        case 0:
            close(pipefd[0]);

            AceUnit_Result_t fixtureResult = { 0, 0, 0 };
            void (*const *testcase)(void);

            fork_runCatching((*fixture)->beforeAll);

            for (testcase = &(*fixture)->testcases[0]; *testcase != NULL; testcase++) {
                fixtureResult.testCaseCount++;

                int testenvStatus;
                pid_t testEnvPid = fork();
                switch(testEnvPid) {
                case -1:
                    perror("Failed to fork testcase.");
                    exit(EXIT_FAILURE);
                case 0:
                    close(pipefd[1]);
                    bool testCaseSuccess = false;

                    fork_runCatching((*fixture)->beforeEach);

                    int executionStatus;
                    pid_t executionPid = fork();
                    switch (executionPid) {
                    case -1:
                        perror("Failed to fork testcase.");
                        exit(EXIT_FAILURE);
                    case 0:
                        fork_runCatching(*testcase);
                        exit(EXIT_SUCCESS);
                    default:
                        waitpid(executionPid, &executionStatus, 0);

                        if (WIFEXITED(executionStatus) && WEXITSTATUS(executionStatus) == EXIT_SUCCESS)
                            testCaseSuccess = true;
                    }

                    fork_runCatching((*fixture)->afterEach);

                    exit(testCaseSuccess ? EXIT_SUCCESS : EXIT_FAILURE);
                default:
                    waitpid(testEnvPid, &testenvStatus, 0);

                    if (WIFEXITED(testenvStatus) && WEXITSTATUS(testenvStatus) == EXIT_SUCCESS)
                        fixtureResult.successCount++;
                    else
                        fixtureResult.failureCount++;
                }
            }

            fork_runCatching((*fixture)->afterAll);

            write(pipefd[1], &fixtureResult, sizeof(AceUnit_Result_t));
            close(pipefd[1]);
            exit(EXIT_SUCCESS);
        default:
            close(pipefd[1]);
            waitpid(fixturePid, &fixtureStatus, 0);
            AceUnit_Result_t childTelemetry;
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
