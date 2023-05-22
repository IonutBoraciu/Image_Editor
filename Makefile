CC=gcc
CFLAGS=-Wall-Wextra -std=c99
build:
	gcc image_editor.c -o image_editor -lm
clean:
	rm -f image_editor
