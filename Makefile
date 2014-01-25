.PHONY: all
## Performs all self-checks.
all: prjcheck

.PHONY: prjcheck
prjcheck:
	! grep -Rn ' $$' src --include="*.[ch]" --include="*.java"
