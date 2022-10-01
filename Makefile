OBJS = output/kernel

TOOLPREFIX = loongarch64-unknown-linux-gnu-

LD = $(TOOLPREFIX)ld

LDFLAGS = -z max-page-size=4096

all: image

image: $(OBJS)
	$(OBJS) > image
# > image means that the output of $(OBJS) is redirected to image

output/kernel:
	(cd kernel; make)

.PHONY: clean

clean: 
	rm -f *.o ./kernel
