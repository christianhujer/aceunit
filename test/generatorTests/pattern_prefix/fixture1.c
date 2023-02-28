#include <stdio.h>


void Fixture1_beforeAll() {
    puts("Fixture1_beforeAll");
}

void Fixture1_afterAll() {
    puts("Fixture1_afterAll");
}

void Fixture1_beforeEach() {
    puts("Fixture1_beoreEach");
}

void Fixture1_afterEach() {
    puts("Fixture1_afterEach");
}

void Fixture1_test1() {
    puts("Fixture1_test1");
}

void Fixture1_test2() {
    puts("Fixture1_test2");
}
