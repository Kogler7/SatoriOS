SECNME := drivers
TGTDIR := ../../build/
INCDIR := ../../include
SUBDIR := $(TGTDIR)$(SECNME)/
TARGET := $(TGTDIR)$(SECNME).o
SOURCE := $(wildcard *.c)
OBJECTS := $(patsubst %.c, $(SUBDIR)%.o, $(SOURCE))
CFLAGS += -I../../include

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo Linking $(TARGET)
	$(ECHOPRE)$(LD) -r -o $(TARGET) $(OBJECTS)

$(SUBDIR)%.o : %.c
	@echo Compiling $<
	$(ECHOPRE)$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean: 
	rm -rf $(TARGET) $(SUBDIR)
