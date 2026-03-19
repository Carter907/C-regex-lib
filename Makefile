CC = gcc
CD = gdb

PROG_NAME = app

SOURCES = main.c

VER = c23

BUILD_DIR = ./build
ASM_DIR = ./build/asm

CFLAGS = -std=$(VER) -g -Wall -Werror -Wconversion -fanalyzer -fsanitize=undefined,address,leak -fsanitize-trap=undefined
AFLAGS = -S -masm=intel

LIBS = 

run: build
	$(BUILD_DIR)/$(PROG_NAME)

vasm: asm
	vim -R $(ASM_DIR)/$(PROG_NAME).s

asm: $(SOURCES) 
	mkdir -p $(ASM_DIR)
	$(CC) -o $(PROG_NAME).s $(AFLAGS) $(SOURCES)
	mv $(PROG_NAME).s $(ASM_DIR) 

build: $(SOURCES)
	mkdir -p $(BUILD_DIR)
	$(CC) -o $(PROG_NAME) $(CFLAGS) $(LIBS) $(SOURCES)
	mv $(PROG_NAME) $(BUILD_DIR) 

clean:
	rm -rf $(BUILD_DIR)

debug: build
	$(CD) $(BUILD_DIR)/$(PROG_NAME)
