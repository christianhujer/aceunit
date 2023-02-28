#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define printme(func) do { fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, func); } while (0)

void test1() {
    printme("test1");
}

void test2() {
    printme("test2");
    assert(false);
}

void test3() {
    printme("test3");
    exit(1);
}

void test4() {
    printme("test4");
}
