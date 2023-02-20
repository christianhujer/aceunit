CPPFLAGS:=-W -Wall -pedantic
LOADLIBES:=-laceunit-fork

.PHONY: all
all: test

leapyear_test: leapyear_test.o leapyear.o testcases.o

.PHONY: test
test: leapyear_test
	./leapyear_test

testcases.c: leapyear_test.o
	aceunit $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] leapyear_test testcases.c
