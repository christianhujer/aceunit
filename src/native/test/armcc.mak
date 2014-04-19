CPPFLAGS_SPECIFIC=--md --no_depend_system_headers --depend_format=unix --phony_targets --depend=$(patsubst %.o,%.d,$@)
CVERSION:=$(if $(filter c89,$(CVERSION)),c99,$(CVERSION))
CFLAGS?=--$(CVERSION) --strict --diag_error=warning

# Set this to the path of your Keil armcc compiler.
CC:= /home/cher/.wine/drive_c/Keil_v5/ARM/ARMCC/bin/armcc.exe
