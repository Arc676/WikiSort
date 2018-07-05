CC=gcc
FLAGS=-c -std=c11

OUT=libwikisort.a

SDIR=src
ODIR=obj

OBJS=merge.o wikisort.o
_OBJS=$(patsubst %, $(ODIR)/%, $(OBJS))

ifdef DEBUG
	FLAGS+=-g -O0
endif

lib: makedir $(_OBJS)
	ar rcs $(OUT) $(_OBJS)

makedir:
	mkdir -p $(ODIR)

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $(FLAGS) -o $@ $<

clean:
	rm -f $(OUT) $(_OBJS)