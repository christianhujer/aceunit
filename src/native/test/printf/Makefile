LOGGER=FullPlainLogger

ACE_UNIT_FILES=AceUnit.c AceUnit.h AceUnitData.c AceUnitData.h AceUnitAnnotations.h AceUnitLogging.h $(LOGGER).c AceUnit.jar

ACE_UNIT_PATH=../../../

ACE_UNIT_JAVA_SRC=$(shell find $(ACE_UNIT_PATH)/java/src -name "*.java")

FIXTURE_NAME=AceUnitPrintfTest

all: prepare compile test

clean:
	rm -f $(ACE_UNIT_FILES) $(FIXTURE_NAME).h runTests *.gcov *.gcno *.gcda

prepare: $(ACE_UNIT_FILES)

AceUnit.c: $(ACE_UNIT_PATH)/native/AceUnit.c
	cp $< $@

AceUnit.h: $(ACE_UNIT_PATH)/native/AceUnit.h
	cp $< $@

AceUnitData.c: $(ACE_UNIT_PATH)/native/AceUnitData.c
	cp $< $@

AceUnitData.h: $(ACE_UNIT_PATH)/native/AceUnitData.h
	cp $< $@

AceUnitAnnotations.h: $(ACE_UNIT_PATH)/native/AceUnitAnnotations.h
	cp $< $@

AceUnitLogging.h: $(ACE_UNIT_PATH)/native/AceUnitLogging.h
	cp $< $@

$(LOGGER).c: $(ACE_UNIT_PATH)/native/$(LOGGER).c
	cp $< $@

AceUnit.jar: $(ACE_UNIT_PATH)/java/AceUnit.jar
	cp $(ACE_UNIT_PATH)/java/AceUnit.jar $@

$(ACE_UNIT_PATH)/java/AceUnit.jar: $(ACE_UNIT_JAVA_SRC)
	ant -f $(ACE_UNIT_PATH)/java/build.xml

compile: runTests

$(FIXTURE_NAME).h: AceUnit.jar $(FIXTURE_NAME).c
	java -jar AceUnit.jar $(FIXTURE_NAME)

runTests: $(FIXTURE_NAME).c $(FIXTURE_NAME).h $(ACE_UNIT_FILES)
	$(CC) -std=c89 -pedantic -fprofile-arcs -ftest-coverage -Wall -g -o runTests *.c

test: runTests
	./runTests

doc: $(FIXTURE_NAME).c $(FIXTURE_NAME).h $(ACE_UNIT_FILES)
	doxygen

coverage: test
	gcov *.c
