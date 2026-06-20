ACEUNIT_HOME?=../
CPPFLAGS+=-I$(ACEUNIT_HOME)/include/
CFLAGS+=-W -Wall -pedantic
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

libaceunit-simple.a: AceUnit_Main.o AceUnit_Runner.o AceUnit_Wrap.o AceUnit_SimpleRunner.o
libaceunit-abort.a: AceUnit_Main.o AceUnit_Runner.o AceUnit_Wrap.o AceUnit_AbortRunner.o
libaceunit-fork.a: AceUnit_Main.o AceUnit_Wrap.o AceUnit_ForkRunner.o
libaceunit-setjmp.a: AceUnit_Main.o AceUnit_Runner.o AceUnit_Wrap.o AceUnit_SetJmpRunner.o
#(%): %
#	flock $@.lock $(AR) $(ARFLAGS) $@ $<
%.a:
	$(AR) $(ARFLAGS) $@ $?

test: test_SimpleRunner test_AbortRunner test_ForkRunner test_SetJmpRunner

test_SimpleRunner: test/AceUnit_SimpleRunner_Test
	test/AceUnit_SimpleRunner_Test

test_AbortRunner: test/AceUnit_AbortRunner_Test
	test/AceUnit_AbortRunner_Test

test_ForkRunner: test/AceUnit_ForkRunner_Test
	test/AceUnit_ForkRunner_Test

test_SetJmpRunner: test/AceUnit_SetJmpRunner_Test
	test/AceUnit_SetJmpRunner_Test

test/AceUnit_SimpleRunner_Test: test/AceUnit_SimpleRunner_Test.o libaceunit-simple.a
test/AceUnit_AbortRunner_Test: test/AceUnit_AbortRunner_Test.o test/AceUnit_AbortRunner_Fixture.o libaceunit-abort.a
test/AceUnit_ForkRunner_Test: test/AceUnit_ForkRunner_Test.o test/AceUnit_ForkRunner_Fixture.o libaceunit-fork.a
test/AceUnit_SetJmpRunner_Test: test/AceUnit_SetJmpRunner_Test.o test/AceUnit_SetJmpRunner_Fixture.o libaceunit-setjmp.a

test/%_Fixture.c: test/%_Test.o
	$(ACEUNIT) $(ACEUNIT_FLAGS) $^ >$@

# Don't delete this. It looks redundant only when building in lib/.
# But when building somewhere else with vpath set, this is important.
test/AceUnit_SimpleRunner_Test.o test/AceUnit_AbortRunner_Test.o test/AceUnit_ForkRunner_Test.o test/AceUnit_SetJmpRunner_Test.o: | test/
test/:
	mkdir -p $@

.PHONY: clean
## clean:	Removes all generated files.
clean::
	$(RM) *.[adios] test/*.[adios] *.bc test/AceUnit_*Runner_Test

.PHONY: help
## help:	Print this help text.
help:
	@sed -En 's/^## ?//p' $(MAKEFILE_LIST)
