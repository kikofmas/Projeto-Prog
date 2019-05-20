#make file example

CC = gcc #compiler
CFLAGS = -Wall -ansi -pedantic -std=c99 -Wextra
TARGET = proj #target file name

all:
	$(CC) $(CFLAGS) projeto_final.c -o $(TARGET) oraculo.o key.o intermedio.o files.o mode.o

clean:
	rm $(TARGET)
