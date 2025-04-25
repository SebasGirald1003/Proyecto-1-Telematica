

## Introducción

Este proyecto tiene como objetivo desarrollar un sistema de chat funcional utilizando sockets en C, aplicando el modelo cliente-servidor y comunicación en red mediante el protocolo TCP/IP. 
El servidor es capaz de gestionar múltiples clientes de forma concurrente usando hilos, mientras que los clientes pueden conectarse, enviar y recibir mensajes en tiempo real.

---

## Desarrollo

El sistema se compone de dos aplicaciones:

### Servidor

- Crea un socket TCP que escucha conexiones entrantes.
- Gestiona múltiples clientes usando `pthread`.
- Recibe los mensajes de cada cliente y los retransmite a todos los demás.
- Registra los eventos y mensajes en un archivo `chat.log`.

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
- Compilación y ejecución en máquina virtual Linux.
- Interfaz de terminal funcional, clara y sencilla.

---

## Aspectos no logrados

- Uso de una base de datos para persistencia avanzada (se usó un log de texto).
- Interfaz gráfica (no requerida, pero podría ser una mejora futura).

---

## Conclusiones

## Conclusiones

El desarrollo de este proyecto permitió comprender de manera profunda el funcionamiento de los sockets en C bajo el modelo cliente-servidor, utilizando la API de sockets de Berkeley. Se exploraron conceptos clave como la creación de sockets TCP, el establecimiento de conexiones confiables, y el intercambio de datos entre múltiples procesos.
También se fortaleció el entendimiento sobre cómo implementar comunicación bidireccional en tiempo real y cómo gestionar múltiples conexiones de clientes de forma concurrente mediante el uso de hilos. Esta experiencia permitió aplicar de forma práctica los fundamentos de la programación en red y observar cómo interactúan los distintos componentes de un sistema distribuido.
En resumen, el proyecto ofreció una base sólida para comprender cómo se diseñan y construyen sistemas de comunicación en red en un entorno realista.


---

## Referencias

- https://www.youtube.com/watch?v=U28svzb1WUs
- https://www.geeksforgeeks.org/socket-programming-cc/
- https://www.ibm.com/docs/es/aix/7.3?topic=subroutines-sockets
- https://chatgpt.com/
