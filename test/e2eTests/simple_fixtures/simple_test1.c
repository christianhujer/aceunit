#include <assert.h>
#include <stdio.h>

#define printme(func) do { fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, func); } while (0)

void beforeAll_1() {
    printme("beforeAll_1");
}

void afterAll_1() {
    printme("afterAll_1");
}

void beforeEach_1() {
    printme("beforeEach_1");
}

void afterEach_1() {
    printme("afterEach_1");
}

void test1_1() {
    printme("test1_1");
}

void test2_1() {
    printme("test2_1");
}

void test3_1() {
    printme("test3_1");
}
