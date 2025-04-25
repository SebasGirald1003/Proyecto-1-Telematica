

## Introducción

Este proyecto tiene como objetivo desarrollar un sistema de chat funcional utilizando sockets en C, aplicando el modelo cliente-servidor y comunicación en red mediante el protocolo TCP/IP. 
El servidor es capaz de gestionar múltiples clientes de forma concurrente usando hilos, mientras que los clientes pueden conectarse, enviar y recibir mensajes en tiempo real.
El desarrollo fue realizado por dos compañeros de forma colaborativa, combinando conocimientos, planificación y trabajo en equipo para alcanzar los objetivos del proyecto.

---

## Desarrollo

El sistema se compone de dos aplicaciones:

### Servidor

- Crea un socket TCP que escucha conexiones entrantes.
- Gestiona múltiples clientes usando `pthread`.
- Recibe los mensajes de cada cliente y los retransmite a todos los demás.
- Registra los eventos y mensajes en un archivo `chat.log`.
- Envía al cliente recién conectado los últimos 10 mensajes guardados en el log.

### Cliente

- Se conecta al servidor usando un socket TCP.
- Solicita al usuario ingresar un nombre de usuario.
- Crea un hilo para enviar mensajes y otro para recibirlos.
- Permite salir del chat escribiendo `exit`.

Ambos programas fueron desarrollados en C utilizando la API de sockets de Berkeley, ejecutados y probados en un entorno Linux sobre VirtualBox.

---

## Aspectos logrados

- Conexión de múltiples clientes simultáneamente.
- Comunicación bidireccional usando sockets TCP.
- Manejo de concurrencia con `pthread`.
- Registro de mensajes y eventos en `chat.log`.
- Envío de los últimos mensajes al conectarse un nuevo cliente.
- Compilación y ejecución en máquina virtual Linux.
- Interfaz de terminal funcional, clara y sencilla.

---

## Aspectos no logrados

- Reconexión automática de clientes tras caída del servidor.
- Uso de una base de datos para persistencia avanzada (se usó un log de texto).
- Interfaz gráfica (no requerida, pero podría ser una mejora futura).

---

## Conclusiones

Este proyecto permitió comprender en profundidad el funcionamiento de sockets TCP, el modelo cliente-servidor y el manejo de concurrencia en C. 
También reforzó habilidades prácticas como el uso de Git, compilación en terminal, gestión de logs, y trabajo colaborativo entre compañeros.

---

## Referencias

- https://www.youtube.com/watch?v=U28svzb1WUs
- https://www.geeksforgeeks.org/socket-programming-cc/
- https://man7.org/linux/man-pages/
- https://www.ibm.com/docs/es/aix/7.3?topic=subroutines-sockets
- https://chatgpt.com/
