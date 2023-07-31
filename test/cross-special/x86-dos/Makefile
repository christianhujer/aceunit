ACEUNIT_FLAGS:=-t nm -b nm86 -s _
ACEUNIT_HOME:=../../../
CC:=bcc

vpath %.c $(ACEUNIT_HOME)/lib/

.PHONY: test-bcc
test-bcc: simple.exe setjmp.exe

simple.exe: AceUnit_SimpleRunner_Test
	cp $^ $@

setjmp.exe: AceUnit_SetJmpRunner_Test
	cp $^ $@

include $(ACEUNIT_HOME)/lib/Makefile
CFLAGS:=-Md -ansi
LDFLAGS:=-Md -ansi

clean::
	$(RM) *.exe
