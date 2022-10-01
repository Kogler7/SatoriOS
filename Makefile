TGTDIR := build/
TARGET := $(TGTDIR)image

all: $(TARGET)

$(TARGET):
	@mkdir -p build
	(cd kernel; make)

.PHONY: clean

clean: 
	rm -f build
