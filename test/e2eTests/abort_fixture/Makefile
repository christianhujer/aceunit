CPPFLAGS:=-W -Wall -pedantic -I../../../include/
LOADLIBES:=../../../lib/libaceunit-abort.a

ACEUNIT:=../../../bin/aceunit

.PHONY: all
all: test

abort_test: abort_test.o testcases.o

.PHONY: test
test: SHELL:=bash
test: abort_test
	diff $(firstword $(wildcard abort_test_expected_$(CC).txt) abort_test_expected.txt) <(./abort_test 2>&1)

testcases.c: abort_test.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] abort_test testcases.c
