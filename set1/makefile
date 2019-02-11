limit:
	gcc limit.c -o limit

array:
	gcc array.c -o array

mxn_matrix:
	gcc mxn_matrix.c -o mxn_matrix

tensor:
	gcc tensor.c -o tensor

fileread:
	gcc fileread.c -o fileread -lm

smooth:
	gcc smooth.c -o smooth

all:
	make limit array mxn_matrix tensor fileread smooth

remove:
	ls | grep -v "\." | grep -v Makefile | xargs rm
