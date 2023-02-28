#include <stdio.h>


void Fixture2_beforeAll() {
    puts("Fixture2_beforeAll");
}

void Fixture2_afterAll() {
    puts("Fixture2_afterAll");
}

void Fixture2_beforeEach() {
    puts("Fixture2_beforeEach");
}

void Fixture2_afterEach() {
    puts("Fixture2_afterEach");
}

void Fixture2_test1() {
    puts("Fixture2_test1");
}

void Fixture2_test2() {
    puts("Fixture2_test2");
}
