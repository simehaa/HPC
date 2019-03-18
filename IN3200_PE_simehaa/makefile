CC := gcc
PROFILE := -pg

PROGRAMS = $(patsubst %.c,%.exe,$(wildcard *.c))
DEP = pagerank.h

.PHONY : clean

# all: $(PROGRAMS)

pagerank.exe : pagerank.c $(DEP)
	$(CC) $< -o $@ -lm

clean :
	rm -f *.o $(PROGRAMS)

print-%  : ; @echo $* = $($*)
