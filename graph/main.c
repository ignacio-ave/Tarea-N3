// Creado por Ignacio Astorga  12/05/2023
// //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "list_node.h"
#include "graph.h"
#include "priority_queue.h"





/*
// Definición de la estructura de una tarea
typedef struct Task {
    char* name;
    char* description;
    int priority;
    struct Task** precedents;  // Lista de tareas precedentes
    int num_precedents;       // Número de tareas precedentes
} Task;
// Defincion de la estructura priority queue

typedef struct {
    Task** tasks;
    int capacity;
    int size;
    PriorityQueue* head;
} PriorityQueue;

// Definición de la estructura de un nodo de lista

typedef struct ListNode {
    Task* task;
    struct ListNode* next;
    struct ListNode* prev;
    struct ListNode* head;
    struct ListNode* tail;

} ListNode;


// Definición de la estructura de un grafo
typedef struct {
    int num_vertices;
    ListNode** adj_lists;
} Graph;



*/





//1. Agregar tarea (nombre, prioridad): La usuaria ingresa el nombre de una tarea y su prioridad (un número entero). La aplicación agrega la tarea a la lista de tareas por hacer.
void add_task(Graph* graph, char* task_name, char* task_description, int task_priority){
    Task* task = create_task(task_name, task_description, task_priority, 0, NULL);
    ListNode* node = create_list_node(task);
    ListNode* current = graph->adj_lists[0];
    if(current == NULL){
        graph->adj_lists[0] = node;
        return;
    }
    while(current->next != NULL){
        current = current->next;
    }
    current->next = node;
}


//2. Establecer precedencia entre tareas (tarea1, tarea2): La usuaria ingresa los nombres de dos tareas existentes. La aplicación establece que la tarea1 debe realizarse antes que la tarea2.
void set_precedence(Graph* graph, char* task1_name, char* task2_name){
    int index1 = -1;
    int index2 = -1;
    for(int i = 0; i < graph->num_vertices; i++){
        if(strcmp(graph->adj_lists[i]->task->name, task1_name) == 0){
            index1 = i;
        }
        if(strcmp(graph->adj_lists[i]->task->name, task2_name) == 0){
            index2 = i;
        }
    }
    if(index1 == -1 || index2 == -1){
        printf("Error: no se encontró la tarea\n");
        return;
    }
    ListNode* node = graph->adj_lists[index2];
    node->next = graph->adj_lists[index1];
    graph->adj_lists[index2] = node;
}
//3. Mostrar tareas por hacer: La aplicación muestra todas las tareas pendientes, ordenadas según su prioridad y teniendo en cuenta las relaciones de precedencia.
void show_tasks(Graph* graph){
    PriorityQueue* queue = create_priority_queue(graph->num_vertices);
    for(int i = 0; i < graph->num_vertices; i++){
        ListNode* node = graph->adj_lists[i];
        Task* task = node->task;
        enqueue(queue, task);
    }
    while(queue->size > 0){
        Task* task = dequeue(queue);
        printf("%s (Prioridad: %d)\n", task->name, task->priority);
        if(task->num_precedents > 0){
            printf("Precedentes: ");
            for(int i = 0; i < task->num_precedents; i++){
                printf("%s ", task->precedents[i]->name);
            }
            printf("\n");
        }
    }
}

/*
Tareas por hacer, ordenadas por prioridad y precedencia:
1. TareaD (Prioridad: 1)
2. TareaA (Prioridad: 3)
3. TareaB (Prioridad: 2) - Precedente: TareaA
4. TareaC (Prioridad: 4) - Precedente: TareaB
5. TareaE (Prioridad: 5) - Precedente: TareaD

En este ejemplo de salida, las tareas se enumeran en el orden en que deben realizarse, teniendo en cuenta tanto su prioridad como las relaciones de precedencia. La tarea con la prioridad más alta (menor número) se muestra primero, seguida de las tareas que dependen de ella en función de las relaciones de precedencia establecidas. Cada tarea se muestra con su nombre, prioridad y, si corresponde, las tareas precedentes.

*/

//4. Marcar tarea como completada (nombre): La usuaria ingresa el nombre de una tarea. La aplicación marca la tarea como completada y la elimina de la lista de tareas por hacer. Si la tarea tiene relaciones de precedencia, se debe colocar una advertencia: “¿estás seguro que desea eliminar la tarea?”
void complete_task(Graph* graph, char* task_name){
    int index = -1;
    for(int i = 0; i < graph->num_vertices; i++){
        if(strcmp(graph->adj_lists[i]->task->name, task_name) == 0){
            index = i;
        }
    }
    if(index == -1){
        printf("Error: no se encontró la tarea\n");
        return;
    }
    ListNode* node = graph->adj_lists[index];
    if(node->next != NULL){
        printf("¿Estás seguro que deseas eliminar la tarea?\n");
        return;
    }
    graph->adj_lists[index] = NULL;
    free(node);
    graph->num_vertices--;
}
//5. Deshacer última acción: La aplicación deshace la última acción realizada por la usuaria, ya sea agregar/eliminar una tarea, establecer precedencia o marcar una tarea como completada. Si no hay acciones que deshacer, se debe mostrar un aviso.

void undo_last_action(Graph* graph){
    if(graph->num_vertices == 0){
        printf("No hay acciones que deshacer\n");
        return;
    }
    graph->num_vertices--;
    ListNode* node = graph->adj_lists[graph->num_vertices];
    graph->adj_lists[graph->num_vertices] = NULL;
    free(node);
}
// 6. Cargar datos de tareas desde un archivo de texto (nombre_archivo): La aplicación carga los datos de las tareas pendientes desde un archivo de texto indicado por la usuaria.
void load_tasks_from_file(Graph* graph, char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Error: no se pudo abrir el archivo\n");
        return;
    }
    char line[100];
    while(fgets(line, 100, file)){
        char* task_name = strtok(line, ",");
        char* task_description = strtok(NULL, ",");
        char* task_priority_str = strtok(NULL, ",");
        int task_priority = atoi(task_priority_str);
        add_task(graph, task_name, task_description, task_priority);
    }
    fclose(file);
}

int main() {
    // Crear un grafo vacío
    Graph* graph = create_graph(0);

    // Mostrar el menú de la aplicación
    while(1) {
        printf("\nMenu:\n");
        printf("1. Agregar tarea\n");
        printf("2. Establecer precedencia\n");
        printf("3. Mostrar tareas\n");
        printf("4. Completar tarea\n");
        printf("5. Deshacer última acción\n");
        printf("6. Cargar tareas desde archivo\n");
        printf("7. Salir\n");
        printf("Elige una opción: ");

        int choice;
        scanf("%d", &choice);
        char name[50], name2[50], filename[50];
        int priority;

        switch(choice) {
            case 1:
                printf("Nombre de la tarea: ");
                scanf("%s", name);
                printf("Descripción de la tarea: ");
                scanf("%s", name2);
                printf("Prioridad de la tarea: ");
                scanf("%d", &priority);
                add_task(graph, name, name2, priority);
                break;
            case 2:
                printf("Nombre de la primera tarea: ");
                scanf("%s", name);
                printf("Nombre de la segunda tarea: ");
                scanf("%s", name2);
                set_precedence(graph, name, name2);
                break;
            case 3:
                show_tasks(graph);
                break;
            case 4:
                printf("Nombre de la tarea: ");
                scanf("%s", name);
                complete_task(graph, name);
                break;
            case 5:
                undo_last_action(graph);
                break;
            case 6:
                printf("Nombre del archivo: ");
                scanf("%s", filename);
                load_tasks_from_file(graph, filename);
                break;
            case 7:
                printf("Saliendo...\n");
                free(graph);
                return 0;
            default:
                printf("Opción inválida. Por favor, intenta de nuevo.\n");
        }
    }

    return 0;
}
