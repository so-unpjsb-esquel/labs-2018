# Laboratorio 8 - Administración de Memoria

## Preliminares
Leer el apunte de práctica sobre administración de memoria en _xv6_, y el Capítulo 2 "Page Tables" del libro de _xv6_, para los ejercicios 2 y 3.

## Ejercicio 1:
Realizar los ejercicios que se incluyen en el archivo `PracticaMemoria.pdf`.

## Ejercicio 2: Contador de páginas en _xv6_
Agregar a _xv6_ una llamada al sistema de nombre `pgcnt()` que retorne la cantidad de páginas en uso del proceso actual. El código de la llamada al sistema se encuentra en el archivo `sys_pgcnt.c`. El archivo `pgcnt.c` es un programa de usuario que invoca a esta llamada al sistema.

Modificar el programa `pgcnt.c` para acepte como argumento un número que indique la cantidad de páginas que tiene que reservar de memoria dinámicante. El programa debe imprimir primero cuantas páginas utiliza antes y despues de reservar más memoria. Por ejemplo, si se ejecuta pidiendo 5 páginas:
```
$ pgcnt 5
6
11
$
```
_Tip_: pueden usar las funciones `malloc()` o `sbrk()` para incrementar la memoria utilizada por el proceso.

### Entrega:
Copiar en el repositorio el archivo `pgcnt.c` modificado, con el código comentado explicando las modificaciones.

## Ejercicio 3: _Lazy allocation_ en _xv6_
Muchos programas reservan memoria que pueden no utilizar nunca, como por ejemplo, un arreglo de gran tamaño. Un sistema operativo como Windows o Linux puede retrasar la asignación de memoria a estas secciones hasta que sean requeridos para su lectura/escritura. Cuando un proceso quiere acceder a estas secciones de memoria, ocurre un _page fault_ (fallo de página), y el sistema operativo carga las páginas requeridas desde disco. Una estrategia basada en este comportamiento se denomina _lazy allocation_.

### Parte 1
En _xv6_ los procesos piden memoria al sistema por medio de la llamada a sistema `sbrk()`, implementada por la función `sys_sbrk()` en el archivo `sysproc.c`. 

Primero se eliminara la reserva de memoria que realiza `sys_sbrk()`, comentando la llamada a `growproc()`. De esta manera, sólo se incrementa la variable que indica tamaño del proceso (`proc->sz`) y se retorna el tamaño anterior, pero sin reservar memoria. 

Hecha esta modificación, compilar y ejecutar _xv6_ y ejecutar el comando `echo hola`.
- ¿Qué error aparece? ¿A qué tipo de error se refiere el número indicado por `trap`?

### Parte 2
Modificar el código en el archivo `trap.c`, para que ante un _page fault_, producido por un programa a nivel de usuario, realice la carga de la página correspondientes a la dirección de memoria virtual que causó el _page fault_. No se necesitan cubrir todos los casos posibles de error, debe bastar para ejecutar comando simples como `echo` o `ls`.
- Para verificar si ocurrió un _page fault_, comprobar en la función `trap()` si `tf->trapno` es igual a `T_PGFLT`.
- Consultar los argumentos a `cprintf()` para ver cómo identificar la dirección virtual.
- Usar código de la función `allocuvm()` en el archivo `vm.c`, que es la función que invoca `growproc()`.
- Usar `PGROUNDDOWN()` para obtener la dirección base de la página (marco).
- Será necesario invocar a `mappages()`, por lo que hay que eliminar la sentencia static de su declaración en el archivo `vm.c`, y agregar su prototipo en `trap.c`.

### Entrega
Copiar en el repositorio del Laboratorio el archivo `trap.c` modificado, y un archivo de texto donde se responda las preguntas de la Parte 1 del Ejercicio.

---

¡Fín del Laboratorio 8!