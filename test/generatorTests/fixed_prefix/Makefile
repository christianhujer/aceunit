ACEUNIT:=../../../bin/aceunit

.PHONY: all
all: test

.PHONY: test
test:: testcases.c
	diff testcases.c expected.c

testcases.c: prefixed.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) -p Prefix_ prefixed.o >$@

.PHONY: clean
clean::
	$(RM) *.[adios] testcases.c
