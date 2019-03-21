TARGET = pagerank.exe
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -fopenmp -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -fopenmp -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
