# Laboratorio 8 - Administración de Memoria

## Preliminares
Leer el Capítulo 2 "Page Tables" del apunte de _xv6_.

## Ejercicio 1: Contador de páginas en _xv6_
Agregar a _xv6_ una llamada al sistema de nombre `pgcnt()` que retorne la cantidad de páginas en uso del proceso actual. El código de la llamada al sistema se encuentra en el archivo `sys_pgcnt.c`. El archivo `pgcnt.c` es un programa de usuario que invoca a esta llamada al sistema.

Modificar la llamada al sistema `pgcnt()`, agregando un parámetro de tipo entero (`int`) que si es cero, hace que la función retorne el número de páginas utilizadas para el espacio de direcciones de usuario, y si es 1 retorna el número de páginas utilizadas por el _kernel_ del sistema operativo.

### Entrega:
Crear en el repositorio del Laboratorio una copia del archivo `sys_pgcnt.c`, agregando comentarios que expliquen su funcionamiento, y la modificación realizada para contar paginas del usuario o del _kernel_.

## Ejercicio 2: _Lazy allocation_ en _xv6_
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