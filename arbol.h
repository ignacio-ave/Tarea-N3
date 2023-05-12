#ifndef ARBOL_H
#define ARBOL_H

// Estructura de un nodo del árbol B+
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

// Funciones del árbol B+
ArbolB *crearArbolB(int orden);
void insertarEnArbolB(ArbolB *arbol, int clave);
void eliminarDeArbolB(ArbolB *arbol, int clave);
bool buscarEnArbolB(ArbolB *arbol, int clave);
void imprimirArbolB(ArbolB *arbol);

#endif  // ARBOL_H
