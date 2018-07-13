# Usage: make FILE=sourceFile.c

# As long as the current working directory is /data relative to
# project root and the library has been compiled to the project
# root, this Makefile will compile the given source file and link
# the library automatically

CC=gcc
FLAGS=-std=c11 -I ../src
LD=-l wikisort
FILE=
OBJ=$(patsubst %.c, %.o, $(FILE))
OUT=$(patsubst %.c, %.test, $(FILE))

# Set this variable (with proper -D syntax) to redefine macros for tests
MACROS=

ifdef DEBUG
	FLAGS+=-g -O0
endif

target: testprog.o $(OBJ)
	$(CC) $(FLAGS) $(MACROS) -L .. -o $(OUT) $(OBJ) testprog.o $(LD)

$(OBJ): $(FILE)
	$(CC) -c $(FLAGS) $(MACROS) $(FILE)

testprog.o: testprog.c
	$(CC) -c $(FLAGS) $(MACROS) testprog.c
