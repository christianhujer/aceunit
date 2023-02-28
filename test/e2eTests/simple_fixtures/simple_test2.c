#include <assert.h>
#include <stdio.h>

#define printme(func) do { fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, func); } while (0)

void beforeAll_2() {
    printme("beforeAll_2");
}

void afterAll_2() {
    printme("afterAll_2");
}

void beforeEach_2() {
    printme("beforeEach_2");
}

void afterEach_2() {
    printme("afterEach_2");
}

void test1_2() {
    printme("test1_2");
}

void test2_2() {
    printme("test2_2");
}

void test3_2() {
    printme("test3_2");
}
