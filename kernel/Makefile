TGTDIR := ../build/
TARGET := $(TGTDIR)kernel
SOURCE := $(wildcard *.c)
SUBOBJS = $(filter %.o, $(patsubst ./%, %.o, $(shell find -maxdepth 1 -type d)))
OBJECTS = $(patsubst %.c, $(TGTDIR)%.o, $(SOURCE))
OBJECTS += $(patsubst %.o, $(TGTDIR)%.o, $(SUBOBJS))

export ECHOPRE := @
export TOOLPREFIX := loongarch64-unknown-linux-gnu-

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
	@echo Linking $(TARGET)
	$(ECHOPRE)$(LD) $(LDFLAGS) -T ld.script -o $(TARGET) $(OBJECTS)

$(TGTDIR)%.o : %.c
	@echo Compiling $<
	$(ECHOPRE)$(CC) $(CFLAGS) -c -o $@ $<

$(TGTDIR)%.o :
	@echo -------------------------- == $(subst .o,,$@) == ------------------------------
	@mkdir -p $(subst .o,,$@)
	@(cd $(subst $(TGTDIR),,$(subst .o,,$@)); make)

.PHONY: clean

clean: 
	rm -rf $(TARGET) $(OBJECTS)
