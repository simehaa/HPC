CC := gcc
PROFILE := -pg

PROGRAMS = $(patsubst %.c,%.exe,$(wildcard *.c))
DEP = week5.h

.PHONY : clean

# all: $(PROGRAMS)

unroll_and_jam.exe : unroll_and_jam.c
	$(CC) $< -o $@ -lm

clean :
	rm -f *.o $(PROGRAMS)

print-%  : ; @echo $* = $($*)
