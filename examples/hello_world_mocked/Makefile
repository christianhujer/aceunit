ACEUNIT_HOME=../../
ACEUNIT:=$(ACEUNIT_HOME)/bin/aceunit
CPPFLAGS:=-W -Wall -pedantic -I../../include
ACEUNIT_LIBRARY:=$(ACEUNIT_HOME)/lib/libaceunit-fork.a

.PHONY: all
all: test

hello: hello.o

.PHONY: test
test: hello_test
	./hello_test

mocked_hello.o: hello.o
	objcopy --redefine-sym main=original_main --redefine-sym puts=mock_puts $^ $@

hello_test: hello_test.o mock_puts.o mocked_hello.o testcases.o $(ACEUNIT_LIBRARY)

testcases.c: hello_test.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) $^ >$@

.PHONY: clean
clean::
	$(RM) hello *.[adios] hello_test
