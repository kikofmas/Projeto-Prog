#make file example

CC = gcc #compiler
CFLAGS = -Wall -ansi -pedantic -std=c99 -O3 
TARGET = proj #target file name

all:
	$(CC) $(CFLAGS) projeto_final.c -o $(TARGET) oraculo.o key.o mode.o intermedio.o files.o

clean:
	rm $(TARGET)
