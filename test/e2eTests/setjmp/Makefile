CPPFLAGS:=-W -Wall -pedantic -I../../../include/
LOADLIBES:=../../../lib/libaceunit-setjmp.a

.PHONY: all
all: test

setjmp_test: setjmp_test.o testcases.o

.PHONY: test
test: SHELL:=bash
test: setjmp_test
	diff setjmp_test_expected.txt <(./setjmp_test 2>&1)

testcases.c: setjmp_test.o
	../../../bin/aceunit $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] setjmp_test testcases.c
