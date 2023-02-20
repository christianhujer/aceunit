#include <assert.h>
#include <stdio.h>

#define printme() do { fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, __func__); } while (0)

void test1() {
    printme();
}

void test2() {
    printme();
}

void test3() {
    printme();
}
