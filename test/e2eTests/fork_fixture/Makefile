CPPFLAGS:=-W -Wall -pedantic -I../../../include/
LOADLIBES:=../../../lib/libaceunit-fork.a

.PHONY: all
all: test

fork_test: fork_test.o testcases.o

.PHONY: test
test: SHELL:=bash
test: fork_test
	diff fork_test_expected.txt <(./fork_test 2>&1)

testcases.c: fork_test.o
	../../../bin/aceunit $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] fork_test testcases.c
