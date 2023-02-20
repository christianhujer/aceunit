#include <assert.h>
#include <stdio.h>

#define printme() do { fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, __func__); } while (0)

void beforeAll_2() {
    printme();
}

void afterAll_2() {
    printme();
}

void beforeEach_2() {
    printme();
}

void afterEach_2() {
    printme();
}

void test1_2() {
    printme();
}

void test2_2() {
    printme();
}

void test3_2() {
    printme();
}
