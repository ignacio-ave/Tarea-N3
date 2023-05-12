#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "task.h"

typedef struct {
    Task** tasks;
    int capacity;
    int size;
} PriorityQueue;


PriorityQueue* create_priority_queue(int capacity);
void enqueue(PriorityQueue* queue, Task* task);
Task* dequeue(PriorityQueue* queue);
Task* peek(PriorityQueue* queue);
void delete_priority_queue(PriorityQueue* queue);

#endif // PRIORITY_QUEUE_H
