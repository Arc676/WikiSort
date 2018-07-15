# Usage: make FILE=sourceFile.c

# As long as the current working directory is /data relative to
# project root and the library has been compiled to the project
# root, this Makefile will compile the given source file and link
# the library automatically

ODIR=obj
SDIR=src
BDIR=bin

CC=gcc
FLAGS=-std=c11 -I ../src
LD=-l wikisort
FILE=
OBJ=$(patsubst %.c, $(ODIR)/%.o, $(FILE))
OUT=$(patsubst %.c, $(BDIR)/%.test, $(FILE))

# Set this variable (with proper -D syntax) to redefine macros for tests
MACROS=

ifdef DEBUG
	FLAGS+=-g -O0
endif

target: testprog.o $(OBJ)
	$(CC) $(FLAGS) $(MACROS) -L .. -o $(OUT) $(OBJ) $(ODIR)/testprog.o $(LD)

$(OBJ): $(SDIR)/$(FILE)
	$(CC) -c $(FLAGS) $(MACROS) -o $(OBJ) $(SDIR)/$(FILE)

testprog.o: $(SDIR)/testprog.c
	$(CC) -c $(FLAGS) $(MACROS) -o $(ODIR)/testprog.o $(SDIR)/testprog.c

clean:
	rm -f $(ODIR)/*.o $(BDIR)/*.test
