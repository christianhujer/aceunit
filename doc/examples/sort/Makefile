# Path to AceUnit.
# Scope: local.
# Type: Single path.
ACE_UNIT_PATH:=../../..

# List of generated files.
# As a side effect, runs the AceUnit generator.
# Scope: local.
# Type: List of pathnames.
GENERATED_FILES:=$(shell java -jar $(ACE_UNIT_PATH)/java/AceUnit.jar --print suites,headers .)

# List of source files.
# Scope: local.
# Type: List of scource files.
SOURCES:=AceUnitMain.c AceUnit.c AceUnitData.c FullPlainLogger.c $(wildcard *.c) $(filter %.c, $(GENERATED_FILES))

## Flags for the C compiler.
# Scope: External
# Type: Flags passed to the C compiler.
override CFLAGS+=-W -Wall -pedantic

## Flags for the C preprocessor.
# Scope: External.
# Type: Flags passed to all programs that do C preprocessing.
override CPPFLAGS+=-DACEUNIT_SUITES -I $(ACE_UNIT_PATH)/native

# Sets the path where to find C source files.
vpath %.c . $(ACE_UNIT_PATH)/native $(ACE_UNIT_PATH)/native/loggers

all: AceUnitMain
	./AceUnitMain

AceUnitMain: $(patsubst %.c,%.o,$(SOURCES))

clean:
	rm -f $(FIXTURE_NAME).h AceUnitMain *.o $(GENERATED_FILES)

$(GENERATED_FILES): ;
