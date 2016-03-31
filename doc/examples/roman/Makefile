# Path to AceUnit.
# Scope: local.
# Type: Single path.
ACE_UNIT_PATH:=../../..

# List of generated files.
# As a side effect, runs the AceUnit generator.
# Scope: local.
# Type: List of pathnames.
GENERATED_FILES:=$(shell java -jar $(ACE_UNIT_PATH)/generator/AceUnit.jar --print suites,headers .)

# List of source files.
# Scope: local.
# Type: List of scource files.
SOURCES:=$(wildcard *.c) $(filter %.c, $(GENERATED_FILES))

## Flags for the C compiler.
# Scope: External
# Type: Flags passed to the C compiler.
override CFLAGS+=-W -Wall -Werror -pedantic

## Flags for the C preprocessor.
# Scope: External.
# Type: Flags passed to all programs that do C preprocessing.
override CPPFLAGS+=-DACEUNIT_SUITES -I $(ACE_UNIT_PATH)/include

.PHONY: all
all: AceUnitMain
	./AceUnitMain

AceUnitMain: $(patsubst %.c,%.o,$(SOURCES)) ../../../libaceunit.a
	$(CC) $^ -o $@

../../../libaceunit.a:
	$(MAKE) -C $(dir $@) $(notdir $@)

.PHONY: clean
clean:
	rm -f $(FIXTURE_NAME).h AceUnitMain *.o $(GENERATED_FILES)

$(GENERATED_FILES): ;
