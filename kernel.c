#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "memoria.h" // Para la memoria

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

void mostrar_detalles(int fila_actual, int id, const char *estado, int tiempo_restante) {
    char *memoria_video = (char *)0xB8000;
    int offset = fila_actual * 160;

    memoria_video[offset++] = 'P';
    memoria_video[offset++] = 0x0F;
    memoria_video[offset++] = '0' + id;
    memoria_video[offset++] = 0x0F;

    memoria_video[offset++] = ' ';
    memoria_video[offset++] = 0x0F;
    for (int i = 0; estado[i] != '\0'; i++) {
        memoria_video[offset++] = estado[i];
        memoria_video[offset++] = 0x0F;
    }

    memoria_video[offset++] = ' ';
    memoria_video[offset++] = 0x0F;
    memoria_video[offset++] = 'T';
    memoria_video[offset++] = 0x0F;
    memoria_video[offset++] = ':';
    memoria_video[offset++] = 0x0F;
    memoria_video[offset++] = '0' + tiempo_restante;
    memoria_video[offset++] = 0x0F;
}

        

void pausa_simulada(int tiempo) {
    for (int i = 0; i < tiempo; i++) {
        for (volatile int j = 0; j < 100000; j++) {
            __asm__ __volatile__("nop");
        }
    }
}
// Función strcmp: compara dos cadenas
int strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

/*void planificador() {
    inicializar_memoria(); // Inicializa la memoria simulada
    ordenar_por_prioridad(tabla_procesos, MAX_PROCESOS);
    bool todos_terminados = false;
    int fila_actual = 1; // Comenzamos en la segunda línea

    while (!todos_terminados) {
        todos_terminados = true;

        for (int i = 0; i < MAX_PROCESOS; i++) {
            if (tabla_procesos[i].tiempo_restante > 0) {
                todos_terminados = false;

                // Asignar memoria cuando el proceso comienza a ejecutarse
                if (strcmp(tabla_procesos[i].estado, "Listo") == 0) {
                    asignar_memoria(tabla_procesos[i].id);
                }

                // Cambiar estado a Ejecutando
                __builtin_memcpy(tabla_procesos[i].estado, "Ejecutando", 11);
                mostrar_detalles(fila_actual++, tabla_procesos[i].id, tabla_procesos[i].estado, tabla_procesos[i].tiempo_restante);

                // Mostrar mapa de memoria
                mostrar_memoria();
                pausa_simulada(3);

                // Reducir tiempo restante
                int tiempo_ejecutado = (tabla_procesos[i].tiempo_restante > QUANTUM) ? QUANTUM : tabla_procesos[i].tiempo_restante;
                tabla_procesos[i].tiempo_restante -= tiempo_ejecutado;

                // Actualizar estado
                if (tabla_procesos[i].tiempo_restante == 0) {
                    __builtin_memcpy(tabla_procesos[i].estado, "Terminado", 11);
                    liberar_memoria(tabla_procesos[i].id);
                } else {
                    __builtin_memcpy(tabla_procesos[i].estado, "Listo", 11);
                }

                // Mostrar estado actualizado y memoria
                mostrar_detalles(fila_actual++, tabla_procesos[i].id, tabla_procesos[i].estado, tabla_procesos[i].tiempo_restante);
                mostrar_memoria();
                pausa_simulada(3);
            }
        }
    }
}
*/

void planificador() {
    inicializar_memoria();
    mostrar_memoria();
    ordenar_por_prioridad(tabla_procesos, MAX_PROCESOS); 
    bool todos_terminados = false;
    int fila_actual = 1; // Comenzamos en la segunda línea (fila 1)

    while (!todos_terminados) {
        todos_terminados = true;

        for (int i = 0; i < MAX_PROCESOS; i++){
            if (tabla_procesos[i].tiempo_restante > 0) {
                todos_terminados = false;
		if (strcmp(tabla_procesos[i].estado, "Listo     ") == 0) {
                    asignar_memoria(tabla_procesos[i].id);
		    mostrar_memoria();
                }
		mostrar_memoria();
                __builtin_memcpy(tabla_procesos[i].estado, "Ejecutando", 11);
                mostrar_detalles(fila_actual++, tabla_procesos[i].id, tabla_procesos[i].estado, tabla_procesos[i].tiempo_restante);
		asignar_memoria(tabla_procesos[i].id); // 
		mostrar_memoria(); //
                int tiempo_ejecutado = (tabla_procesos[i].tiempo_restante > QUANTUM) ? QUANTUM : tabla_procesos[i].tiempo_restante;
                tabla_procesos[i].tiempo_restante -= tiempo_ejecutado;
                
		pausa_simulada(80000);

                if (tabla_procesos[i].tiempo_restante == 0) {
                    __builtin_memcpy(tabla_procesos[i].estado, "Terminado ", 11);
		    mostrar_memoria();
		    liberar_memoria(tabla_procesos[i].id);
		    mostrar_memoria();
                } else {
                    __builtin_memcpy(tabla_procesos[i].estado, "Listo     ", 11);
		    asignar_memoria(tabla_procesos[i].id);
		    mostrar_memoria();
                }

		mostrar_detalles(fila_actual++, tabla_procesos[i].id, tabla_procesos[i].estado, tabla_procesos[i].tiempo_restante);
		mostrar_memoria();
            }
        }
    }
}


void kernel_main(void) {
    inicializar_memoria();
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
