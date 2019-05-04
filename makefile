all:
	gcc -Wall -Wpedantic -std=c99 *.c -g -o 3240Assignment0

test:
	./3240Assignment0 < test-input.txt
