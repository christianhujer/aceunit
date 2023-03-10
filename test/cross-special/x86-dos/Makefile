CC:=bcc
CFGLAGS:=-Md -ansi
LDGLAGS:=-Md -ansi
ACEUNIT_HOME:=../../../
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
