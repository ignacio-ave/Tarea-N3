
#include "graph.h"
#include "list_node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Graph* create_graph(int num_vertices);
void delete_graph(Graph* graph);
void display_graph(Graph* graph);


Graph *create_graph(int num_vertices){
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adj_lists = (ListNode**) malloc(num_vertices * sizeof(ListNode*));
    for(int i = 0; i < num_vertices; i++){
        graph->adj_lists[i] = NULL;
    }
    return graph;
}
/*
Graph* create_graph(int num_tasks){
    Graph* graph = malloc(sizeof(Graph));
    graph->num_vertices = num_tasks;
    graph->adj_lists = malloc(num_tasks * sizeof(ListNode*));
    for(int i = 0; i < num_tasks; i++){
        graph->adj_lists[i] = NULL;
    }
    return graph;

}
*/






void delete_graph(Graph* graph){
    for(int i = 0; i < graph->num_vertices; i++){
        ListNode* current = graph->adj_lists[i];
        while(current != NULL){
            ListNode* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->adj_lists);
    free(graph);

}
void display_graph(Graph* graph){  
    for(int i = 0; i < graph->num_vertices; i++){
        ListNode* current = graph->adj_lists[i];
        printf("%d: ", i);
        while(current != NULL){
            printf("%s -> ", current->task->name);
            current = current->next;
        }
        printf("NULL\n");
    } 

}