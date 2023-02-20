CPPFLAGS:=-W -Wall -pedantic -I../../../include/
LOADLIBES:=../../../lib/libaceunit-simple.a

.PHONY: all
all: test

simple_test: simple_test.o testcases.o

.PHONY: test
test: SHELL:=bash
test: simple_test
	diff simple_test_expected.txt <(./simple_test 2>&1)

testcases.c: simple_test.o
	../../../bin/aceunit $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] simple_test testcases.c
