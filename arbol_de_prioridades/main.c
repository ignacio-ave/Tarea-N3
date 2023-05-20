#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "hashmap.h"
#include "stack.h"
#include <stdbool.h>
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
void mostrarTareas(Heap* heap, HashMap* map);
void eliminarPrecedente(HashMap* map, char* nombre);
void marcarTareaComoCompletada(Heap* heap, HashMap* map, char* nombre);

typedef struct Tarea Tarea;



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
        if(tarea2->numPrecedentes < 50) {
            tarea2->precedentes[tarea2->numPrecedentes++] = tarea1;
        } else {
            printf("Error: La tarea %s ya tiene el máximo número de precedentes (50).\n", nombreTarea2);
        }
    } else {
        if(pairTarea1 == NULL) {
            printf("Error: La tarea %s no se encuentra en el mapa.\n", nombreTarea1);
        }
        if(pairTarea2 == NULL) {
            printf("Error: La tarea %s no se encuentra en el mapa.\n", nombreTarea2);
        }
    }
}

// 3. Mostrar tareas por hacer: La aplicación muestra todas las tareas pendientes, ordenadas según su prioridad y teniendo en cuenta las relaciones de precedencia.
void eliminarTarea(Heap* heap, HashMap* map, char* nombre) {
    // Buscar tarea en el mapa
    Pair* pair = searchMap(map, nombre);
    if(pair == NULL) return;

    // Buscar tarea en el heap y eliminarla
    for(int i = 0; i < heap->size; i++) {
        Tarea* tarea = heap->heapArray[i].data;
        if(strcmp(tarea->nombre, nombre) == 0) {
            heap->heapArray[i] = heap->heapArray[heap->size - 1];
            heap->size--;
            break;
        }
    }

    // Eliminar tarea del mapa
    eraseMap(map, nombre);
}

void mostrarTareas(Heap* heap, HashMap* map) {
    printf("Tareas por hacer, ordenadas por prioridad y precedencia:\n");
    int numeroTarea = 1;

    // Crear una copia del heap
    Heap* heapCopia = createHeap();
    for(int i = 0; i < heap->size; i++) {
        heap_push(heapCopia, heap->heapArray[i].data, heap->heapArray[i].priority);
    }

    // Creamos un stack para las tareas
    Stack* stack = createStack(heap->size);

    // Mientras haya tareas en el heapCopia
    while(heapCopia->size > 0) {
        // Extraer la tarea con la prioridad más alta
        Tarea* tarea = heap_top(heapCopia);
        heap_pop(heapCopia);

        // Empuja la tarea al stack
        stack_push(stack, tarea);
    }

    // Mientras el stack no esté vacío
    while (!stack_isEmpty(stack)) {
        // Pop la tarea desde el stack
        Tarea* tarea = stack_top(stack);
        stack_pop(stack);

        // Imprimir tarea
        printf("%d. %s (Prioridad: %d)", numeroTarea++, tarea->nombre, tarea->prioridad);
        // Si la tarea tiene precedentes, imprimirlos
        if(tarea->numPrecedentes > 0) {
            printf(" - Precedente: ");
            for(int i = 0; i < tarea->numPrecedentes; i++) {
                printf("%s", tarea->precedentes[i]->nombre);
                if(i < tarea->numPrecedentes - 1) {
                    printf(", "); // Agrega una coma entre cada precedente, excepto el último
                }
            }
        }
        printf("\n");
    }

    // Liberar memoria del heap copia y el stack
    destroyHeap(heapCopia);
    destroyStack(stack);
}





// 4. Marcar tarea como completada (nombre): La usuaria ingresa el nombre de una tarea. La aplicación marca la tarea como completada y la elimina de la lista de tareas por hacer. Si la tarea tiene relaciones de precedencia, se debe colocar una advertencia: “¿estás seguro que desea eliminar la tarea?”
void eliminarPrecedente(HashMap* map, char* nombre) {
    Pair* pair = firstMap(map);
    while(pair != NULL) {
        Tarea* tarea = (Tarea*)pair->value;
        for(int i = 0; i < tarea->numPrecedentes; i++) {
            if(strcmp(tarea->precedentes[i]->nombre, nombre) == 0) {
                // Cambia el orden de los precedentes a la izquierda
                for(int j = i; j < tarea->numPrecedentes - 1; j++) {
                    tarea->precedentes[j] = tarea->precedentes[j+1];
                }
                tarea->numPrecedentes--;
                // Solo una posible ocurrencia
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

void ejemplotareas() {
    // Crear el heap y el hashmap
    Heap* heap = createHeap();
    HashMap* map = createMap(100);

    // Crear las tareas
    agregarTarea(heap, map, "TareaD", 1);
    agregarTarea(heap, map, "TareaA", 3);
    agregarTarea(heap, map, "TareaB", 2);
    agregarTarea(heap, map, "TareaC", 4);
    agregarTarea(heap, map, "TareaE", 5);

    // Establecer las precedencias
    establecerPrecedencia(map, "TareaA", "TareaB");
    establecerPrecedencia(map, "TareaB", "TareaC");
    establecerPrecedencia(map, "TareaD", "TareaE");

    // Mostrar las tareas
    mostrarTareas(heap, map);
    
}




int main() {
    Heap* heap = createHeap();
    HashMap* map = createMap(100);
    
    // Variables que necesitaremos
    char nombre[50];
    char tarea1[50];
    char tarea2[50];
    int opcion, prioridad;

    ejemplotareas();

    // Inicializar tareas previamente
    
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
        getchar(); 
        switch (opcion) {
            case 1:
                printf("Ingrese el nombre de la tarea: ");
                fgets(nombre, sizeof(nombre), stdin);
                nombre[strcspn(nombre, "\n")] = 0; 
                printf("Ingrese la prioridad de la tarea: ");
                scanf("%d", &prioridad);
                getchar(); 
                agregarTarea(heap, map, nombre, prioridad);
                break;
            case 2:
                mostrarTareas(heap, map);
                break;
            case 3:
                printf("Ingrese el nombre de la tarea 1: ");
                fgets(tarea1, sizeof(tarea1), stdin);
                tarea1[strcspn(tarea1, "\n")] = 0; 
                printf("Ingrese el nombre de la tarea 2: ");
                fgets(tarea2, sizeof(tarea2), stdin);
                tarea2[strcspn(tarea2, "\n")] = 0; 
                establecerPrecedencia(map, tarea1, tarea2);
                break;
            case 4:
                printf("Ingrese el nombre de la tarea: ");
                fgets(nombre, sizeof(nombre), stdin);
                nombre[strcspn(nombre, "\n")] = 0; 
                eliminarPrecedente(map, nombre);
                break;
            case 5:
                printf("Ingrese el nombre de la tarea a marcar como completada: ");
                fgets(nombre, sizeof(nombre), stdin);
                nombre[strcspn(nombre, "\n")] = 0; 
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
