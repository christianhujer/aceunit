#include <stdio.h>


#define printme() \
    do { \
        puts(__func__); \
    } while (0)


void Prefix_beforeAll() {
    printme();
}

void Prefix_afterAll() {
    printme();
}

void Prefix_beforeEach() {
    printme();
}

void Prefix_afterEach() {
    printme();
}

void Prefix_test1() {
    printme();
}

void Prefix_test2() {
    printme();
}
