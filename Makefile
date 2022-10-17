TGTDIR := build/
TARGET := $(TGTDIR)image

.PHONY:

all:
	@mkdir -p build
	(cd kernel; make)

clean: 
	rm -rf build/
