ACEUNIT_HOME:=../../
vpath %.c $(ACEUNIT_HOME)/lib/
include $(ACEUNIT_HOME)/lib/Makefile
CC=clang
LD=clang
CFLAGS+=-fprofile-instr-generate -fcoverage-mapping
LDFLAGS+=-fprofile-instr-generate -fcoverage-mapping
test: export LLVM_PROFILE_FILE=$^.profraw

all: coverage-report

coverage-report: AceUnit_SimpleRunner_Test.profdata AceUnit_SetJmpRunner_Test.profdata AceUnit_AbortRunner_Test.profdata AceUnit_ForkRunner_Test.profdata
	llvm-cov show ./AceUnit_SimpleRunner_Test -instr-profile=AceUnit_SimpleRunner_Test.profdata
	llvm-cov show ./AceUnit_SetJmpRunner_Test -instr-profile=AceUnit_SetJmpRunner_Test.profdata
	llvm-cov show ./AceUnit_AbortRunner_Test -instr-profile=AceUnit_AbortRunner_Test.profdata
	llvm-cov show ./AceUnit_ForkRunner_Test -instr-profile=AceUnit_ForkRunner_Test.profdata

%.profdata: %.profraw
	llvm-profdata merge -sparse $^ -o $@

%.profraw: %
	LLVM_PROFILE_FILE=$@ ./$*

clean::
	$(RM) *.profraw *.profdata
