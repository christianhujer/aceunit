#include <stdio.h>


#define printme() \
    do { \
        puts(__func__); \
    } while (0)


void Fixture1_beforeAll() {
    printme();
}

void Fixture1_afterAll() {
    printme();
}

void Fixture1_beforeEach() {
    printme();
}

void Fixture1_afterEach() {
    printme();
}

void Fixture1_test1() {
    printme();
}

void Fixture1_test2() {
    printme();
}
