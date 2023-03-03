ACEUNIT_HOME=../../
ACEUNIT:=$(ACEUNIT_HOME)/bin/aceunit
CPPFLAGS:=-W -Wall -pedantic -I../../include
ACEUNIT_LIBRARY:=$(ACEUNIT_HOME)/lib/libaceunit-fork.a
#LOADLIBES:=

.PHONY: all
all: test

leapyear_test: leapyear_test.o leapyear.o testcases.o $(ACEUNIT_LIBRARY)

.PHONY: test
test: leapyear_test
	./$^

testcases.c: leapyear_test.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] leapyear_test testcases.c
