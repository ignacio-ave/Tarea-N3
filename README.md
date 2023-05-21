
# Gestor de tareas
Este es un simple programa en C que permite manejar una lista de tareas. Las tareas pueden tener prioridades y relaciones de precedencia, lo que permite organizar de forma eficiente las actividades que deben llevarse a cabo.
## Compilación y Ejecución

  

1. Compile el archivo con el siguiente comando:

```{bash}
gcc -o gestorTareas main.c heap.c hashmap.c list.c
```
2.  Ejecute el programa con el comando:
 ```{bash}
	./gestorTareas
```

##  Funcionalidad
El programa permite realizar las siguientes tareas:

1.  **Agregar tarea:** Permite agregar una nueva tarea, proporcionando un nombre y una prioridad para la tarea.
    
2.  **Mostrar tareas:** Muestra todas las tareas pendientes, ordenadas según su prioridad y teniendo en cuenta las relaciones de precedencia.
    
3.  **Establecer precedencia entre dos tareas:** Permite establecer una relación de precedencia entre dos tareas existentes.
    
4.  **Eliminar precedente de una tarea:** Permite eliminar una relación de precedencia existente de una tarea.
    
5.  **Marcar tarea como completada:** Permite marcar una tarea como completada. Si la tarea tiene relaciones de precedencia, se mostrará una advertencia.
    
6.  **Salir:** Termina la ejecución del programa

## Problemas conocidos
1. El programa no verifica si las relaciones de precedencia entre las tareas crean un ciclo, lo que podría generar un bucle entre precedencias de tareas.

### 

## Coevaluación del aporte individual
| Integrante | Participación | Responsabilidad | Comunicación | Calidad del trabajo | Trabajo en equipo | Pje Total |
|------------|--------------|----------------|--------------|------------------|------------------|------------------|
| Ignacio    | 20           | 20             |  20          | 20               | 20               | 100               |
