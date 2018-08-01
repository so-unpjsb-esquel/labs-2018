# Laboratorio 2 - Llamadas al Sistema

## Ejercicio 1
Completar el programa `hola.c`, para que imprima el mensaje `hola mundo` en la _salida estándar_. Compilar dos versiones, una utilizando el parámetro `-static` del compilador gcc, que enlaza estáticamente las librerías utilizadas, y otra versión sin utilizar este parámetro. Ejecutar ambos ejecutables utilizando el comando `strace`, para ver que llamadas al sistema utiliza el programa. Responder:
1. ¿Qué diferencias existen en la ejecución de ambas versiones, según lo que indica el comando `strace`?
2. Identificar las llamadas al sistema utilizadas por las funciones de biblioteca empleadas en el programa.
3. ¿Qué llamada al sistema se encarga de imprimir el mensaje en la _salida estándar_?

_Nota_: es posible que el comando `strace` no este instalado en el sistema. De ser así, utilizar el administrador de paquetes de la distribución para instalarlo. Por ejemplo, en Ubuntu el comando es `sudo apt install strace`.

## Ejercicio 2
Completar los programas `ej2-reader.c` y `ej2-writer.c`. El programa `ej2-reader.c` debe leer líneas desde la _entrada estándar_ y enviarlas al programa `ej2-writer.c` para que este las imprima a través de la _salida estándar_. La comunicación entre los dos procesos debe realizarse mediante una *tubería* (_pipe_), creada con la llamada al sistema [`mkfifo()`](http://man7.org/linux/man-pages/man3/mkfifo.3.html) en `ej2-reader.c`. En el programa `ej2-writer.c` utilizar la llamada al sistema [`open()`](http://man7.org/linux/man-pages/man2/open.2.html) para abrir la tubería. Emplear las llamadas al sistema [`read()`](http://man7.org/linux/man-pages/man2/read.2.html), para leer desde la _entrada estandar_, y [`write()`](http://man7.org/linux/man-pages/man2/write.2.html) para escribir en la _salida estándar_. El programa `ej2-reader.c` debe finalizar su ejecución al leer una línea en blanco (esto es, una línea que solo contenga el carácter `\n`).

## Ejercicio 3
En este ejercicio, se agregará una traza a _xv6_ que imprima un mensaje cada vez que se invoca una llamada al sistema. Este mensaje tiene que indicar el nombre de la llamada al sistema invocada, y el valor que la misma retorna. Para esto, se debe modificar la función `syscall()` en el archivo `syscall.c`. Una vez hecha la modificación, al iniciar _xv6_ se tendría que ver algo similar a:
```
xv6...
cpu1: starting
cpu0: starting
sys_fstat -> 0
sys_write -> -1
sys_unlink -> 0
sys_write -> 0
sys_getpid -> 1
...
```
_Bonus_: imprimir también los argumentos pasados a la llamada al sistema.

## Ejercicio 4
Este ejercicio consiste en agregar una nueva llamada al sistema a _xv6_. Esta llamada al sistema debe retornar al usuario la fecha UTC actual del sistema. Para facilitar la implementación, copiar el código de una llamada al sistema ya existente, como por ejemplo `uptime()`, y usarlo como base.

Para leer el reloj del sistema, usar la función auxiliar `cmostime()`, definida en el archivo `lapic.c`. Esta función requiere como parámetro un puntero a una estructura `struct rtcdate`, definida en el archivo `date.h`.

Para probar la nueva llamada al sistema, usar el archivo `date.c` como base para un programa que invoca la llamada al sistema e imprime por la salida estándar la fecha UTC. Se debe agregar `date.c` a la lista  `UPROGS` del `Makefile` de _xv6_ para que sea compilado como un programa de usuario.

---

¡Fin del Laboratorio 2!