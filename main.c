/*
Objetivos
● Uso de TDAs en el lenguaje de programación C.
● Diseñar y proponer una solución eficiente para el problema planteado.

*/

/*
En esta actividad, se desea crear una aplicación para organizar tareas por hacer. 
La aplicación permitirá a los/las usuarios/as agregar tareas, establecer relaciones de precedencia entre ellas (una tarea debe realizarse antes que otra) y prioridades.
*/

/*

Ejemplo de formato de archivo de entrada/salida:

Nombre, Prioridad, TareasPrecedentes
TareaA, 3,
TareaB, 2, TareaA
TareaC, 4, TareaB
TareaD, 1,
TareaE, 5, TareaD
...

*/

/*
En este archivo, cada línea representa una tarea y los campos están separados por comas. 
El primer campo indica el nombre de la tarea, el segundo campo indica la prioridad de la tarea (un número entero) y el tercer campo indica las tareas precedentes, separadas por espacios.

*/

/*

Se propone el siguiente menú para la aplicación:


*/
# incluide <stdio.h>
# incluide <stdlib.h>
# incluide <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_TASKS 100

// Estructura para la tarea
typedef struct {
    char nombre[MAX_NAME_LENGTH];
    int prioridad;
    int completada;
    int num_precedentes;
    char precedentes[MAX_TASKS][MAX_NAME_LENGTH];
} Tarea;

// Estructura para el grafo
typedef struct {
    int num_tareas;
    Tarea tareas[MAX_TASKS];
} Grafo;

// Estructura para la pila de acciones
typedef struct {
    int top;
    char acciones[MAX_TASKS][MAX_NAME_LENGTH];
} Pila;




/*
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

*/



//1. Agregar tarea (nombre, prioridad): La usuaria ingresa el nombre de una tarea y su prioridad (un número entero). La aplicación agrega la tarea a la lista de tareas por hacer.

//2. Establecer precedencia entre tareas (tarea1, tarea2): La usuaria ingresa los nombres de dos tareas existentes. La aplicación establece que la tarea1 debe realizarse antes que la tarea2.

//3. Mostrar tareas por hacer: La aplicación muestra todas las tareas pendientes, ordenadas según su prioridad y teniendo en cuenta las relaciones de precedencia.

/*
Tareas por hacer, ordenadas por prioridad y precedencia:
1. TareaD (Prioridad: 1)
2. TareaA (Prioridad: 3)
3. TareaB (Prioridad: 2) - Precedente: TareaA
4. TareaC (Prioridad: 4) - Precedente: TareaB
5. TareaE (Prioridad: 5) - Precedente: TareaD

En este ejemplo de salida, las tareas se enumeran en el orden en que deben realizarse, teniendo en cuenta tanto su prioridad como las relaciones de precedencia. La tarea con la prioridad más alta (menor número) se muestra primero, seguida de las tareas que dependen de ella en función de las relaciones de precedencia establecidas. Cada tarea se muestra con su nombre, prioridad y, si corresponde, las tareas precedentes.

*/

//4. Marcar tarea como completada (nombre): La usuaria ingresa el nombre de una tarea. La aplicación marca la tarea como completada y la elimina de la lista de tareas por hacer. Si la tarea tiene relaciones de precedencia, se debe colocar una advertencia: “¿estás seguro que desea eliminar la tarea?”

//5. Deshacer última acción: La aplicación deshace la última acción realizada por la usuaria, ya sea agregar/eliminar una tarea, establecer precedencia o marcar una tarea como completada. Si no hay acciones que deshacer, se debe mostrar un aviso.

//
6. Cargar datos de tareas desde un archivo de texto (nombre_archivo): La aplicación carga los datos de las tareas pendientes desde un archivo de texto indicado por la usuaria.