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
// NO PODEMOS USAR SPRINTF
/*
void mostrar_detalles() {
    char *memoria_video = (char *)0xB8000;
    int offset = 0;

    for (int i = 0; i < MAX_PROCESOS; i++) {
        const char *estado_actual = tabla_procesos[i].estado;
        offset += sprintf(memoria_video + offset * 2,
            "ID: %d, Prioridad: %d, Estado: %s, Restante: %d\n",
            tabla_procesos[i].id, tabla_procesos[i].prioridad,
            estado_actual, tabla_procesos[i].tiempo_restante);
    }
}
*/

void mostrar_detalles() {
    char *memoria_video = (char *)0xB8000;
    int offset = 160;

    for (int i = 0; i < MAX_PROCESOS; i++) {
        memoria_video[offset++] = 'P';
        memoria_video[offset++] = 0x0F;
        memoria_video[offset++] = '0' + tabla_procesos[i].id;
        memoria_video[offset++] = 0x0F;

        memoria_video[offset++] = ' ';
        memoria_video[offset++] = 0x0F;
        for (int j = 0; tabla_procesos[i].estado[j] != '\0'; j++) {
            memoria_video[offset++] = tabla_procesos[i].estado[j];
            memoria_video[offset++] = 0x0F;
        }

        memoria_video[offset++] = ' ';
        memoria_video[offset++] = 0x0F;
        memoria_video[offset++] = 'T';
        memoria_video[offset++] = 0x0F;
        memoria_video[offset++] = ':';
        memoria_video[offset++] = 0x0F;
        memoria_video[offset++] = '0' + tabla_procesos[i].tiempo_restante;
        memoria_video[offset++] = 0x0F;
        
        offset = (offset / 160 + 1) * 160;
    }
}

void pausa_ejecucion() {
    for (int t = 0; t < 1000000; t++) asm("nop");
}

void planificador() {
    ordenar_por_prioridad(tabla_procesos, MAX_PROCESOS); 
    bool todos_terminados = false;

    while (!todos_terminados) {
        todos_terminados = true;

        for (int i = 0; i < MAX_PROCESOS; i++) {
            if (tabla_procesos[i].tiempo_restante > 0) {
                todos_terminados = false;

                
                __builtin_memcpy(tabla_procesos[i].estado, "ejecutando", 11);
                int tiempo_ejecutado = (tabla_procesos[i].tiempo_restante > QUANTUM) ? QUANTUM : tabla_procesos[i].tiempo_restante;
                tabla_procesos[i].tiempo_restante -= tiempo_ejecutado;

                
                mostrar_detalles();

                pausa_ejecucion();

                if (tabla_procesos[i].tiempo_restante == 0) {
                    __builtin_memcpy(tabla_procesos[i].estado, "terminado", 9);
                } else {
                    __builtin_memcpy(tabla_procesos[i].estado, "listo", 5);
                }
            }
        }
    }
}

void kernel_main(void) {
   
    planificador();

    // resultados
    char *memoria_video = (char *)0xB8000;
    const char *mensaje = "Prueba con RR acabo";
    for (int i = 0; mensaje[i] != '\0'; i++) {
        memoria_video[i * 2] = mensaje[i];
        memoria_video[i * 2 + 1] = 0x0F;
    }

    while (1);
}
