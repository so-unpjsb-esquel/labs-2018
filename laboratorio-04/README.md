# Laboratorio 4: Planificación

## Ejercicio 1
Completar el programa `ej1.c`, que crea _n_ hilos, cada uno de los cuales imprime un mensaje un determinado número de veces por la salida estándar.
* Ejecutar el programa múltiples veces con los mismos parámetros, ¿Varía el orden de ejecución de los hilos? ¿Por qué?

## Ejercicio 2
Consultar la sección [`sched`](http://man7.org/linux/man-pages/man7/sched.7.html) del manual y realizar una breve descripción de las políticas `SCHED_FIFO`, `SCHED_RR` y `SCHED_OTHER`.

## Ejercicio 3
El programa `ej3.c` crea un cierto número de hilos, y los planifica con la política `SCHED_FIFO` o `SCHED_OTHER`, según se le indique. Ejecutar el programa y describir los resultados de planificación de ambas políticas.

## Ejercicio 4: cambio de contexto en _xv6_
Agregar un par de invocaciones a `cprintf()` en el archivo `proc.c`, antes y despues de las llamadas a la función `swtch()`. Primero, en la funcion `scheduler()`, de esta forma:
```
cprintf("a");
swtch(&(c->scheduler), p->context);
cprintf("b");
```
Luego, en la función `sched()`, de la siguiente manera:
```
cprintf("c");
swtch(&p->context, mycpu()->scheduler);
cprintf("d");
```
Luego, compilar y ejecutar _xv6_. Responder:
* ¿Como es el patron de cuatro caracteres que aparece? ¿Por qué se da en ese orden?
* Sin embargo, los primeros caracteres que aparecen son `ac`, ¿Por qué?

Poner las respuestas en un archivo de texto en el directorio del Laboratorio.

## Ejercicio 5
Resolver los ejercicios sobre algoritmos de planificación que estan en el archivo `politicas_planificacion.pdf`.

---

¡Fin del Laboratorio 4!