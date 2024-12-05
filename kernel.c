void main() {
    volatile char *video_memory = (char *)0xb8000;

    // Escribe "HELLO" en la parte superior de la pantalla
    const char *message = "HELLO";
    for (int i = 0; message[i] != '\0'; i++) {
        video_memory[i * 2] = message[i];        // Caracter
        video_memory[i * 2 + 1] = 0x0F;         // Atributo (blanco brillante sobre negro)
    }

    while (1) {}  // Bucle infinito
}

void _start() {
    main();
    while (1) {}
}

