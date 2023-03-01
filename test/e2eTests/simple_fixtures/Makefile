CPPFLAGS:=-W -Wall -pedantic -I../../../include/
LOADLIBES:=../../../lib/libaceunit-simple.a

ACEUNIT:=../../../bin/aceunit

.PHONY: all
all: test

testcases: simple_test1.o simple_test2.o testcases.o

.PHONY: test
test: SHELL:=bash
test: testcases
	diff simple_test_expected.txt <(./testcases 2>&1)

testcases.c: simple_test1.o simple_test2.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] testcases testcases.c
