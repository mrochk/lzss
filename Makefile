all: build

build:
	@mkdir -p bin
	@gcc -Wall main.c lzss.c -lm -o bin/bin

run: build
	@./bin/bin