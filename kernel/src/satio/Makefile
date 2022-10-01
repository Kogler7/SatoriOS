SRC := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRC))

TOOLPREFIX = loongarch64-unknown-linux-gnu-

CC = $(TOOLPREFIX)gcc
LD = $(TOOLPREFIX)ld

CFLAGS = -Wall -O2 -g3 -march=loongarch64 -mabi=lp64s -ffreestanding -fno-common -nostdlib -I. -fno-stack-protector -fno-pie -no-pie 
LDFLAGS = -z max-page-size=4096

all: satio.o

satio.o: $(OBJS)
	$(LD) $(LDFLAGS) -r -o ../output/config.o $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean: 
	rm -f *.o ./kernel
