all: build

build:
	@mkdir -p bin
	@gcc -Wall -Wextra -pedantic -std=c99 main.c lzss.c -o bin/lzss

test:
	@./bin/lzss -c input
	@./bin/lzss -d input.enc

fmt:
	@clang-format-11 -i main.c lzss.c lzss.h

clean:
	@rm -f *.enc *.dec 
