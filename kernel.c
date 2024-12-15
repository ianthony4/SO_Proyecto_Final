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

