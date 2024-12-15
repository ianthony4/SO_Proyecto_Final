void kernel_main(void) {
    char *video_memory = (char *)0xB8000; // Dirección de video
    const char *msg = "Proyecto gamaOS v0.01";
    
    for (int i = 0; msg[i] != '\0'; i++) {
        video_memory[i * 2] = msg[i];      
        video_memory[i * 2 + 1] = 0x0F;    // Para el color
    }

    while (1); 
}

