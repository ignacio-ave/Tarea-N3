
# Gestor de tareas
Este es un simple programa en C que permite manejar una lista de tareas. Las tareas pueden tener prioridades y relaciones de precedencia, lo que permite organizar de forma eficiente las actividades que deben llevarse a cabo.
## Compilación y Ejecución

1. Descarge y entre al archivo:

```{bash}
git clone https://github.com/tu_usuario/tu_repositorio.git
cd tu_repositorio 
```

2. Compile el archivo con el siguiente comando:

```{bash}
gcc -o gestorTareas main.c heap.c hashmap.c list.c
```

2.  Ejecute el programa con el comando:

```{bash}
	./gestorTareas
```

## Estructuras y algoritmos
El programa utiliza las siguientes estructuras de datos:

- `Tarea`: Una estructura que representa una tarea con campos como nombre, clave, prioridad, arreglo de tareas precedentes y cantidad de precedentes.

- `Heap`: Una estructura de montículo binario utilizada para mantener las tareas ordenadas por prioridad.

- `HashMap`: Una estructura de mapa hash utilizada para almacenar las tareas y permitir búsquedas eficientes.

- `List`: Una estructura de lista enlazada utilizada para almacenar las tareas que se mostrarán ordenadas por prioridad y considerando las relaciones de precedencia.

Los algoritmos principales utilizados en el programa son:

- `agregarTarea`: Crea una nueva instancia de la estructura Tarea, la llena con los datos proporcionados y la agrega tanto al montículo binario como al mapa hash.

- `establecerPrecedencia`: Busca las dos tareas en el mapa hash y añade la primera tarea a la lista de precedentes de la segunda tarea.

- `mostrarTareas`: Muestra todas las tareas pendientes ordenadas por prioridad y considerando las relaciones de precedencia. Utiliza funciones auxiliares como size, TareaslistaCapa, ordenarlista e imprimirlista para realizar la tarea de forma eficiente.

- `marcarTareaComoCompletada`: Marca una tarea como completada y la elimina de la lista de tareas por hacer, si la tarea no tiene precedentes. Si la tarea tiene relaciones de precedencia, se muestra una advertencia y se solicita confirmación antes de eliminarla.

- `eliminarPrecedente`: Elimina una relación de precedencia existente de una tarea. Recorre el mapa hash y los precedentes de cada tarea para encontrar y eliminar la relación.

- `heap_eliminar`: Elimina un elemento específico del montículo binario.

Estos algoritmos y estructuras de datos permiten una gestión eficiente de las tareas, considerando tanto las prioridades como las relaciones de precedencia entre ellas.

##  Funcionalidad
El programa permite realizar las siguientes tareas:

1.  **Agregar tarea:** Permite agregar una nueva tarea, proporcionando un nombre y una prioridad para la tarea.
    
2.  **Mostrar tareas:** Muestra todas las tareas pendientes, ordenadas según su prioridad y teniendo en cuenta las relaciones de precedencia.
    
3.  **Establecer precedencia entre dos tareas:** Permite establecer una relación de precedencia entre dos tareas existentes.
    
4.  **Eliminar tarea de las listas de precedentes:** Permite eliminar una tarea de las listas de precedentes.
    
5.  **Marcar tarea como completada:** Permite marcar una tarea como completada. Si la tarea tiene relaciones de precedencia, se mostrará una advertencia.
    
6.  **Salir:** Termina la ejecución del programa

## Problemas conocidos
1. El programa no verifica si las relaciones de precedencia entre las tareas crean un ciclo, lo que podría generar un bucle entre precedencias de tareas.

### 

## Coevaluación del aporte individual
| Integrante | Participación | Responsabilidad | Comunicación | Calidad del trabajo | Trabajo en equipo | Pje Total |
|------------|--------------|----------------|--------------|------------------|------------------|------------------|
| Ignacio    | 20           | 20             |  20          | 20               | 20               | 100               |
