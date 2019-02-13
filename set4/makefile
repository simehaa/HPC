CC := gcc
PROFILE := -pg

PROGRAMS = $(patsubst %.c,%.exe,$(wildcard *.c))

.PHONY : all clean

all: $(PROGRAMS)

bandwidth.exe : bandwidth.c
	$(CC) $< -o $@ -lm

matrix_multiplication.exe : matrix_multiplication.c
	$(CC) $< -o $@ 

clean :
	rm -f *.o $(PROGRAMS)

print-%  : ; @echo $* = $($*)
