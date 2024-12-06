void proceso1() {
    char *video_memory = (char *)0xb8000;
    *video_memory = 'A';       // Letra 'A'
    *(video_memory + 1) = 0x07;
}

void proceso2() {
    char *video_memory = (char *)0xb8002;
    *video_memory = 'B';       // Letra 'B'
    *(video_memory + 1) = 0x07;
}

void proceso3() {
    char *video_memory = (char *)0xb8004;
    *video_memory = 'C';       // Letra 'C'
    *(video_memory + 1) = 0x07;
}

typedef void (*Proceso)();
Proceso procesos[] = {proceso1, proceso2, proceso3};
int num_procesos = 3;

void scheduler() {
    int i = 0;
    while (1) {
        procesos[i]();  // Ejecuta el proceso actual
        for (volatile int j = 0; j < 100000; j++) {} // Retraso
        i = (i + 1) % num_procesos;  // Alterna al siguiente proceso
    }
}

void main() {
    char *video_memory = (char *)0xb8000;
    *video_memory = 'K';  // Indica que el kernel ha iniciado
    while (1) {}
}

