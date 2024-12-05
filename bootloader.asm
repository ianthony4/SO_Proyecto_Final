bits 16
org 0x7c00

mov ah, 0x0E   ; Modo de impresión en pantalla
mov al, 'H'    ; Caracter 'H'
int 0x10       ; Llamada a la BIOS para imprimir

cli            ; Desactiva interrupciones
hlt            ; Detiene la CPU

times 510-($-$$) db 0  ; Rellena hasta 512 bytes
dw 0xAA55              ; Firma de arranque
