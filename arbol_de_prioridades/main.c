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

// 3. Mostrar tareas por hacer: La aplicación muestra todas las tareas pendientes, ordenadas según su prioridad y teniendo en cuenta las relaciones de precedencia.

void mostrarTareas(Heap* heap) {
    // Crear un heap auxiliar para no modificar el original
    Heap* heapAux = createHeap();
    while(heap->size > 0) {
        Tarea* tarea = (Tarea*)heap_top(heap);
        printf("%s (Prioridad: %d)", tarea->nombre, tarea->prioridad);

        printf(" - Precedentes: ");
        for(int i = 0; i < tarea->numPrecedentes; i++) {
            printf("%s ", tarea->precedentes[i]->nombre);
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

// 4. Marcar tarea como completada (nombre): La usuaria ingresa el nombre de una tarea. La aplicación marca la tarea como completada y la elimina de la lista de tareas por hacer. Si la tarea tiene relaciones de precedencia, se debe colocar una advertencia: “¿estás seguro que desea eliminar la tarea?”
void eliminarPrecedente(HashMap* map, char* nombre) {
    Pair* pair = firstMap(map);
    while(pair != NULL) {
        Tarea* tarea = (Tarea*)pair->value;
        for(int i = 0; i < tarea->numPrecedentes; i++) {
            if(strcmp(tarea->precedentes[i]->nombre, nombre) == 0) {
                // Shift all following tasks one position to the left
                for(int j = i; j < tarea->numPrecedentes - 1; j++) {
                    tarea->precedentes[j] = tarea->precedentes[j+1];
                }
                tarea->numPrecedentes--;
                // Only one occurrence possible, break loop
                break;
            }
        }
        pair = nextMap(map);
    }
}
void heap_eliminar(Heap* pq, void* data) {
    int i;
    for(i = 0; i < pq->size; i++) {
        if(pq->heapArray[i].data == data) {
            break;
        }
    }
    if(i == pq->size) {
        // Element not found, return without doing anything
        return;
    }

    // Move the last element to the position of the removed element
    pq->heapArray[i] = pq->heapArray[pq->size - 1];
    pq->size--;

    // Reorder the heap
    int parent = i;
    int child = 2 * parent + 1;
    while(child < pq->size) {
        if(child + 1 < pq->size && pq->heapArray[child].priority < pq->heapArray[child + 1].priority) {
            child++;
        }
        if(pq->heapArray[parent].priority >= pq->heapArray[child].priority) {
            break;
        }
        swap(&pq->heapArray[parent], &pq->heapArray[child]);
        parent = child;
        child = 2 * parent + 1;
    }
}



void marcarTareaComoCompletada(Heap* heap, HashMap* map, char* nombre) {
    Pair* pair = searchMap(map, nombre);
    if(pair) {
        Tarea* tarea = (Tarea*)pair->value;
        printf("¿Estás seguro que desea eliminar la tarea %s? (S/N): ", tarea->nombre);
        char respuesta;
        scanf(" %c", &respuesta);
        if(respuesta == 'S' || respuesta == 's') {
            eliminarPrecedente(map, nombre);
            eraseMap(map, nombre);
            heap_eliminar(heap, tarea);  // New line
        }
    }
}




// 5. Deshacer última acción: La aplicación deshace la última acción realizada por la usuaria, ya sea agregar/eliminar una tarea, establecer precedencia o marcar una tarea como completada. Si no hay acciones que deshacer, se debe mostrar un aviso.

// 6. Cargar datos de tareas desde un archivo de texto (nombre_archivo): La aplicación carga los datos de las tareas pendientes desde un archivo de texto indicado por la usuaria.

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
    establecerPrecedencia(map, "Tarea 6", "Tarea 10");
    mostrarTareas(heap);
    
    marcarTareaComoCompletada(heap, map, "Tarea 1");
    mostrarTareas(heap);

    return 0;
}