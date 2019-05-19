#make file example

CC = gcc #compiler
CFLAGS = -Wall -ansi -pedantic -std=c99 -Wextra
TARGET = proj #target file name

all:
	$(CC) $(CFLAGS) projeto_final.c -o $(TARGET) oraculo/oraculo.o key/key.o intermedio/intermedio.o files/files.o

clean:
	rm $(TARGET)
