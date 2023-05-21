#ifndef Heap_h
#define Heap_h

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;

void swap(heapElem* a, heapElem* b);
Heap* createHeap();
void* heap_top(Heap* pq);
void heap_push(Heap* pq, void* data, int priority);
void heap_pop(Heap* pq);
void destroyHeap(Heap* heap);

#endif /* HashMap_h */

