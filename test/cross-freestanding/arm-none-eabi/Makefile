export QEMU_LD_PREFIX:=/usr/arm-none-eabi/
ACEUNIT_HOME:=../../../
.DEFAULT_GOAL:=libs
vpath %.c $(ACEUNIT_HOME)lib/
include $(ACEUNIT_HOME)/lib/Makefile
LDFLAGS:=-ffreestanding -nostdlib -nostartfiles
CC=arm-none-eabi-gcc
AR=arm-none-eabi-gcc-ar
