// Creado por Ignacio Astorga  12/05/2023
//
#include "task.h"
#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



PriorityQueue* create_priority_queue(int capacity){
    PriorityQueue* queue = (PriorityQueue*) malloc(sizeof(PriorityQueue));
    queue->capacity = capacity;
    queue->size = 0;
    queue->heap = (Task**) malloc(capacity * sizeof(Task*));
    return queue;

}
void enqueue(PriorityQueue* queue, Task* task){
    if(queue->size == queue->capacity){
        printf("Priority queue is full\n");
        return;
    }
    int index = queue->size;
    queue->heap[index] = task;
    queue->size++;
    while(index > 0){
        int parent_index = (index - 1) / 2;
        if(queue->heap[index]->priority > queue->heap[parent_index]->priority){
            Task* aux = queue->heap[index];
            queue->heap[index] = queue->heap[parent_index];
            queue->heap[parent_index] = aux;
            index = parent_index;
        }else{
            break;
        }
    }
}
Task* dequeue(PriorityQueue* queue){
    if(queue->size == 0){
        printf("Priority queue is empty\n");
        return NULL;
    }
    Task* task = queue->heap[0];
    queue->heap[0] = queue->heap[queue->size - 1];
    queue->size--;
    int index = 0;
    while(index < queue->size){
        int left_child_index = 2 * index + 1;
        int right_child_index = 2 * index + 2;
        if(left_child_index >= queue->size){
            break;
        }
        int max_child_index = left_child_index;
        if(right_child_index < queue->size){
            if(queue->heap[right_child_index]->priority > queue->heap[left_child_index]->priority){
                max_child_index = right_child_index;
            }
        }
        if(queue->heap[index]->priority < queue->heap[max_child_index]->priority){
            Task* aux = queue->heap[index];
            queue->heap[index] = queue->heap[max_child_index];
            queue->heap[max_child_index] = aux;
            index = max_child_index;
        }else{
            break;
        }
    }
    return task;
}
Task* peek(PriorityQueue* queue){
    if(queue->size == 0){
        printf("Priority queue is empty\n");
        return NULL;
    }
    return queue->heap[0];
}
void delete_priority_queue(PriorityQueue* queue){
    free(queue->heap);
    free(queue);
}