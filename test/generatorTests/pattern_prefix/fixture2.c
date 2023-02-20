#include <stdio.h>


#define printme() \
    do { \
        puts(__func__); \
    } while (0)


void Fixture2_beforeAll() {
    printme();
}

void Fixture2_afterAll() {
    printme();
}

void Fixture2_beforeEach() {
    printme();
}

void Fixture2_afterEach() {
    printme();
}

void Fixture2_test1() {
    printme();
}

void Fixture2_test2() {
    printme();
}
