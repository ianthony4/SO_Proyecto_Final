#include "memoria.h"

#define TAM_MEMORIA 32
#define BLOQUES_POR_PROCESO 4

char memoria[TAM_MEMORIA];

void inicializar_memoria() {
    for (int i = 0; i < TAM_MEMORIA; i++) memoria[i] = '-';
}

void asignar_memoria(int id) {
    for (int i = 0; i < TAM_MEMORIA; i++) {
        if (memoria[i] == '-') {
            int j;
            for (j = 0; j < BLOQUES_POR_PROCESO && i + j < TAM_MEMORIA; j++) {
                if (memoria[i + j] != '-') break;
            }
            if (j == BLOQUES_POR_PROCESO) {
                for (int k = 0; k < BLOQUES_POR_PROCESO; k++) memoria[i + k] = '0' + id;
                return;
            }
        }
    }
}

void liberar_memoria(int id) {
    for (int i = 0; i < TAM_MEMORIA; i++) {
        if (memoria[i] == '0' + id) memoria[i] = '-';
    }
}

void mostrar_memoria() {
    char *memoria_video = (char *)0xB8000;
    int offset = 20 * 160;
    for (int i = 0; i < TAM_MEMORIA; i++) {
        memoria_video[offset++] = memoria[i];
        memoria_video[offset++] = 0x0F;
    }
}

