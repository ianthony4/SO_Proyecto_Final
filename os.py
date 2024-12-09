class SistemaOperativo:
    def __init__(self):
        self.ejecutando = False  # Estado muestra el estado 
        self.procesos = []       # Lista de los proceso

    def start(self):
        # Arranque
        self.ejecutando = True
        print("Sistema Operativo Iniciado.")
        while self.ejecutando:
            comando = input("Ingrese un comando ('iniciar' para añadir un proceso, 'salir' para detener): ")
            self.procesar_comando(comando)

    def procesar_comando(self, comando):
        #Aqui deberiamos procesar los comandos del usuario
        if comando == "iniciar":
            self.iniciar_proceso()
        elif comando == "salir":
            self.detener_sistema()
        else:
            print("Comando NO conocido.")

    def iniciar_proceso(self):
        # Aqui simulares la creacion de un nuevo proceso
        id_proceso = len(self.procesos) + 1
        self.procesos.append(f"Proceso {id_proceso}")
        print(f"Proceso {id_proceso} iniciado.")

    def detener_sistema(self):
        # Detenemos el sistema operativo
        self.ejecutando = False
        print("Sistema Operativo Detenido.")

# Instancia y arranque
sistema = SistemaOperativo()
sistema.start()

