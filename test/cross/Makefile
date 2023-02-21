# Some platforms are known to currently not work.
# avr is excluded because it's not a hosted environment, and I haven't prepared a freestanding environment for qemu-system yet.
# hppa64, m68k, sh4, and sparc64 are excluded because either gcc or qemu or both do not work properly.
subs:=$(filter-out \
    avr \
    hppa64 \
    m68k \
    sh4 \
    sparc64 \
    ,$(patsubst %/Makefile,%,$(wildcard */Makefile)))
include ../../recurse.mk
