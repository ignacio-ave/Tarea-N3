// Creado por Ignacio Astorga  12/05/2023
//

#include "task.h"
#include "list_node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Crea un nodo de lista
ListNode* create_list_node(Task* task){
    ListNode* node = (ListNode*) malloc(sizeof(ListNode));
    node->task = task;
    node->next = NULL;
    return node;
}

// Elimina un nodo de lista
void delete_list_node(ListNode* node){
    free(node);
}

