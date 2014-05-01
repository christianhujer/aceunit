CPPFLAGS_SPECIFIC=--md --no_depend_system_headers --depend_format=unix --phony_targets --depend=$(patsubst %.o,%.d,$@)
CVERSION:=$(if $(filter c89,$(CVERSION)),c99,$(CVERSION))
CFLAGS?=--$(CVERSION) --strict --diag_error=warning

## The path to the Keil armcc compiler.
# Set this to the directory which contains the bin directory that contains armcc.path of your Keil armcc compiler.
ARMCC_HOME:=/home/cher/.wine/drive_c/Keil_v5/ARM/ARMCC
CC:=armcc.exe
export PATH:=/home/cher/.wine/drive_c/Keil_v5/ARM/ARMCC/bin:$(PATH)
