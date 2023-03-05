ACEUNIT:=../../../bin/aceunit

define NL


endef

.PHONY: all
all: test

SHELL:=bash
.PHONY: test

# Test that the generated output is as expected.
test: $(patsubst %.c,characterize/%,$(wildcard *.c))
characterize/%: actual/%.c | characterize/
	diff expected/$*.c actual/$*.c && touch $@

# Given the file has no test cases,
# When generating the test source,
# Then it prints a warning message.
test: test_empty
.PHONY: test_empty
test_empty: zero.o
	diff <<<"zero.o: warning: No test cases found." - <($(ACEUNIT) $(ACEUNIT_FLAGS) zero.o 2>&1 >/dev/null)

# When calling it with an unknown option,
# Then it prints a usage message on stderr,
# But it prints nothing to stdout,
# And it exits with status 1 (EXIT_FAILURE).
# Important: set LC_ALL to prevent locale to get in the way of test expectations.
test: test_unknown_option
.PHONY: test_unknown_option
test_unknown_option: export SHELLOPTS:=$(if $(SHELLOPTS),$(SHELLOPTS):)pipefail:errexit
.ONESHELL: test_unknown_option
test_unknown_option:
	diff <<<"$(ACEUNIT): illegal option -- x${NL}Usage: $(ACEUNIT) [OPTION]... OBJECT_FILE..." - <(LC_ALL=C $(ACEUNIT) -x 2>&1 >/dev/null)
	diff /dev/null <($(ACEUNIT) -x 2>/dev/null)
	! $(ACEUNIT) -x $^ 2>/dev/null

actual/%.c: %.o | actual/
	$(ACEUNIT) $(ACEUNIT_FLAGS) $^ >$@

.PRECIOUS: %/
%/:
	mkdir -p $@

.PHONY: clean
clean::
	$(RM) *.[adios] -r actual/ characterize/
