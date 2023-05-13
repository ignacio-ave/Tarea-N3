#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "hashmap.h"

/*
struct HashMap {
    Pair **buckets;
    long size;     // cantidad de datos/pairs en la tabla
    long capacity; // capacidad de la tabla
    long current;  // indice del ultimo dato accedido
};
typedef struct Pair {
    char * key;
    void * value;
} Pair;

HashMap * createMap(long capacity);
void insertMap(HashMap * table, char * key, void * value);
void eraseMap(HashMap * table, char * key);
Pair * searchMap(HashMap * table, char * key);
Pair * firstMap(HashMap * table);
Pair * nextMap(HashMap * table);
void enlarge(HashMap * map);

---
typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
    heapElem* heapArray;
    int size;
    int capac;
} Heap;

Heap* createHeap();
void* heap_top(Heap* pq);
void heap_push(Heap* pq, void* data, int priority);
void heap_pop(Heap* pq);

*/

typedef struct Tarea {
    char nombre[50];
    int prioridad;
    struct Tarea *precedentes[50];  // Array de punteros a las tareas precedentes
    int numPrecedentes;  // Número de tareas precedentes
} Tarea;

// Agregar tarea (nombre, prioridad): Creamos una nueva instancia de Tarea, la llenamos con el nombre y la prioridad proporcionados, y luego la agregamos al heap y al hashmap.
void agregarTarea(Heap* heap, HashMap* map, char* nombre, int prioridad) {
    Tarea* tarea = malloc(sizeof(Tarea));
    strcpy(tarea->nombre, nombre);
    tarea->prioridad = prioridad;
    tarea->numPrecedentes = 0;
    
    heap_push(heap, tarea, prioridad);
    insertMap(map, nombre, tarea);
}
// Establecer precedencia entre tareas (tarea1, tarea2): Buscamos las dos tareas en el hashmap, añadimos la tarea1 a la lista de precedentes de la tarea2.
void establecerPrecedencia(HashMap* map, char* nombreTarea1, char* nombreTarea2) {
    Pair* pairTarea1 = searchMap(map, nombreTarea1);
    Pair* pairTarea2 = searchMap(map, nombreTarea2);
    
    if(pairTarea1 && pairTarea2) {
        Tarea* tarea1 = (Tarea*)pairTarea1->value;
        Tarea* tarea2 = (Tarea*)pairTarea2->value;
        tarea2->precedentes[tarea2->numPrecedentes++] = tarea1;
    }
}

void mostrarTareas(Heap* heap) {
    // Crear un heap auxiliar para no modificar el original
    Heap* heapAux = createHeap();
    while(heap->size > 0) {
        Tarea* tarea = (Tarea*)heap_top(heap);
        printf("%s (Prioridad: %d)", tarea->nombre, tarea->prioridad);
        for(int i = 0; i < tarea->numPrecedentes; i++) {
            printf(" - Precedente: %s", tarea->precedentes[i]->nombre);
        }
        printf("\n");
        heap_push(heapAux, heap_top(heap), tarea->prioridad);
        heap_pop(heap);
    }
    // Restaurar el heap original
    while(heapAux->size > 0) {
        heap_push(heap, heap_top(heapAux), ((Tarea*)heap_top(heapAux))->prioridad);
        heap_pop(heapAux);
    }
    free(heapAux);
}


int main() {
    Heap* heap = createHeap();
    HashMap* map = createMap(100);
    
    agregarTarea(heap, map, "Tarea 1", 1);
    agregarTarea(heap, map, "Tarea 2", 2);
    agregarTarea(heap, map, "Tarea 3", 3);
    agregarTarea(heap, map, "Tarea 4", 4);
    agregarTarea(heap, map, "Tarea 5", 5);
    agregarTarea(heap, map, "Tarea 6", 6);
    agregarTarea(heap, map, "Tarea 7", 7);
    agregarTarea(heap, map, "Tarea 8", 8);
    agregarTarea(heap, map, "Tarea 9", 9);
    agregarTarea(heap, map, "Tarea 10", 10);
    
    establecerPrecedencia(map, "Tarea 1", "Tarea 2");
    establecerPrecedencia(map, "Tarea 1", "Tarea 3");
    establecerPrecedencia(map, "Tarea 2", "Tarea 4");
    establecerPrecedencia(map, "Tarea 2", "Tarea 5");
    establecerPrecedencia(map, "Tarea 3", "Tarea 6");
    establecerPrecedencia(map, "Tarea 3", "Tarea 7");
    establecerPrecedencia(map, "Tarea 4", "Tarea 8");
    establecerPrecedencia(map, "Tarea 4", "Tarea 9");
    establecerPrecedencia(map, "Tarea 5", "Tarea 10");
    
    mostrarTareas(heap);
    
    return 0;
}