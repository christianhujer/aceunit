export PATH:=$(abspath amiga/bin):$(PATH)

CC:=m68k-amigaos-gcc
LDFLAGS:=-L./amiga/m68k-amigaos/lib/

.PHONY: all
all: test

.PHONY: test
# Note: To run the test, requires that AmiTools are installed https://github.com/cnvogelg/amitools
# and setup with binfmt https://github.com/cnvogelg/amitools/issues/176
test: SHELL:=bash
test: hello
	diff <<<"Hello, world!" - <(./hello)

.PHONY: download
download: amiga-gcc.tgz
amiga-gcc.tgz:
	wget https://github.com/bebbo/amiga-gcc/releases/download/Mechen/amiga-gcc.tgz

.PHONY: extract
extract: amiga/
amiga/: amiga-gcc.tgz
	tar xf amiga-gcc.tgz --strip-components=4
	touch $@

.PHONY: clean
clean::
	$(RM) *.[adios] hello

.PHONY: distclean
distclean::
	$(RM) amiga-gcc.tgz -r amiga/
