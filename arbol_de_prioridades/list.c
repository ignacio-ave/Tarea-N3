#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *local = (List*) malloc(sizeof(List));
  if (local == NULL) exit(EXIT_FAILURE);
  local->current = NULL;
  local->head = NULL;
  local->tail = NULL;
  return local;
}

void * firstList(List * list) {
  if (list->head == NULL) return NULL;
  list->current = list->head;
  return list->head->data;
}

void * nextList(List * list) {
  if (list->current == NULL || list->current->next == NULL) return NULL;
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if (list->tail == NULL) return NULL;
  list->current = list->tail;
  return list->current->data;
}

void * prevList(List * list) {
  if (list->current == NULL || list->current->prev == NULL) return NULL;
  list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
  Node *aux = createNode(data);
  aux->next = list->head;
  list->head = aux;
  if (list->tail == NULL)
      list->tail = aux;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
  if (!list->current) {
    pushFront(list, data);
    return;
  }
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if (list->current == NULL) return;
  Node *aux = createNode(data);
  if (list->current->next == NULL){
    list->current->next = aux;
    aux->prev = list->current;
    list->tail = aux;
  }
  else {
    aux->next = list->current->next;
    aux->prev = list->current;
    aux->next->prev = aux;
    list->current->next = aux;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node * aux = list->current->data;
  if (list->head == list->tail) {
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    }
  else if (list->current == list->head) {
    list->head = list->current->next;
    list->head->prev = NULL;
    list->current = list->head;
  }
  else if (list->current == list->tail) {
    list->tail = list->current->prev;
    list->tail->next = NULL;
    free(list->current);
    list->current = NULL;
  }
  else {
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
    Node *temp = list->current;
    list->current = list->current->next;
    free(temp);
  }
  return aux;
}



void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}