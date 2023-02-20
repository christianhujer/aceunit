#include <assert.h>
#include <stdio.h>

#define printme() do { fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, __func__); } while (0)

void beforeAll_1() {
    printme();
}

void afterAll_1() {
    printme();
}

void beforeEach_1() {
    printme();
}

void afterEach_1() {
    printme();
}

void test1_1() {
    printme();
}

void test2_1() {
    printme();
}

void test3_1() {
    printme();
}
