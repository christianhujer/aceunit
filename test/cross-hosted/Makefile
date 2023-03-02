# Some platforms are known to currently not work.
# avr is excluded because it's not a hosted environment, and I haven't prepared a freestanding environment for qemu-system yet.
# hppa64, m68k, sh4, and sparc64 are excluded because either gcc or qemu or both do not work properly.
# m68k-amigaos is excluded as most will not have the environment setup for it.
subs:=$(filter-out \
    avr \
    hppa64-linux-gnu \
    m68k-amigaos \
    m68k-linux-gnu \
    sh4-linux-gnu \
    sparc64-linux-gnu \
    ,$(patsubst %/Makefile,%,$(wildcard */Makefile)))

# clang doesn't support Alpha AXP and HPPA.
# clang doesn't support amigaos as a target platform.
ifeq "$(CC)" "clang"
subs:=$(filter-out \
    alpha-linux-gnu \
    hppa-linux-gnu \
    hppa64-linux-gnu \
    m68k-amigaos \
    sh4-linux-gnu \
    ,$(subs))
endif

include ../../recurse.mk
