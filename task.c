// Creado por Ignacio Astorga  12/05/2023
//
#include "task.h"
#include "list_node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Task* create_task(char* title, char* description, int priority, int num_precedents, Task** precedents){
    Task* task = (Task*) malloc(sizeof(Task));
    task->name = (char*) malloc(strlen(title) + 1);
    strcpy(task->name, title);
    task->description = (char*) malloc(strlen(description) + 1);
    strcpy(task->description, description);
    task->priority = priority;
    task->num_precedents = num_precedents;
    task->precedents = precedents;
    return task;


}
void delete_task(Task* task){
    free(task->name);
    free(task->description);
    free(task);

}
void display_task(Task* task){
    printf("Title: %s\n", task->name);
    printf("Description: %s\n", task->description);
    printf("Priority: %d\n", task->priority);
    printf("Precedents: ");
    for(int i = 0; i < task->num_precedents; i++){
        printf("%s ", task->precedents[i]->name);
    }
    printf("\n");
}
