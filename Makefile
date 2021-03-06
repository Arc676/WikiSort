CC=gcc
FLAGS=-c -std=c11

OUT=libwikisort.a

SDIR=src
ODIR=obj

OBJS=wikisort.o merge.o bubble.o selection.o insertion.o quick.o shell.o \
	oddeven.o comb.o cocktail.o gnome.o stooge.o cycle.o slow.o bogo.o \
	heap.o intro.o tim.o radix.o counting.o bucket.o pigeonhole.o patience.o \
	cartesian.o tree.o splay.o pancake.o
_OBJS=$(patsubst %, $(ODIR)/%, $(OBJS))

ifdef DEBUG
	FLAGS+=-g -O0
endif

ifdef VISUALIZER
	FLAGS+=-D VISUALIZER
endif

ifdef _32BITMODE
	FLAGS+=-D _32BITMODE
endif

lib: makedir $(_OBJS)
	ar rcs $(OUT) $(_OBJS)

makedir:
	mkdir -p $(ODIR)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(FLAGS) -o $@ $<

clean:
	rm -f $(OUT) $(_OBJS)
