# Laboratorio 7 - E/S

## Ejercicio 1: Archivos y E/S de disco

### Preliminares
Leer las funciones `readi()`, `writei()`, `fileread()`, `filewrite()`, `create()` y `dirlink()`, y el código relacionado a estas funciones, en los archivos `fs.c`, `bio.c`, `ide.c`, `file.c` y `sysfile.c`.

Ignorar el archivo `log.c` (excepto para las modificaciones que se requiren para este ejercicio). Cuando se vea una invocación a `log_write()` en el código, suponer que dicha función invoca `bwrite()` con los mismos argumentos.

### Que modificar
Agregar una invocación a `cprintf()` en la funcion `log_write()` (en el archivo `log.c`), de manera que se imprima por pantalla un mensaje cada vez que un bloque es escrito en el disco:
```
cprintf("log_write sector %d\n", b->sector);
```
Volver a compilar y ejecutar _xv6_, y ejecutar estos comandos:
```
echo > a
echo x > a
rm a
mkdir d
```
Se debería ver una secuencia de mensajes "log write sector..." luego de ejecutar cada comando.

### Que hacer
Registar la lista de mensajes generados, indicando que función invoco a `bwrite()`, y que tipo de bloque es el que se esta escribiendo. Por ejemplo, "bloque de i-nodos", "bloque de datos", etc.

_Tip_: una manera sencilla de obtener el nombre de la función que invoca a `bwrite()` es agregarlo como un argumento extra a la función `log_write()`, y modificando todas las invocaciones agregando el nombre de la función en cuestión.

## Ejercicio 2: Pantalla
El archivo `console.c` implementa la funcionalidad de E/S de la terminal. La entrada se realiza desde el teclado y/o desde el puerto serial (RS232), y la salida es tanto por la pantalla y el puerto serial.
La función `cgaputc()` escribe el carácter que recibe como parámetro en la memoria de video en modo texto, suponiendo un adaptador CGA. Utiliza los siguientes datos:
- `CRTPORT`, una macro con el valor `0x3D4`, que es la dirección de memoria del puerto de comandos del controlador de vídeo.
- La variable `*crt`, que es un puntero a la memoria de video en modo texto, mapeada en la dirección `0xB8000`. La memoria de vídeo es un arreglo de 4000 bytes que representa una grilla de 80 columnas y 25 filas, donde cada carácter se representa con 2 bytes. El primer byte indica el color de la fuente y fondo, mientras que el segundo byte es el código ASCII.
- La posición del cursor por hardware, que es almacenada por la controladora de vídeo en los registros _Cursor Location High Register_ y _Cursor Location Low Register_ (consultar archivo `cga.txt`).

La función `cgaputc()` funciona de la siguiente manera:
1. Obtiene la posición del cursor hardware, y lo almacena en la variable `pos`.
2. Si el carácter es imprimible, lo escribe en la memoria de vídeo en la posición correspondiente. Si es un `\n` o un `BACKSPACE` actualiza la variable `pos` para reflejar el cambio de la posición del cursor.
3. Comprueba que la nueva posición del cursor (`pos++`) este dentro de los límites de la pantalla.
4. Realiza el _scroll_ (desplazamiento) de la pantalla si corresponde.
5. Actualiza el cursor hardware con la nueva posición.

### Que hacer:
Para este ejercicio se pide:
- Modificar el archivo `console.c` para cambiar el color con que el que se imprimen los caracteres por pantalla. Probar también cambiar el color de fondo. Ver la página 34 de la sección Alphanumeric Modes en la documentación VGA (que lo hereda de CGA).
- _Opcional_: Mantener el cursor en dos variables `x` e `y`, de manera que no se requiera recuperar el cursor hardware, y sólo se deba actualizarlo.

### Referencias:
- La sección “Terminales” (página 235) del Capítulo 3 (Entrada/Salida) del libro “Sistemas Operativos - Diseño e Implementación” (Tanenbaum).

---

¡Fin del Laboratorio 7!
