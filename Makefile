all: build

build:
	@mkdir -p bin
	@gcc -Wall -Wextra -pedantic main.c lzss.c -o bin/bin

run: build
	@./bin/bin