#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "hashmap.h"
#include "list.h"
#include <stdbool.h>


typedef struct Tarea Tarea;

typedef struct Tarea {
    char nombre[50];
    char clave[50];  
    int prioridad;
    struct Tarea *precedentes[50];
    int numPrecedentes;
} Tarea;





// Agregar tarea (nombre, prioridad): Creamos una nueva instancia de Tarea, la llenamos con el nombre y la prioridad proporcionados, y luego la agregamos al heap y al hashmap.
void agregarTarea(Heap* heap, HashMap* map, char* nombre, int prioridad) {
    Tarea* tarea = malloc(sizeof(Tarea));
    strcpy(tarea->nombre, nombre);
    strcpy(tarea->clave, nombre);  // Almacenar el nombre como clave
    tarea->prioridad = prioridad;
    tarea->numPrecedentes = 0;
    
    heap_push(heap, tarea, prioridad);
    insertMap(map, tarea->clave, tarea);  // Utilizar tarea->clave como clave
}


// Establecer precedencia entre tareas (tarea1, tarea2): Buscamos las dos tareas en el hashmap, añadimos la tarea1 a la lista de precedentes de la tarea2.
void establecerPrecedencia(HashMap* map, char* nombreTarea1, char* nombreTarea2) {
    // Eliminar el salto de línea de los nombres de las tareas
    nombreTarea1[strcspn(nombreTarea1, "\n")] = '\0';
    nombreTarea2[strcspn(nombreTarea2, "\n")] = '\0';

    Pair* pairTarea1 = searchMap(map, nombreTarea1);
    Pair* pairTarea2 = searchMap(map, nombreTarea2);

    if (pairTarea1 == NULL) {
        printf("Error: La tarea %s no se encuentra en el mapa.\n", nombreTarea1);
        return;
    }

    if (pairTarea2) {
        Tarea* tarea1 = (Tarea*)pairTarea1->value;
        Tarea* tarea2 = (Tarea*)pairTarea2->value;
        if (tarea2->numPrecedentes < 50) {
            tarea2->precedentes[tarea2->numPrecedentes++] = tarea1;
        } else {
            printf("Error: La tarea %s ya tiene el máximo número de precedentes (50).\n", nombreTarea2);
        }
    } else {
        printf("Error: La tarea %s no se encuentra en el mapa.\n", nombreTarea2);
    }
}


// Mostrar tareas por hacer: La aplicación muestra todas las tareas pendientes, ordenadas según su prioridad y teniendo en cuenta las relaciones de precedencia.

int size(List* list) {
    int count = 0;
    Node* current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}



List* TareaslistaCapa(HashMap* map, int n) {
    List* lista = createList();
    Pair* pair = firstMap(map);
    while(pair != NULL) {
        Tarea* tarea = (Tarea*)pair->value;
        if(tarea->numPrecedentes == n) {
            pushBack(lista, tarea);
        }
        pair = nextMap(map);
    }
    return lista;
}


List * ordenarlista(List* list){
    List* listOrdenada = createList();
    Node* current = list->head;
    while(current != NULL) {
        Node* min = current;
        Node* r = current->next;
        while(r) {
            Tarea* tareaMin = (Tarea*)min->data;
            Tarea* tareaR = (Tarea*)r->data;
            if(tareaR->prioridad < tareaMin->prioridad) {
                min = r;
            }
            r = r->next;
        }
        Tarea* tareaMin = (Tarea*)min->data;
        Tarea* nuevaTarea = malloc(sizeof(Tarea));
        // Asegúrate de copiar todos los campos de la tarea
        strncpy(nuevaTarea->nombre, tareaMin->nombre, sizeof(nuevaTarea->nombre));
        nuevaTarea->prioridad = tareaMin->prioridad;
        nuevaTarea->numPrecedentes = tareaMin->numPrecedentes;
        for (int i = 0; i < nuevaTarea->numPrecedentes; i++) {
            nuevaTarea->precedentes[i] = tareaMin->precedentes[i];
        }
        pushBack(listOrdenada, nuevaTarea);

        if (min == current) {
            current = current->next;
        }
        if (min->prev) {
            min->prev->next = min->next;
        }
        if (min->next) {
            min->next->prev = min->prev;
        }
        free(min);
    }
    return listOrdenada;
}

void imprimirlista(List* list){
    Node* current = list->head;
    while(current != NULL) {
        Tarea* tarea = (Tarea*)current->data;
        printf("Tarea: %s\n", tarea->nombre);
        printf("Prioridad: %d\n", tarea->prioridad);
        if (tarea->numPrecedentes > 0){
            printf("Tareas precedentes:\n");
            for (int i = 0; i < tarea->numPrecedentes; i++) {
                printf("- %s\n", tarea->precedentes[i]->nombre);
            }
        }
        printf("\n");
        current = current->next;
    }
}

int contarTareas(HashMap* map) {
    int count = 0;
    Pair* pair = firstMap(map);
    while(pair != NULL) {
        count++;
        pair = nextMap(map);
    }
    return count;
}

void mostrarTareas(HashMap* map) {
    int totalTareas = contarTareas(map);
    int tareasMostradas = 0;
    for(int i = 0; tareasMostradas < totalTareas; i++) {
        List* listaCapa = TareaslistaCapa(map, i);
        tareasMostradas += size(listaCapa);
        if(size(listaCapa) == 0) {
            continue;
        }
        List* listaOrdenada = ordenarlista(listaCapa);
        imprimirlista(listaOrdenada);
    }
}



// Marcar tarea como completada (nombre): La usuaria ingresa el nombre de una tarea. La aplicación marca la tarea como completada y la elimina de la lista de tareas por hacer. Si la tarea tiene relaciones de precedencia, se debe colocar una advertencia: “¿estás seguro que desea eliminar la tarea?”
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



int main() {
    Heap* heap = createHeap();
    HashMap* map = createMap(100);
    
    char nombre[50];
    char tarea1[50];
    char tarea2[50];
    int opcion, prioridad;

    //ejemplotareas();

    // Inicializar tareas previamente
    
    do {
        printf("\n╭──────────────────────────────────────────────────────────╮");
        printf("\n│                     MENU PRINCIPAL                       │");
        printf("\n├──────────────────────────────────────────────────────────┤");
        printf("\n│ 1. Agregar tarea                                         │");
        printf("\n│ 2. Mostrar tareas                                        │");
        printf("\n│ 3. Establecer precedencia entre dos tareas               │");
        printf("\n│ 4. Eliminar de los precedentes                           │");
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
                mostrarTareas( map);
                break;
            case 3:
                printf("Ingrese el nombre de la tarea que se agregará a la lista de tareas precedentes: ");
                fgets(tarea1, sizeof(tarea1), stdin);
                tarea1[strcspn(tarea1, "\n")] = 0; 
                printf("Ingrese el nombre de la tarea a la cual pertenece la lista: ");
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

    free(heap);
    free(map);

    return 0;
}
