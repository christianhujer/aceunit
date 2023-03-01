ACEUNIT:=../../../bin/aceunit
ACEUNIT_FLAGS+=-p Prefix_

.PHONY: all
all: test

.PHONY: test
test:: testcases.c
	diff testcases.c expected.c

testcases.c: prefixed.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) prefixed.o >$@

.PHONY: clean
clean::
	$(RM) *.[adios] testcases.c
