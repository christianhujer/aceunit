TESTGEN:=../../../bin/aceunit

define NL


endef

.PHONY: all
all: test

SHELL:=bash
.ONESHELL:

.PHONY: test

# Test that the generated output is as expected.
test: $(patsubst %.c,characterize/%,$(wildcard *.c))
characterize/%: actual/%.c | characterize/
	diff expected/$*.c actual/$*.c
	touch $@

# Given the file has no test cases,
# When generating the test source,
# Then it prints a warning message.
test: test_empty
.PHONY: test_empty
test_empty: zero.o
	diff <<<"zero.o: warning: No test cases found." - <($(TESTGEN) zero.o 2>&1 >/dev/null)

# When calling it with an unknown option,
# Then it prints a usage message on stderr,
# But it prints nothing to stdout,
# And it exits with status 1 (EXIT_FAILURE).
test: test_unknown_option
.PHONY: test_unknown_option
test_unknown_option:
	diff <<<"$(TESTGEN): illegal option -- x${NL}Usage: $(TESTGEN) [-h] [-p PATTERN] OBJECT_FILE..." - <($(TESTGEN) -x 2>&1 >/dev/null)
	diff /dev/null <($(TESTGEN) -x 2>/dev/null)
	! $(TESTGEN) -x $^ 2>/dev/null

actual/%.c: %.o | actual/
	$(TESTGEN) $^ >$@

.PRECIOUS: %/
%/:
	mkdir -p $@

.PHONY: clean
clean::
	$(RM) *.[adios] -r actual/ characterize/
