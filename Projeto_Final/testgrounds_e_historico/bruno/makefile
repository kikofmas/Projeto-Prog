PROJECT_NAME=mastermind

CC=gcc
FLAGS=-c -W -Wall -ansi -pedantic -O3 -std=c99

# .c files
C_SOURCE=$(wildcard ./source/*.c)
# .h files
H_SOURCE=$(wildcard ./source/*.h)
# .o files
OBJ=$(subst .c,.o,$(subst source,objects,$(C_SOURCE)))

RM = rm -rf


#
# Compilation and linking
#
all: objFolder $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ oraculo.o -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./objects/%.o: ./source/%.c ./source/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(FLAGS) -o $@
	@ echo ' '

./objects/main.o: ./source/main.c $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p objects

clean:
	@ $(RM) ./objects/*.o $(PROJECT_NAME) *~
	@ rmdir objects

.PHONY: all clean
