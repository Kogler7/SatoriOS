TGTDIR := ../build/
TARGET := $(TGTDIR)kernel
SOURCE := $(wildcard *.c)
SUBOBJS := config.o satio.o shell.o util.o boot.o trap.o
OBJECTS = $(patsubst %.c, $(TGTDIR)%.o, $(SOURCE))
OBJECTS += $(patsubst %.o, $(TGTDIR)%.o, $(SUBOBJS))

export TOOLPREFIX = loongarch64-unknown-linux-gnu-

export CC = $(TOOLPREFIX)gcc
export LD = $(TOOLPREFIX)ld

export CFLAGS = -Wall -O2 -g3 \
	-march=loongarch64 -mabi=lp64s \
	-ffreestanding -fno-common \
	-nostdlib \
	-I../include \
	-fno-stack-protector \
	-fno-pie -no-pie 

export LDFLAGS = -z max-page-size=4096

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
