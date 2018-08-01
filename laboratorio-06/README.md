# Laboratorio 6 - Mensajes y Memoria Compartida

## Ejercicio 1
En este ejercicio usaremos el API de cola de mensajes de POSIX, que permite intercambiar datos entre procesos mediante mensajes. El manual [`mq_overview`](http://man7.org/linux/man-pages/man7/mq_overview.7.html) presenta una introducción general al API de colas de mensajes.

Las funciones del API que vamos a usar en este ejercicio son:
* [`mq_open()`](http://man7.org/linux/man-pages/man3/mq_open.3.html): crea una nueva cola de mensajes, o abre una ya existente.
* [`mq_send()`](http://man7.org/linux/man-pages/man3/mq_send.3.html): envía un mensaje a la cola de mensajes, con una prioridad dada.
* [`mq_receive()`](http://man7.org/linux/man-pages/man3/mq_send.3.html): recibe un mensaje.
* [`mq_close()`](http://man7.org/linux/man-pages/man3/mq_close.3.html): cierra el descriptor de una cola de mensajes (se trata como si fuera un descriptor de archivo).
* [`mq_unlink()`](http://man7.org/linux/man-pages/man3/mq_unlink.3.html): elimina una cola de mensajes.
* [`mq_getattr()`](http://man7.org/linux/man-pages/man3/mq_getattr.3.html): recupera los atributos de la cola de mensajes especificada.

Deberán completar los siguientes programas, que permiten enviar y recibir mensajes por medio de una cola de mensajes:
* `mq_open.c`: crea una cola de mensajes.
* `mq_send.c`: envia un mensaje a travez de la cola de mensajes especificada.
* `mq_receive.c`: lee el mensaje de mayor prioridad en la cola de mensajes indicada.
* `mq_attr.c`: muestra información acerca de la cola de mensajes especificada.
* `mq_unlink.c`: elimina la cola de mensajes indicada.

Una vez completados, deben poder crear colas de mensajes y envíar y recibir mensajes por medio de las mismas.

Responder también las siguientes preguntas:
1. Ejecutar el programa `mq_receive` cuando la cola de mensajes está vacía, ¿Qué sucede? ¿Por qué?
2.	Enviar varios mensajes, algunos con distinta prioridad y otros con la misma prioridad, usando el programa `mq_send`. Luego, recuperarlos con `mq_receive`. ¿En qué orden son recuperados de la cola de mensajes? ¿Cómo se ordenan los mensajes con la misma prioridad?

## Ejercicio 2
En este ejercicio usaremos el API de POSIX para crear y utilzar segmentos de memoria compartida. Mediante estos segmentos, múltiples procesos pueden intercambiar datos de una manera mucho más rapida que mediante el intercambio de mensajes. El manual [`shm_overview`](http://man7.org/linux/man-pages/man7/shm_overview.7.html) tiene una introducción al API de memoria compartida de POSIX.

Las principales funciones que vamos a usar en el ejercicio son:
* [`shm_open()`](http://man7.org/linux/man-pages/man3/shm_open.3.html): crea un nuevo objeto de memoria compartida, o abre uno ya existente.
* [`ftruncate()`](http://man7.org/linux/man-pages/man2/ftruncate.2.html): cambia ("trunca") el tamaño del segmento de memoria compartida (es la misma función que cambia el tamaño de un archivo).
* [`mmap()`](http://man7.org/linux/man-pages/man2/mmap.2.html): realiza el mapeo del segmento de memoria compartida indicado dentro del espacio de direcciones del proceso.
* [`shm_unlink()`](http://man7.org/linux/man-pages/man3/shm_unlink.3.html): elimina el segmento de memoria compartida indicado.
* [`close()`](http://man7.org/linux/man-pages/man2/close.2.html): cierra el descriptor de un segmento de memoria compartida.

Deben completar los siguientes programas haciendo uso del API de memoria compartida de POSIX, que utilizan memoria compartida para escribir y leer una serie de datos:
* `shm_create.c`: crea un segmento de memoria compartida.
* `shm_write.c`: escribe una serie de datos en el segmento de memoria compartida indicado.
* `shm_read.c`: lee los datos que se encuentren el segmento de memoria compartida especificado.
* `shm_unlink.c`: elimina el segmento de memoria compartida.

Responder también la siguiente pregunta:
1. ¿Cómo sabe `shm_read` cuanto datos puede leer del segmento de memoria compartida?

## Ejercicio 3
El programa `ej3.c` crea dos procesos hijos que se comunican por medio de una tubería. Uno de los procesos lee una línea desde la _entrada estándar_, y la envía por la tubería. El segundo proceso lee esta línea de la tubería y la imprime por la _salida estándar_. El programa termina cuando se ingresa una linea en blanco (osea, un `\n`). 

Modificar el programa de manera que ambos procesos se comuniquen con una cola de mensajes, en lugar de una tubería.

## Ejercicio 4
El programa `ej4.c` es identico al programa del ejercicio anterior. Modificarlo para que ambos procesos se comuniquen utilizando un segmento de memoria compartida en lugar de una tubería. Se requerirá sincronizar el acceso a la memoria compartida, por ejemplo utilizando un _mutex_.

---

¡Fin del Laboratorio 6!