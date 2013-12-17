CVERSION=c89

ACE_UNIT_PATH=../../..

LINT=splint

PARTS=\
      ExceptionHandling \
      TryExceptionHandling

VPATH=$(ACE_UNIT_PATH)/native

OBJECTS=$(addsuffix .o,$(PARTS))

LINTOUTS=$(addsuffix .ln,$(PARTS))

CPPFLAGS=-I . -I $(ACE_UNIT_PATH)/native

C_and_LD_FLAGS=-fprofile-arcs

CFLAGS=-fdiagnostics-show-option -std=$(CVERSION) -pedantic $(C_and_LD_FLAGS) -ftest-coverage -W -Wall -g

LDFLAGS=$(C_and_LD_FLAGS)

LINTFLAGS=-badflag -weak

.PHONY : all
all: test

TryExceptionHandling: $(OBJECTS)

%.d: %.c
	$(CPP) -M -MM -MG $(CPPFLAGS) $< | sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

coverage: test
	gcov *.c

test: TryExceptionHandling
	./TryExceptionHandling

.PHONY : clean
clean:
	rm -f TryExceptionHandling *.gcov *.gcno *.gcda *.o *.d

.PHONY : lint
lint: $(LINTOUTS)

$(OBJECTS) $(OBJECTS:.o=.d): Makefile

ifneq ($(MAKECMDGOALS),clean)
-include $(OBJECTS:.o=.d)
endif
