TGTDIR := build/
TARGET := $(TGTDIR)image

.PHONY:

all:
	@echo Building kernel...
	@echo ==------------------------ == kernel == ----------------------------==
	@mkdir -p build
	@(cd kernel; make)
	@echo ==------------------------ == kernel == ----------------------------==

clean: 
	rm -rf build/
