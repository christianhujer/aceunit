ACEUNIT_HOME:=../../../
ACEUNIT:=$(ACEUNIT_HOME)/bin/aceunit
ACEUNIT_FLAGS:=-s _

.PHONY: all
all: test

.PHONY: test
test:: testcases.c
	diff testcases.c expected.c

testcases.c: fixture.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] testcases.c
