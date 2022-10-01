SRC := $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
SUBS := config.o satio.o
OBJS += $(patsubst %.o, ../output/%.o, $(SUBS))

TOOLPREFIX = loongarch64-unknown-linux-gnu-

CC = $(TOOLPREFIX)gcc
LD = $(TOOLPREFIX)ld

CFLAGS = -Wall -O2 -g3 -march=loongarch64 -mabi=lp64s -ffreestanding -fno-common -nostdlib -I. -fno-stack-protector -fno-pie -no-pie 
LDFLAGS = -z max-page-size=4096

all: kernel

kernel: $(OBJS) ld.script
	$(LD) $(LDFLAGS) -T ld.script -o ../output/kernel $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

../output/config.o:
	(cd config; make)

../output/satio.o:
	(cd satio; make)

.PHONY: clean

clean: 
	rm -f *.o ./kernel
