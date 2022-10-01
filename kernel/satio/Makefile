TGTDIR := ../../build/
INCDIR := ../../include
TARGET := $(TGTDIR)satio.o
SOURCE := $(wildcard *.c)
OBJECTS := $(patsubst %.c, $(TGTDIR)%.o, $(SOURCE))

TOOLPREFIX = loongarch64-unknown-linux-gnu-

CC = $(TOOLPREFIX)gcc
LD = $(TOOLPREFIX)ld

CFLAGS = -Wall -O2 -g3 -march=loongarch64 -mabi=lp64s\
	-ffreestanding -fno-common -nostdlib -I$(INCDIR) -fno-stack-protector -fno-pie -no-pie 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -r -o $(TARGET) $(OBJECTS)

$(TGTDIR)%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean: 
	rm -f $(TARGET)
