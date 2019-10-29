CC := gcc
PROFILE := -pg

PROGRAMS = $(patsubst %.c,%.exe,$(wildcard *.c))

.PHONY : all clean

all: $(PROGRAMS)

division.exe : division.c
	$(CC) $< -o $@ -O0 $(PROFILE)

pow.exe : pow.c
	$(CC)  $< -o $@ -lm

clean :
	rm -f *.o $(PROGRAMS)

print-%  : ; @echo $* = $($*)
