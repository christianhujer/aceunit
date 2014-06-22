.PHONY: all
all: MAIN

CC:=~/.wine/drive_c/Keil_v5_c251/C251/BIN/C251.EXE
CPPFLAGS:='INCDIR(../../include/)' 'DEFINE(ACEUNIT_SUITES)'
CFLAGS:=NOPRINT
COMPILE.c:=$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH)
%.o: OUTPUT_OPTION='OBJECT($@)'

empty:=
space:=$(empty) $(empty)
comma:=,

vpath %.c ../../src/

OBJS:=main.o Suite1.o DummyTest.o AceUnit.o AceUnitData.o Logger.o

# Note: The filename must be in caps because l251 creates a filena because l251 creates a filename in caps.
MAIN: $(OBJS)
	~/.wine/drive_c/Keil_v5_c251/C251/BIN/l251.exe $(subst $(space),$(comma),$(OBJS))

.c.o:
	$(CC) $< $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) $(OUTPUT_OPTION)

Suite1.c %Test.c:
	java -jar ../../generator/AceUnit.jar .

.PHONY: clean
clean:
	$(RM) $(OBJS) *Test.h Suite1.c MAIN MAIN.MAP
