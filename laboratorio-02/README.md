# Laboratorio 2 - Llamadas al Sistema

## Preliminares
Leer el Capítulo 3, especialmente la seccion _Code: C trap handler_, del libro de referencia de _xv6_, para los ejercicios 3 y 4.

Este es el primer Laboratorio en que utilizaremos _xv6_. Este es un sistema operativo pequeño, de tipo Unix, que fue desarrollado con fines educativos. Lo ejecutaremos en una máquina virtual mediante QEMU, con el comando `make qemu` o `make qemu-nox`. Con el último comando, no se abre una ventana nueva que emula una monitor de PC, si no que utiliza la misma terminal desde la cual se ejecutó el comando.

Para instalar QEMU, utilizar el administrador de paquetes de la distribución de Linux que estén utilizando. Por ejemplo en Ubuntu:
```
$ sudo apt install qemu
```

### Clonar el repositorio de _xv6_
Para clonar el repositorio de _xv6_:
```
$ git clone git@github.com:so-unpjsb-esquel/xv6-2018-alumno.git
```
Donde `alumno` tienen que reemplazarlo por su nombre de usuario en GitHub. El comando va a decargar su copia de _xv6_ en el directorio _xv6-2018-alumno_ en el directorio donde ejecuten el comando.

Luego, para probar que el sistema operativo se compile y ejecute correctamente:
```
$ cd xv6-2018-alumno
$ make qemu
```

_Curiosidad_: Si tienen Windows y ejecutan Linux dentro de una máquina virtual en VirtualBox, y luego _xv6_ con QEMU dentro de ese Linux... es como un _Inception_ de VMs.

## Ejercicio 1
Compilar el programa `hola.c`, que imprime el mensaje `hola mundo` en la _salida estándar_. Ejecutar el ejecutable utilizando el comando `strace`, para ver que llamadas al sistema utiliza el programa. Responder:
1. Identificar las llamadas al sistema utilizadas por las funciones de biblioteca empleadas en el programa.
2. ¿Qué llamada al sistema se encarga de imprimir el mensaje en la _salida estándar_?

_Nota_: es posible que el comando `strace` no este instalado en el sistema. De ser así, utilizar el administrador de paquetes de la distribución para instalarlo. Por ejemplo, en Ubuntu el comando es `sudo apt install strace`.

## Ejercicio 2
Completar los programas `ej2-reader.c` y `ej2-writer.c`. El programa `ej2-reader.c` debe leer líneas desde la _entrada estándar_ y enviarlas al programa `ej2-writer.c` para que este las imprima a través de la _salida estándar_. La comunicación entre los dos procesos debe realizarse mediante una *tubería* (_pipe_), creada con la llamada al sistema [`mkfifo()`](http://man7.org/linux/man-pages/man3/mkfifo.3.html) en `ej2-reader.c`. En el programa `ej2-writer.c` utilizar la llamada al sistema [`open()`](http://man7.org/linux/man-pages/man2/open.2.html) para abrir la tubería. Emplear las llamadas al sistema [`read()`](http://man7.org/linux/man-pages/man2/read.2.html), para leer desde la _entrada estandar_, y [`write()`](http://man7.org/linux/man-pages/man2/write.2.html) para escribir en la _salida estándar_. El programa `ej2-reader.c` debe finalizar su ejecución al leer una línea en blanco (esto es, una línea que solo contenga el carácter `\n`).

## Ejercicio 3
En este ejercicio, se modificara el _kernel_ de _xv6_ para que imprima un mensaje cada vez que un programa invoca una llamada al sistema. En este mensaje se indicará el nombre de la llamada al sistema ejecutada, y el valor que la misma retorna.

Para esto, se debe modificar la función `syscall()` en el archivo `syscall.c`. Esta función es ejecutada por el sistema operativo cuando se detecta que una interrupción por software ha sido generada desde un proceso de usuario para requerir algún tipo servicio. En otras palabras, para poder ejecutar una llamada al sistema.

Una vez hecha la modificación, al compilar y ejecutar _xv6_ en QEMU se tendría que ver algo similar a esto:
```
xv6...
cpu1: starting
cpu0: starting
sys_fstat -> 0
sys_write -> -1
...
sys_write -> 1
sys_fork -> 2
sys_exec -> 0
sys_open -> 3
sys_close -> 0
$sys_write -> 1
 sys_write -> 1
```
Las últimas lineas muestran como el proceso `init` crea y ejecuta el programa `sh` (el interprete de comandos), y luego `sh` escribiendo el símbol `$` (el _prompt_ o símbolo de sistema).

### Entrega:
Agregar en el directorio del Laboratorio:
- Una copia del archivo `syscall.c` modificado (ejecutar `git add syscall.c` para agregarlo al _commit_).
- Un archivo de texto donde este el resultado de ejecutar el comando `echo hola`, y se explique brevemente para que se invocan las llamadas al sistema utilizadas.

## Ejercicio 4
Este ejercicio vamos a modificar nuevamente el _kernel_ de a _xv6_, para agregar una nueva llamada al sistema operativo que retorne al usuario la fecha UTC actual del sistema.

Para facilitar la implementación, utilizar como base el código fuente de una llamada al sistema ya existente, como por ejemplo `uptime()`.

Para leer el reloj del sistema y obtener la fecha UTC, hay que usar la función auxiliar `cmostime()`, implementada en el archivo `lapic.c`. Esta función requiere como parámetro un puntero a una estructura `struct rtcdate`, definida en el archivo `date.h`.

Para probar la nueva llamada al sistema, usar el archivo `date.c` como base para un programa que invoca la llamada al sistema e imprime por la salida estándar la fecha UTC. Se debe agregar `date.c` a la lista  `UPROGS` del `Makefile` de _xv6_ para que sea compilado como un programa de usuario.

### Entrega
Agregar en el directorio del Laboratorio un archivo de texto donde se explique brevemente las modificaciones realizadas en cada uno de los archivos de _xv6_ que hayan modificado. Recordar utilizar `git add` para que Git agregue este archivo en el _commit_.

---

¡Fin del Laboratorio 2!