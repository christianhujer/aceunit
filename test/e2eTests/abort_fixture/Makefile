CPPFLAGS:=-W -Wall -pedantic -I../../../include/
LOADLIBES:=../../../lib/libaceunit-abort.a

.PHONY: all
all: test

abort_test: abort_test.o testcases.o

.PHONY: test
test: SHELL:=bash
test: abort_test
	diff abort_test_expected.txt <(./abort_test 2>&1)

testcases.c: abort_test.o
	../../../bin/aceunit $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] abort_test testcases.c
