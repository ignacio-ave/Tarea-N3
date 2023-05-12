#ifndef LIST_NODE_H
#define LIST_NODE_H

#include "task.h"


typedef struct ListNode {
    Task* task;
    struct ListNode* next;
} ListNode;

ListNode* create_list_node(Task* task);
void delete_list_node(ListNode* node);

#endif // LIST_NODE_H