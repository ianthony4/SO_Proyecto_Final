void main() {
    char *video_memory = (char *)0xb8000;
    *video_memory = 'H';
    *(video_memory + 1) = 0x07;
    while (1) {}
}

