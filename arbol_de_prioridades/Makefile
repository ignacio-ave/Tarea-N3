# Variables
CC=gcc
CFLAGS=-I. -Wall
DEPS = heap.h hashmap.h
OBJ = main.o heap.o hashmap.o

# Reglas
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) main