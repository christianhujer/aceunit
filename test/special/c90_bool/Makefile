ACEUNIT_HOME:=../../../
CPPFLAGS:=-W -Wall -pedantic -Werror -I$(ACEUNIT_HOME)/include
c90_macros_defined: CFLAGS:=-std=c90
c90_macros_override: CFLAGS:=-std=c90

.PHONY: all
all: c90_macros_defined c90_macros_override

.PHONY: clean
clean::
	$(RM) *.[adios] c90_macros_defined c90_macros_override
