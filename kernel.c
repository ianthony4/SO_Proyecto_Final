#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_PROCESSES 3
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
