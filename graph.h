#ifndef GRAPH_H
#define GRAPH_H

#include "list_node.h"

typedef struct {
    int num_vertices;
    ListNode** adj_lists;
        
} Graph;

Graph* create_graph(int num_vertices);
void add_edge(Graph* graph, int src, int dest);
void delete_graph(Graph* graph);
void display_graph(Graph* graph);

#endif // GRAPH_H
