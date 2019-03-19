CC := gcc
PROFILE := -pg

PROGRAMS = $(patsubst %.c,%.exe,$(wildcard *.c))
DEP = PE_functions_simehaa.h

.PHONY : clean

# all: $(PROGRAMS)

pagerank.exe : PE_main_simehaa.c PE_functions_simehaa.c $(DEP)
	$(CC) $< -o $@ -lm

clean :
	rm -f *.o $(PROGRAMS)

print-%  : ; @echo $* = $($*)
