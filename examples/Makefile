CC=gcc
FLAGS=-std=c11 -I ../src -L ..
LD=-l wikisort
FILE=
OUT=$(patsubst %.c, %.ignore, $(FILE))

ifdef DEBUG
	FLAGS+=-g -O0
endif

ifdef VISUALIZER
	FLAGS+=-D VISUALIZER
endif

target:
	$(CC) $(FLAGS) -o $(OUT) $(FILE) $(LD)
