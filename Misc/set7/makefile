CC := gcc
PROFILE := -pg

PROGRAMS = $(patsubst %.c,%.exe,$(wildcard *.c))
DEP = week5.h

.PHONY : clean

# all: $(PROGRAMS)

dotproduct_openmp.exe : dotproduct_openmp.c
	$(CC) $< -o $@ -lm

clean :
	rm -f *.o $(PROGRAMS)

print-%  : ; @echo $* = $($*)
