bits 16            ; Indica que estamos en modo real
org 0x7c00         ; Dirección donde se carga el bootloader

; -------------------
; Mensaje de depuración
; -------------------
mov ah, 0x0E       ; Servicio de impresión de caracteres de la BIOS
mov al, 'B'        ; Imprime la letra 'B' (indica que el bootloader funciona)
int 0x10

; -------------------
; Configurar segmentos
; -------------------
mov ax, 0x07C0     ; Base del bootloader en la RAM
mov ds, ax         ; Configurar segmento de datos
mov es, ax         ; Configurar segmento extra

; -------------------
; Leer el kernel desde el disco
; -------------------
mov ax, 0x1000     ; Dirección del segmento donde cargaremos el kernel
mov es, ax         ; Configuramos ES al segmento 0x1000
xor bx, bx         ; Offset en ES donde empezará el kernel (0x0000)
mov ah, 0x02       ; Servicio de lectura de disco de la BIOS
mov al, 1          ; Leer 1 sector
mov ch, 0          ; Cilindro 0
mov cl, 2          ; Sector 2 (el kernel empieza aquí)
mov dh, 0          ; Cabeza 0
int 0x13           ; Llama a la BIOS para leer el disco
jc disk_error      ; Si falla, saltar al manejo de error

; -------------------
; Transferir control al kernel
; -------------------
jmp 0x1000:0000    ; Salta al inicio del kernel (0x1000:0x0000)

; -------------------
; Manejo de errores
; -------------------
disk_error:
mov ah, 0x0E       ; Servicio de impresión de caracteres de la BIOS
mov al, 'E'        ; Imprime la letra 'E' (indica error al leer el disco)
int 0x10
jmp $

; -------------------
; Rellenar hasta 512 bytes
; -------------------
times 510-($-$$) db 0  ; Rellena con ceros hasta que el tamaño sea 510 bytes
dw 0xAA55              ; Firma de arranque (necesaria para un bootloader válido)

