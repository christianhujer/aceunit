CPPFLAGS:=-W -Wall -pedantic
LOADLIBES:=-laceunit-fork
ACEUNIT:=aceunit
ACEUNIT_FLAGS:=

.PHONY: all
all: test

leapyear_test: leapyear_test.o leapyear.o testcases.o

.PHONY: test
test: leapyear_test
	./leapyear_test

testcases.c: leapyear_test.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] leapyear_test testcases.c
