#ifndef TASK_H
#define TASK_H


typedef struct Task {
    char* name;
    char* description;
    int priority;
    struct Task** precedents;  // Lista de tareas precedentes
    int num_precedents;       // Número de tareas precedentes
} Task;

Task* create_task(char* title, char* description, int priority, int num_precedents, Task** precedents);
void delete_task(Task* task);
void display_task(Task* task);


#endif // TASK_H
