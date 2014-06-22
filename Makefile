.PHONY: all
## Performs all self-checks.
all: prjcheck

.PHONY: prjcheck
prjcheck:
	! grep -Rn ' $$' src include generator --include="*.[ch]" --include="*.java" --include="Makefile" --include="*.mak"
