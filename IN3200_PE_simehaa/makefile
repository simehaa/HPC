CC := gcc
PROFILE := -pg

PROGRAMS = $(patsubst %.c,%.exe,$(wildcard *.c)) PE_main_simehaa.exe
DEP = PE_functions_simehaa.h

.PHONY : clean

# all: $(PROGRAMS)

PE_main_simehaa.exe : PE_main_simehaa.c $(DEP)
	$(CC) $< -o $@ -lm 

clean :
	rm -f *.o $(PROGRAMS)

print-%  : ; @echo $* = $($*)
