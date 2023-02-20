#include <aceunit.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    AceUnit_Result_t result = { 0, 0, 0 };
    AceUnit_run(fixtures, &result);
    fprintf(stderr, "AceUnit: %d test cases, %d successful, %d failed.\n", result.testCaseCount, result.successCount, result.failureCount);
    return result.failureCount ? EXIT_FAILURE : EXIT_SUCCESS;
}
