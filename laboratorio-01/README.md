# Laboratorio 1 - El lenguaje C

## Preliminares

### Software de base
Para realizar estos ejercicios, y los de los siguientes Laboratorios, se utilizará Linux. Si no cuentan con una distribución ya instalada en sus computadoras, pueden utilizar VirtualBox, para crear una máquina virtual.

Las herramientas de desarrollo que utilizaremos son:
- [VirtualBox](https://www.virtualbox.org/), para ejecutar Linux en una máquina virtual, si no lo tienen ya instalado en sus computadoras, o no quieren instalarlo nativamente.
- Compilador [GCC](https://gcc.gnu.org/).
- [GNU Make](https://www.gnu.org/software/make/).
- [Git](https://git-scm.com/), para el control de versiones.
- [QEMU](https://www.qemu.org/) para ejecutar el sistema operativo _xv6_.
- Editor de texto.

En general, cualquier distribución de Linux reciente servirá para la materia. La mayoría de las distribuciones actuales cuentan con el software anterior en sus repositorios, por lo que pueden instalarse de manera sencilla utilizando el administrados de paquetes correspondiente.

En el cursado de la cátedra no utilizaremos una IDE, únicamente un editor de texto a elección, y se automatizará la compilación de los ejercicios con Make.

Distribuciones de Linux recomendadas son:
- [Xubuntu](https://xubuntu.org/)
- [Ubuntu Desktop](https://www.ubuntu.com/download/desktop)
- [Fedora](https://getfedora.org/es/)

Si van instalar Linux en VirtualBox, y quieren utilizar un entorno gráfico, es recomendable utilizar XFCE, ya que requiere menos recursos que Gnome3, Unity o KDE. El mismo puede ser instalado fácilmente tanto en Ubuntu como en Fedora, o utilizar Xubuntu que lo tiene configurado como entorno gráfico por defecto.

Otra opción, es un distribución mínima con las herramientas necesarias, que se puede obtener en: https://people.westminstercollege.edu/faculty/ggagne/osc10e/vm/index.html

El objetivo de este primer Laboratorio es familiarizarse con las herramientas de desarrollo y repasar el uso del lenguaje C.

### Cómo compilar los ejercicios

Para compilar los ejercicios, vamos a emplear el programa `make`, que nos permite automatizar el proceso de compilación y evita que tengamos que escribir el comando completo del compilador. Por ejemplo, en el ejercicio 1 se pide modificar el programa `ej1.c`. Luego, para compilarlo hay que ejecutar:
```
$ make ej1
gcc ...
$
```
Lo que hace `make` es buscar, en el directorio actual, un archivo de nombre `Makefile`, que contiene las reglas para el objetivo `ej1`, que es compilar el programa `ej1.c`. El binario ejecutable es puesto en el subdirectorio `bin`. Para ejecutarlo:
```
$ bin/ej1 1 2
3
$
```
Para compilar _todos_ los programas en el Laboratorio, se puede ejecutar `make` sin argumentos (o con el objetivo `all`):
```
$ make
...
$
```
`make` es lo suficientemente inteligente para no volver a compilar un programa si el código fuente del mismo no fue modificado. Por lo tanto, si se ejecutará nuevamente `make` nos indicaría que no hay nada para hacer.
```
$ make
$ make ej1
$
```

### Como subir los ejercicios al repositorio
```
git commit -a
```
```
git pull origin master
```

## Ejercicio 1
Modificar el programa `ej1.c` para que realize la suma de un número arbitrario de números enteros, que son provistos desde la línea de comandos como argumentos. Por ejemplo:
```
$ sumatoria 1 2 3 5 8
19
```

## Ejercicio 2
Realizar los siguientes ejercicios del Capítulo 1 del libro K&R: 
- 1.4
- 1.8
- 1.12
- 1.13

## Ejercicio 3
Repasar los siguientes capitulos del libro K&R:
- 2.9 (Bitwise operators).
- 5.1 (Pointers and Addresses) a 5.5 (Character Pointers and Functions).
- 6.1 a 6.4 (pointers to structures).

Y realizar los siguientes ejercicios:
- 2.6
- 5.3

---

¡Fín del Laboratorio 1!
