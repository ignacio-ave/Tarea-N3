# Variables
CC = gcc
CFLAGS = -Wall -std=c11
OBJS = main.o  graph.o list_node.o priority_queue.o task.o

# Regla por defecto
all: program

# Reglas de compilación
main.o: main.c graph.h list_node.h priority_queue.h task.h
	$(CC) $(CFLAGS) -c main.c


graph.o: graph.c graph.h list_node.h task.h
	$(CC) $(CFLAGS) -c graph.c

list_node.o: list_node.c list_node.h task.h
	$(CC) $(CFLAGS) -c list_node.c

priority_queue.o: priority_queue.c priority_queue.h task.h
	$(CC) $(CFLAGS) -c priority_queue.c

task.o: task.c task.h
	$(CC) $(CFLAGS) -c task.c

# Regla de enlace
program: $(OBJS)
	$(CC) $(CFLAGS) -o program $(OBJS)

# Regla de limpieza
clean:
	rm -f $(OBJS) program
