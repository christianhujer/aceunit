ACEUNIT_HOME=../../../../../
ACEUNIT:=$(ACEUNIT_HOME)/bin/aceunit
CPPFLAGS:=-W -Wall -pedantic -I$(ACEUNIT_HOME)include -MMD
ACEUNIT_LIBRARY:=$(ACEUNIT_HOME)/lib/libaceunit-fork.a
ifeq "$(shell uname -s)" "Darwin"
OBJCOPY:=llvm-objcopy
else
OBJCOPY:=objcopy
endif

.PHONY: all
all: test

hello: hello.o

.PHONY: test
test: hello_test
	./hello_test

hello_test: LOADLIBES+=-Wl,--wrap=puts -Wl,--wrap=main
hello_test: hello_test.o hello.o mock_puts.o testcases.o $(ACEUNIT_LIBRARY)

testcases.c: hello_test.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) $^ >$@

.PHONY: clean
clean::
	$(RM) hello *.[adios] hello_test

-include *.d

-include .config.mk
.INTERMEDIATE: .configtest.c .configtest.o
.configtest.c:
	echo "int main(void){}" >$@

.config.mk: .configtest.o
	echo "USER_LABEL_PREFIX:=$$(nm $^ | grep -q " _main" && echo "_" || echo "")" >$@

.PHONY: distclean
distclean::
	$(RM) .config.mk .configtest.[cdo]
