CPPFLAGS:=-W -Wall -pedantic -I../../include
LOADLIBES:=../../lib/libaceunit-fork.a

.PHONY: all
all: test

leapyear_test: leapyear_test.o leapyear.o testcases.o

.PHONY: test
test: leapyear_test
	./leapyear_test

testcases.c: leapyear_test.o
	../../bin/aceunit $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] leapyear_test testcases.c
