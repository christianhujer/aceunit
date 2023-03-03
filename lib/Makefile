ACEUNIT_HOME?=../
CPPFLAGS+=-I$(ACEUNIT_HOME)/include/ -W -Wall -pedantic -Werror
ACEUNIT:=$(ACEUNIT_HOME)/bin/aceunit

.PHONY: all
## all:	Builds and tests the AceUnit libraries.
all: test

# Our archives are small, and we don't need individual member update.
# Better update the archive all at once than individual members to prevent race conditions on make -j.

#libraries: \
#	libaceunit-simple.a(AceUnit_Main.o AceUnit_Runner.o AceUnit_SimpleRunner.o) \
#	libaceunit-abort.a(AceUnit_Main.o AceUnit_Runner.o AceUnit_AbortRunner.o) \
#	libaceunit-fork.a(AceUnit_Main.o AceUnit_Runner.o AceUnit_ForkRunner.o) \
#	libaceunit-setjmp.a(AceUnit_Main.o AceUnit_Runner.o AceUnit_SetJmpRunner.o) \

.PHONY: libs
## libs:	Builds the AceUnit libraries (without testing them).
libs: \
    libaceunit-simple.a \
    libaceunit-abort.a \
    libaceunit-fork.a \
    libaceunit-setjmp.a \

libaceunit-simple.a: AceUnit_Main.o AceUnit_Runner.o AceUnit_SimpleRunner.o
libaceunit-abort.a: AceUnit_Main.o AceUnit_Runner.o AceUnit_AbortRunner.o
libaceunit-fork.a: AceUnit_Main.o AceUnit_Runner.o AceUnit_ForkRunner.o
libaceunit-setjmp.a: AceUnit_Main.o AceUnit_Runner.o AceUnit_SetJmpRunner.o
#(%): %
#	flock $@.lock $(AR) $(ARFLAGS) $@ $<
%.a:
	$(AR) $(ARFLAGS) $@ $?

test:: AceUnit_SimpleRunner_Test
	./AceUnit_SimpleRunner_Test

test:: AceUnit_AbortRunner_Test
	./AceUnit_AbortRunner_Test

test:: AceUnit_ForkRunner_Test
	./AceUnit_ForkRunner_Test

test:: AceUnit_SetJmpRunner_Test
	./AceUnit_SetJmpRunner_Test

AceUnit_SimpleRunner_Test: AceUnit_SimpleRunner_Test.o libaceunit-simple.a
AceUnit_AbortRunner_Test: AceUnit_AbortRunner_Test.o libaceunit-abort.a
AceUnit_ForkRunner_Test: AceUnit_ForkRunner_Test.o libaceunit-fork.a
AceUnit_SetJmpRunner_Test: AceUnit_SetJmpRunner_Test.o AceUnit_SetJmpRunner_Fixture.o libaceunit-setjmp.a

%_Fixture.c: %_Test.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) $^ >$@

.PHONY: clean
## clean:	Removes all generated files.
clean::
	$(RM) *.[adios] *.bc AceUnit_*Runner_Test

.PHONY: help
## help:	Print this help text.
help:
	@sed -n 's/^## \?//p' $(MAKEFILE_LIST)
