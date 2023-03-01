arch:=$(notdir $(abspath .))
export QEMU_LD_PREFIX:=/usr/$(arch)/
ACEUNIT_HOME:=../../../
vpath %.c $(ACEUNIT_HOME)lib/
include $(ACEUNIT_HOME)/lib/Makefile
CC=$(arch)-gcc-10
AR=$(arch)-gcc-ar-10

ifeq "$(CC)" "clang"
CFLAGS+=-target $(arch)
LDFLAGS+=-target $(arch)
AR=llvm-ar
endif
