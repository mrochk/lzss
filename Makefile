all: build

build:
	@mkdir -p bin
	@gcc -Wall -Wextra -pedantic main.c lzss.c -o bin/lzss

test:
	@./bin/lzss -c input
	@./bin/lzss -d input.enc
