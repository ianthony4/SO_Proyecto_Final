bits 16
org 0x7c00

; Mostrar un mensaje
mov ah, 0x0E
mov al, 'H'
int 0x10

; Saltar al kernel
jmp 0x1000

times 510-($-$$) db 0  ; Rellenar con ceros hasta 512 bytes
dw 0xAA55              ; Firma de arranque

