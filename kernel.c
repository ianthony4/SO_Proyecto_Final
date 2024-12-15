#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_PROCESOS 3
#define QUANTUM 2

typedef struct {
    int id;                 
    int prioridad;          
    int tiempo_ejecucion;   
    int tiempo_restante;   
    char estado[12];        // listo, ejecutando, terminado
} proceso;

proceso tabla_procesos[MAX_PROCESOS] = {
    {1, 2, 5, 5, "listo"},
    {2, 1, 6, 6, "listo"},
    {3, 3, 4, 4, "listo"}
};

//Ordenamos los procesos por prioridad
void ordenar_por_prioridad(proceso *tabla, int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        for (int j = i + 1; j < tamano; j++) {
            if (tabla[j].prioridad < tabla[i].prioridad) {
                proceso temporal = tabla[i];
                tabla[i] = tabla[j];
                tabla[j] = temporal;
            }
        }
    }
}

void planificador() {
    ordenar_por_prioridad(tabla_procesos, MAX_PROCESOS); 
    bool todos_terminados = false;

    while (!todos_terminados) {
        todos_terminados = true;

        for (int i = 0; i < MAX_PROCESOS; i++) {
            if (tabla_procesos[i].tiempo_restante > 0) {
	 	//Todavia tenemos procesos
                todos_terminados = false; 

                // simulacion
                __builtin_memcpy(tabla_procesos[i].estado, "ejecutando", 11);
                int tiempo_ejecutado = (tabla_procesos[i].tiempo_restante > CUANTO_TIEMPO) ? CUANTO_TIEMPO : tabla_procesos[i].tiempo_restante;
                tabla_procesos[i].tiempo_restante -= tiempo_ejecutado;

                // simu tiempo de ejecucion (retardo)
                for (int t = 0; t < 1000000; t++); 

                // actualizacion dele stado actual
                if (tabla_procesos[i].tiempo_restante == 0) {
                    __builtin_memcpy(tabla_procesos[i].estado, "terminado", 9);
                } else {
                    __builtin_memcpy(tabla_procesos[i].estado, "listo", 5);
                }
            }
        }
    }
}
