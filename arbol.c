#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct NodoB {
    int *claves;
    struct NodoB **hijos;
    struct NodoB *hermanoDerecho;
    int numClaves;
    bool esHoja;
} NodoB;

// Estructura del árbol B+
typedef struct ArbolB {
    NodoB *raiz;
    int orden;
} ArbolB;

ArbolB *crearArbolB(int orden) {
    ArbolB *arbol = (ArbolB *)malloc(sizeof(ArbolB));
    arbol->raiz = NULL;
    arbol->orden = orden;
    return arbol;
}

void insertarEnArbolB(ArbolB *arbol, int clave) {

}

void eliminarDeArbolB(ArbolB *arbol, int clave) {

}
bool buscarEnArbolB(ArbolB *arbol, int clave) {

}


// Función auxiliar para imprimir un nodo y sus claves
void imprimirNodo(NodoB *nodo) {

}

// Función auxiliar para imprimir recursivamente el árbol B+
void imprimirRecursivo(NodoB *nodo) {

}

void imprimirArbolB(ArbolB *arbol) {

}
