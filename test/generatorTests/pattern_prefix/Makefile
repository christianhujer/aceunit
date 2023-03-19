ACEUNIT:=../../../bin/aceunit

.PHONY: all
all: test

.PHONY: test
test:: testcases.c
	diff testcases.c expected.c

testcases.c: fixture1.o fixture2.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) -p '[^_][^_]*_' $^ >$@

.PHONY: clean
clean::
	$(RM) *.[adios] testcases.c
