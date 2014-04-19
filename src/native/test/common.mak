LOGGER?=FullPlainLogger
CVERSION?=c89
MAIN?=RunTests

ACEUNIT_NATIVE_PATH:=../..
ACEUNIT_JAVA_PATH:=../../../java
ACEUNIT_JAVA_SRC:=$(shell find $(ACEUNIT_JAVA_PATH)/src -name "*.java")
ACEUNIT_PARTS:=AceUnit AceUnitData $(LOGGER)

VPATH=$(ACEUNIT_NATIVE_PATH) $(ACEUNIT_NATIVE_PATH)/loggers

GENERATED:=$(shell java -ea -jar $(ACEUNIT_JAVA_PATH)/AceUnit.jar --exit true --print=generated $(ACEUNIT_OPTS) -o alltests.txt .)
SUITES:=$(filter *.c,$(GENERATED))
CSOURCES:=$(sort $(shell find . -name "*.c")) $(SUITES)
CXXSOURCES:=$(sort $(shell find . -name "*.cpp"))
OBJECTS:=$(CSOURCES:.c=.o) $(CXXSOURCES:.cpp=.o) $(addsuffix .o,$(ACEUNIT_PARTS)) $(addsuffix .o,$(MAIN))
DEPENDS:=$(OBJECTS:.o=.d)
LINTOUTS:=$(OBJECTS:.o=.ln)

LINT:=splint

COMPILER?=gcc
include ../$(COMPILER).mak
-include $(COMPILER).mak

CPPFLAGS=$(CPPFLAGS_SPECIFIC) -DACEUNIT_CONFIG_FILE=\"AceUnitConfig.h\" -I . -I $(ACEUNIT_NATIVE_PATH)

LINTFLAGS?=+quiet -badflag -weak

.PHONY : all clean coverage lint help

## Default target.
# Same as test.
all: test

$(MAIN): $(OBJECTS)

$(ACEUNIT_JAVA_PATH)/AceUnit.jar: $(ACEUNIT_JAVA_SRC)
	ant -f $(ACEUNIT_JAVA_PATH)/build.xml

#%.d: %.c
#	$(CPP) -M -MM -MG $(CPPFLAGS) $< | sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

## Creates a coverage report.
coverage: test
	gcov *.c

## Runs the tests.
# Note: Tests are run incrementally.
# They will only be re-run if the input changed.
test: $(MAIN)
	./$(MAIN)
	touch test

## Removes all generated files.
clean:
	rm -f $(OBJECTS) $(GENERATED) $(DEPENDS) $(MAIN) $(OBJECTS:.o=.c.gcov) $(OBJECTS:.o=.gcno) $(OBJECTS:.o=.gcda) test

## Runs lint.
lint: $(LINTOUTS)

$(OBJECTS) $(DEPENDS): $(MAKEFILE_LIST)

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

../makehelp.pl:
	wget -q --no-check-certificate -O $@ https://github.com/christianhujer/makehelp/raw/master/makehelp.pl

## Prints this help text.
help: ../makehelp.pl
	@perl $^ $(MAKEFILE_LIST)
