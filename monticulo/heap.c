#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


// Implementación de funciones auxiliares

void swap(heapElem* a, heapElem* b);
heapElem create_heapElem(void* data, int priority);
void reordenamiento_ascendente(heapElem* arreglo, int n);
void reordenamiento_descendente(Heap* pq, int parent);



void swap(heapElem* a, heapElem* b) {
   heapElem temp = *a;
   *a = *b;
   *b = temp;
}

heapElem create_heapElem(void* data, int priority){
   heapElem nuevo; // = (heapElem*)malloc(sizeof(heapElem));
   nuevo.data = data;
   nuevo.priority = priority;
   return nuevo;
}

void reordenamiento_ascendente(heapElem* arreglo, int n){
   
   int i = n-1;
   // Mientras el padre tenga al menos un hijo
   while ( i > 0 && arreglo[i].priority > arreglo[(i-1)/2].priority ){
      // Intercambia el padre con el hijo mayor
      swap(&arreglo[i], &arreglo[(i-1)/2]);
      // Actualiza el índice del padre
      i = (i-1)/2;
   }
}

void reordenamiento_descendente(Heap* pq, int parent){
   int maxChild;

   // Mientras el padre tenga al menos un hijo
   while (2 * parent + 1 < pq->size) {
      int leftChild = 2 * parent + 1;
      int rightChild = 2 * parent + 2;

      // Selecciona el hijo mayor
      if (rightChild < pq->size && pq->heapArray[rightChild].priority > pq->heapArray[leftChild].priority) {
         maxChild = rightChild;
      } else {
         maxChild = leftChild;
      }

      // Compara el padre con el hijo mayor
      if (pq->heapArray[parent].priority < pq->heapArray[maxChild].priority) {
         // Intercambia el padre con el hijo mayor
         swap(&pq->heapArray[parent], &pq->heapArray[maxChild]);

         // Actualiza el índice del padre
         parent = maxChild;
      } else {
         // Si el padre es mayor que sus hijos, termina el ciclo
         break;
      }
   }
}

////////////////////////////////////////////////////////////////////////////

// Implementación la función void* heap_top(Heap* pq).

void* heap_top(Heap* pq){
   // Si el montículo está vacío retorne NULL
   if ( pq-> size <= 0 ) return NULL; 
   
   // Retorne el dato con mayor prioridad del montículo
   return pq->heapArray[0].data;
}


// Implemente la función void heap_push(Heap* pq, void* data, int p). 

void heap_push(Heap* pq, void* data, int priority){
   // Si el arreglo está lleno aumente la capacidad al doble + 1 usando la función realloc así: arreglo = realloc(arreglo, nueva_capacidad)
   if ( pq-> size == pq->capac ){
      pq->capac = pq->capac*2 + 1;
      pq->heapArray = realloc(pq->heapArray, pq->capac*sizeof(heapElem));
   }

   heapElem nuevo = create_heapElem(data, priority);
   // Inserte el nuevo dato en la primera posición disponible del árbol (arreglo)
   pq->heapArray[pq->size] = nuevo;
   pq->size++;
   
   // Llame a la función para ordenar el arreglo
   reordenamiento_ascendente  (pq->heapArray, pq->size);
   
}


// Implemente la función void heap_pop(Heap* pq).

void heap_pop(Heap* pq) {
   if (pq->size == 0) {
      return;
   }

   swap(&pq->heapArray[0], &pq->heapArray[pq->size - 1]);
   pq->size--;

   int parent = 0;

   reordenamiento_descendente(pq, parent);
}



// Implemente la función Heap* createHeap(). 
Heap* createHeap(){
   Heap* nuevo = (Heap*)malloc(sizeof(Heap));
   nuevo->heapArray = (heapElem*)malloc(3*sizeof(heapElem));
   nuevo->size = 0;
   // La capacidad inicial del arreglo será 3
   nuevo->capac = 3;
   return nuevo;
}
