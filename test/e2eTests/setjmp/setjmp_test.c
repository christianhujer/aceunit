#include <stdio.h>
#include <aceunit.h>

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
}
