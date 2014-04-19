CPPFLAGS_SPECIFIC:=-MMD
C_and_LD_FLAGS:=-fprofile-arcs
CFLAGS?=-fdiagnostics-show-option -std=$(CVERSION) -pedantic $(C_and_LD_FLAGS) -ftest-coverage -W -Wall -g
CXXFLAGS?=-fdiagnostics-show-option -pedantic $(C_and_LD_FLAGS) -ftest-coverage -W -Wall -g
LDFLAGS?=$(C_and_LD_FLAGS)
