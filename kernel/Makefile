TGTDIR := ../build/
TARGET := $(TGTDIR)kernel
SOURCE := $(wildcard *.c)
SUBOBJS := config.o satio.o shell.o util.o boot.o trap.o
OBJECTS = $(patsubst %.c, $(TGTDIR)%.o, $(SOURCE))
OBJECTS += $(patsubst %.o, $(TGTDIR)%.o, $(SUBOBJS))

TOOLPREFIX = loongarch64-unknown-linux-gnu-

CC = $(TOOLPREFIX)gcc
LD = $(TOOLPREFIX)ld

CFLAGS = -Wall -O2 -g3 -march=loongarch64 -mabi=lp64s\
	-ffreestanding -fno-common -nostdlib -I../include -fno-stack-protector -fno-pie -no-pie 

# -Wall means that all warnings are enabled
# -O2 means that the compiler will optimize the code
# -g3 means that the compiler will generate debugging information
# -march=loongarch64 means that the compiler will generate code for LoongArch64
# -mabi=lp64s means that the compiler will generate code for LP64S ABI
# -ffreestanding means that the compiler will not assume that the code is part of a larger program
# 开启后GCC就知道正在编译内核，因此禁用C标准库里的大部分库，并针对裸机环境进行调整。
# 而不使用此选项，gcc就会针对运行在操作系统上的应用编译。
# -fno-common means that the compiler will not allow uninitialized global variables
# -nostdlib means that the compiler will not use the standard C library
# -I means that the compiler will search for header files in the specified directory
# -fno-stack-protector means that the compiler will not generate stack protection code
# -fno-pie means that the compiler will not generate position-independent code
# -no-pie means that the compiler will not generate position-independent code

LDFLAGS = -z max-page-size=4096

$(TARGET): $(OBJECTS) ld.script
	$(LD) $(LDFLAGS) -T ld.script -o $(TARGET) $(OBJECTS)

$(TGTDIR)%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TGTDIR)config.o:
	@mkdir -p $(TGTDIR)config
	(cd config; make)

$(TGTDIR)satio.o:
	@mkdir -p $(TGTDIR)satio
	(cd satio; make)

$(TGTDIR)shell.o:
	@mkdir -p $(TGTDIR)shell
	(cd shell; make)

$(TGTDIR)util.o:
	@mkdir -p $(TGTDIR)util
	(cd util; make)

$(TGTDIR)boot.o:
	@mkdir -p $(TGTDIR)boot
	(cd boot; make)

$(TGTDIR)trap.o:
	@mkdir -p $(TGTDIR)trap
	(cd trap; make)

.PHONY: clean

clean: 
	rm -rf $(TARGET) $(OBJECTS)
