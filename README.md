# Proyecto Final - Sistemas Operativos

### Inconveniente Actual

- Se esta utilizando actualmente QEMU (Por su gran capacidad comparado a VirtualBox)
- En una primera instancia se logro, imprimir (en Qemu) letras en consola, usando un archivo bootloader.asm el cual resulto de forma satisfactoria-
- Como segunda parte se planeo hacer nuestro kernel (kernel.c) donde ira por ahora la logica del schedule, que en este caso sera el Round Robin (Prueba)
- LOS PROBLEMA ocurren cuando tratamos de ejecutarlo para que se muestra en QEMU, el cual no imprime nada.
- Se intento añadirle el bootloader.asm a la compilacion con Kernel.c, a pesar de eso QEMU solo imprime solo lo implementado en el bootloader.asm, QEMU ignora a kernel.c
- Se hara mas investigaciones para resolver el problema
