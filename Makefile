OBJECTS = build/kernel

TOOLPREFIX = loongarch64-unknown-linux-gnu-

LD = $(TOOLPREFIX)ld

LDFLAGS = -z max-page-size=4096

all: build/kernel

image: $(OBJECTS)
	$(OBJECTS) > image
# > image means that the output of $(OBJECTS) is redirected to image

build/kernel:
	@mkdir -p build
	(cd kernel; make)

.PHONY: clean

clean: 
	rm -f build
