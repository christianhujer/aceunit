export PATH:=$(abspath amiga/bin):$(PATH)

CC:=m68k-amigaos-gcc
AR:=m68k-amigaos-ar
LDFLAGS:=-L./amiga/m68k-amigaos/lib/ -noixemul

#.PHONY: amiga-test
#amiga-test: AceUnit_SimpleRunner_Test AceUnit_SetJmpRunner_Test libaceunit-abort.a libaceunit-fork.a
#	./AceUnit_SimpleRunner_Test
#	./AceUnit_SetJmpRunner_Test

ACEUNIT_HOME:=../../../
vpath %.c $(ACEUNIT_HOME)/lib/
include $(ACEUNIT_HOME)/lib/Makefile

.PHONY: download
download: amiga-gcc.tgz
amiga-gcc.tgz:
	wget https://github.com/bebbo/amiga-gcc/releases/download/Mechen/amiga-gcc.tgz

.PHONY: extract
extract: amiga/
amiga/: amiga-gcc.tgz
	tar xf amiga-gcc.tgz --strip-components=4
	touch $@

.PHONY: distclean
distclean::
	$(RM) amiga-gcc.tgz -r amiga/
