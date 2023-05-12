// Creado por Ignacio Astorga  12/05/2023
//

#include "file_io.h"
#include "priority_queue.h"
#include "task.h"
#include "list_node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void save_tasks_to_file(char* filename, PriorityQueue* queue){
    FILE* file = fopen(filename, "w");
    if(file == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }
    ListNode* current = queue->head;
    while(current != NULL){
        fprintf(file, "%s\n", current->task->name);
        current = current->next;
    }
    fclose(file);
}
PriorityQueue* load_tasks_from_file(char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Error al abrir el archivo\n");
        return NULL;
    }
    // PriorityQueue* create_priority_queue(int capacity);
    PriorityQueue* queue = create_priority_queue(25);
    char line[100];
    while(fgets(line, 100, file) != NULL){
        line[strlen(line) - 1] = '\0';
        //Task* create_task(char* title, char* description, int priority);
        Task* task = create_task(line, "", 0, 0, NULL);
        enqueue(queue, task);
    }
    fclose(file);
    return queue;
}