# Laboratorio 9 - Sistema de Archivos

## Ejercicio 1: Incrementar el tamaño máximo de un archivo en _xv6_
Con `BSIZE = 512`, _xv6_ está limitado a un máximo de 140 sectores, osea 71680 bytes. Este límite proviene del hecho que un _i-nodo_ en _xv6_ contiene 12 bloques de acceso directo, más un bloque de indirección sencilla (128 bloques adicionales). Luego, el máximo número de sectores en disco que puede ocupar un archivo es 12 + 128 = 140 sectores.

En este ejercicio se incrementará el tamaño máximo de un archivo en _xv6_, agregando soporte en la estructura de _i-nodo_ para un bloque de indirección doble.

### Preliminares
1. En el archivo `Makefile` de _xv6_ indicar que simule un solo CPU (`CPU := 1`), y agregar la opción -snapshot en la definición de `QEMUOPTS`. Estos cambios mejoran la performance de xv6 al generar archivos grandes, y utilizar solo una CPU facilita la evaluación.
2. Modificar `FSSIZE` en el archivo `defs.h` para que sea igual a 262144 sectores. Esto incrementa el tamaño de la imagen de disco a 128 Mb (262144 * 512 bytes).
3. Copiar el archivo `big.c` en el directorio de _xv6_, y agregarlo a la lista `UPROGS` en el `Makefile`. Este programa al ejecutarse crea un nuevo archivo, con un tamaño tal que ocupe un número determinado de sectores en el disco.
4. Compilar y ejecutar _xv6_. Luego, ejecutar el comando `big` con 200 sectores como parámetro. Debe retornar que sólo 140 sectores fueron escritos, ya que es el máximo tamaño posible del archivo.

### Qué tener en cuenta
El formato de un _i-nodo_ en disco es establecido por la estructura `struct dinode`, definida en el archivo `fs.h`. Prestar atención a `NDIRECT`, `NINDIRECT`, `MAXFILE` y el arreglo `addrs[]`.

La función `bmap()`, en el archivo `fs.c`, permite recuperar los datos de una archivo en el disco. Esta función es invocada tanto en la lectura como la escritura de un archivo. Para este último caso, `bmap()` reserva nuevos bloques según sea necesario.

Notar que `bmap()` maneja dos tipos de números de bloques. El argumento `bn` indica un número lógico de bloque, que es relativo al inicio del archivo. Sin embargo, los números de sectores almacenados en el arreglo `addrs[]` del _i-nodo_ corresponden con números de sectores en el disco, que pueden no ser consecutivos.

### Modificaciones a realizar
Modificar `bmap()` para que implemente el bloque de indirección doble, además del bloque de indirección sencilla y los bloques directos. 

No se debe modificar el tamaño del _i-nodo_, si no que, en cambio, se debe alterar para que tenga 11 bloques directos (en lugar de 12). De esta manera, el elemento 10 del arreglo `addrs[]` será el bloque indirecto sencillo, y el último elemento del arreglo será la dirección del nuevo bloque de indirección doble. 

Se de modificar también, en el archivo `mkfs.c`, la función `iappend()` de manera similar. Este programa genera la imagen de disco inicial para la máquina virtual (archivo `fs.img`), y crea los _i-nodos_ de los programas en disco.

### Tips:
- Liberar cada bloque luego de utilizarlo, utilizando la función `brelse()`.
- Sólo se deben reservar nuevos sectores en disco a medida que sean necesarios.
- Si el sistema de archivos se corrompe, eliminar el archivo `fs.img`.

### Entrega
Agregar al repositorio del Laboratorio una copia del archivo `fs.c` modificado.

---

¡Fín del Laboratorio 9!