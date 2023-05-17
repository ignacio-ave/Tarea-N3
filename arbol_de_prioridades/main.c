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
// Cabecera de funciones
void agregarTarea(Heap* heap, HashMap* map, char* nombre, int prioridad);
void establecerPrecedencia(HashMap* map, char* tarea1, char* tarea2);
void mostrarTareas(Heap* heap);
void eliminarPrecedente(HashMap* map, char* nombre);
void marcarTareaComoCompletada(Heap* heap, HashMap* map, char* nombre);


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
        // Elemento no encontrado en el heap
        return;
    }

    // Mover el último elemento al lugar del elemento a eliminar
    pq->heapArray[i] = pq->heapArray[pq->size - 1];
    pq->size--;

    // Reordenar el heap
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
            heap_eliminar(heap, tarea);  
        }
    }
}




// 5. Deshacer última acción: La aplicación deshace la última acción realizada por la usuaria, ya sea agregar/eliminar una tarea, establecer precedencia o marcar una tarea como completada. Si no hay acciones que deshacer, se debe mostrar un aviso.


// 6. Cargar datos de tareas desde un archivo de texto (nombre_archivo): La aplicación carga los datos de las tareas pendientes desde un archivo de texto indicado por la usuaria.



int main() {
    Heap* heap = createHeap();
    HashMap* map = createMap(100);
    
    // Variables que necesitaremos
    char nombre[50];
    char tarea1[50];
    char tarea2[50];
    int opcion, prioridad;


    // Inicializar tareas previamente
    
    agregarTarea(heap, map, "A", 1);
    agregarTarea(heap, map, "B", 3);
    establecerPrecedencia(map, "A", "B");
    agregarTarea(heap, map, "C", 2);
    establecerPrecedencia(map, "A", "C");
    agregarTarea(heap, map, "D", 4);
    establecerPrecedencia(map, "B", "D");
    establecerPrecedencia(map, "C", "D");
    agregarTarea(heap, map, "E", 5);
    establecerPrecedencia(map, "B", "E");
    agregarTarea(heap, map, "F", 1);
    agregarTarea(heap, map, "G", 2);
    establecerPrecedencia(map, "F", "G");
    agregarTarea(heap, map, "H", 3);
    establecerPrecedencia(map, "F", "H");
    agregarTarea(heap, map, "I", 5);
    establecerPrecedencia(map, "G", "I");
    establecerPrecedencia(map, "H", "I");
    agregarTarea(heap, map, "J", 4);
    establecerPrecedencia(map, "F", "J");
    agregarTarea(heap, map, "K", 1);
    agregarTarea(heap, map, "L", 2);
    establecerPrecedencia(map, "K", "L");
    agregarTarea(heap, map, "M", 3);
    establecerPrecedencia(map, "K", "M");
    agregarTarea(heap, map, "N", 4);
    establecerPrecedencia(map, "L", "N");
    establecerPrecedencia(map, "M", "N");
    agregarTarea(heap, map, "O", 5);
    establecerPrecedencia(map, "K", "O");
    agregarTarea(heap, map, "P", 1);
    agregarTarea(heap, map, "Q", 3);
    establecerPrecedencia(map, "P", "Q");
    agregarTarea(heap, map, "R", 2);
    establecerPrecedencia(map, "P", "R");
    agregarTarea(heap, map, "S", 5);
    establecerPrecedencia(map, "Q", "S");
    establecerPrecedencia(map, "R", "S");
    agregarTarea(heap, map, "T", 4);
    establecerPrecedencia(map, "P", "T");
    
    do {
        printf("\n╭──────────────────────────────────────────────────────────╮");
        printf("\n│                     MENU PRINCIPAL                       │");
        printf("\n├──────────────────────────────────────────────────────────┤");
        printf("\n│ 1. Agregar tarea                                         │");
        printf("\n│ 2. Mostrar tareas                                        │");
        printf("\n│ 3. Establecer precedencia entre dos tareas               │");
        printf("\n│ 4. Eliminar precedente de una tarea                      │");
        printf("\n│ 5. Marcar tarea como completada                          │");
        printf("\n│ 0. Salir                                                 │");
        printf("\n╰──────────────────────────────────────────────────────────╯");
        printf("\n\nIngrese una opción: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("Ingrese el nombre de la tarea: ");
                scanf("%s", nombre);
                printf("Ingrese la prioridad de la tarea: ");
                scanf("%d", &prioridad);
                agregarTarea(heap, map, nombre, prioridad);
                break;
            case 2:
                mostrarTareas(heap);
                break;
            case 3:
                printf("Ingrese el nombre de la tarea 1: ");
                scanf("%s", tarea1);
                printf("Ingrese el nombre de la tarea 2: ");
                scanf("%s", tarea2);
                establecerPrecedencia(map, tarea1, tarea2);
                break;
            case 4:
                printf("Ingrese el nombre de la tarea: ");
                scanf("%s", nombre);
                eliminarPrecedente(map, nombre);
                break;
            case 5:
                printf("Ingrese el nombre de la tarea a marcar como completada: ");
                scanf("%s", nombre);
                marcarTareaComoCompletada(heap, map, nombre);
                break;
            case 0:
                printf("Saliendo del programa...");
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
        }
    } while (opcion != 0);

    destroyHeap(heap);
    destroyMap(map);

    return 0;
}
