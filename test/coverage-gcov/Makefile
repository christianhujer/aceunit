ACEUNIT_HOME:=../../
vpath %.c $(ACEUNIT_HOME)/lib/
include $(ACEUNIT_HOME)/lib/Makefile
CFLAGS+=--coverage -ftest-coverage -fprofile-arcs
LOADLIBES+=-lgcov

all: coverage-report

.PHONY: coverage-report
coverage-report: AceUnit_SimpleRunner.c.gcov AceUnit_SetJmpRunner.c.gcov AceUnit_AbortRunner.c.gcov AceUnit_ForkRunner.c.gcov

%.gcov:
	gcov $*

clean::
	$(RM) *.gcno *.gcov *.gcda
