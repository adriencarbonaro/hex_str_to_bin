#!make

OUT_DIR=dist
CFLAGS=-std=c99

.PHONY: build
build:
	@if [ ! -d "dist" ]; then mkdir $(OUT_DIR); fi
	gcc $(CFLAGS) -o $(OUT_DIR)/hex_str_to_bin main.c

.PHONY: clean
clean:
	rm -rf $(OUT_DIR)

.PHONY: all
all: clean build

