TGTDIR := build/
TARGET := $(TGTDIR)image

.PHONY:

$(TARGET):
	@mkdir -p build
	(cd kernel; make)

clean: 
	rm -rf build/
