#ifndef KERNEL_H
#define KERNEL_H

#include <stdbool.h>

// Definición de la estructura de un proceso
typedef struct {
    int id;                 
    int prioridad;          
    int tiempo_ejecucion;   
    int tiempo_restante;    
    char estado[12];        // "listo", "ejecutando", "terminado", "en espera"
    bool necesita_e_s;      // Indica si el proceso requiere E/S
} proceso;

// Declaración de constantes globales
#define MAX_PROCESOS 3
#define QUANTUM 3

// Declaración de funciones principales del kernel
void mostrar_detalles(int fila_actual, int id, const char *estado, int tiempo_restante);
void pausa_simulada(int tiempo);
void planificador();

#endif // KERNEL_H

