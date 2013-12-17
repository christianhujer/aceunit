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

CPPFLAGS:=-MMD -DACEUNIT_CONFIG_FILE=\"AceUnitConfig.h\" -I . -I $(ACEUNIT_NATIVE_PATH)
C_and_LD_FLAGS:=-fprofile-arcs
CFLAGS?=-fdiagnostics-show-option -std=$(CVERSION) -pedantic $(C_and_LD_FLAGS) -ftest-coverage -W -Wall -g
CXXFLAGS?=-fdiagnostics-show-option -pedantic $(C_and_LD_FLAGS) -ftest-coverage -W -Wall -g
LDFLAGS?=$(C_and_LD_FLAGS)
LINTFLAGS?=-badflag -weak

.PHONY : all clean coverage lint test

all: test

$(MAIN): $(OBJECTS)

$(ACEUNIT_JAVA_PATH)/AceUnit.jar: $(ACEUNIT_JAVA_SRC)
	ant -f $(ACEUNIT_JAVA_PATH)/build.xml

#%.d: %.c
#	$(CPP) -M -MM -MG $(CPPFLAGS) $< | sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

coverage: test
	gcov *.c

test: $(MAIN)
	./$(MAIN)

clean:
	rm -f $(OBJECTS) $(GENERATED) $(DEPENDS) $(MAIN) $(OBJECTS:.o=.gcov) $(OBJECTS:.o=.gcno) $(OBJECTS:.o=.gcda)

lint: $(LINTOUTS)

$(OBJECTS) $(DEPENDS): Makefile

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif
