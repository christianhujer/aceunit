# It looks strange defining CC to a C++ compiler, but that's intentional:
# This testcase tests if AceUnit also works fine if somebody uses a C++ compiler to compile AceUnit C code.
CC=$(CXX)
CFLAGS=-fdiagnostics-show-option -pedantic $(C_and_LD_FLAGS) -ftest-coverage -W -Wall -g
MAIN=AceUnitMain
include ../common.mak
