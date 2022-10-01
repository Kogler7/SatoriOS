OUTDIR := ../../output/
SRC := $(wildcard *.c)
OBJS := $(patsubst %.c, $(OUTDIR)%.o, $(SRC))
OUT := $(OUTDIR)config.o

TOOLPREFIX = loongarch64-unknown-linux-gnu-

CC = $(TOOLPREFIX)gcc
LD = $(TOOLPREFIX)ld

CFLAGS = -Wall -O2 -g3 -march=loongarch64 -mabi=lp64s -ffreestanding -fno-common -nostdlib -I. -fno-stack-protector -fno-pie -no-pie 

all: $(OUT)

$(OUT): $(OBJS)
	$(LD) -r -o $(OUT) $(OBJS)

$(OUTDIR)%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean: 
	rm -f *.o ./kernel
