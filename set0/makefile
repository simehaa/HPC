CC := GCC
FLAGS := -Wall
PROGRAMS := array.exe limit.exe fileread.exe mxn_matric.exe smooth.exe sort.exe tensor.exe

.PHONY : all clean

all: $(PROGRAMS)

array.exe : array.c
 				$(CC) $(FLAGS) array.c -o array.exe
limit.exe : limit.c
 				$(CC) $(FLAGS) limit.c -o limit.exe
fileread.exe : fileread.c
 				$(CC) $(FLAGS) fileread.c -o fileread.exe
mxn_matric.exe : mxn_matric.c
 				$(CC) $(FLAGS) mxn_matric.c -o mxn_matric.exe
smooth.exe : smooth.c
 				$(CC) $(FLAGS) smooth.c -o smooth.exe
sort.exe : sort.c
 				$(CC) $(FLAGS) sort.c -o sort.exe
tensor.exe : tensor.c
				$(CC) $(FLAGS) tensor.c -o tensor.exe

clean :
