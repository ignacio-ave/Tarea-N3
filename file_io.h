#ifndef FILE_IO_H
#define FILE_IO_H

#include "task.h"
#include "graph.h"
#include "priority_queue.h"

void save_tasks_to_file(char* filename, PriorityQueue* queue);
PriorityQueue* load_tasks_from_file(char* filename);

#endif // FILE_IO_H
