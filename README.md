# Laboratorios SO
En este repositorio encontraran los Laboratorios para la cátedra Sistemas Operativos, ciclo lectivo 2018.

## Software de base
Para el desarrollo de los Laboratorios se utilizará Linux. Si no cuentan con una distribución ya instalada en sus computadoras, pueden utilizar VirtualBox, para crear una máquina virtual.

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

## Cómo compilar los ejercicios

Para compilar los ejercicios de los Laboratorios, vamos a emplear el programa `make`, que nos permite automatizar el proceso de compilación y evita que tengamos que escribir el comando completo del compilador. Por ejemplo, cuando en un Laboratorio se pide modificar el programa `ej1.c`, para compilarlo hay que ejecutar:
```
$ make ej1
gcc -o bin/ej1 ej1.c -Wall -Werror -g
$
```
Lo que hace `make` es buscar, en el directorio actual, un archivo de nombre `Makefile`, que contiene las reglas para el objetivo `ej1`, que es compilar el programa `ej1.c`. El binario ejecutable es puesto en un subdirectorio de nombre `bin`. Para ejecutarlo:
```
$ bin/ej1 1 2
3
$
```
Para compilar _todos_ los programas en el Laboratorio, se puede ejecutar `make` sin argumentos (o con el objetivo `all`):
```
$ make
gcc -o bin/ej1 ej1.c -Wall -Werror -g
gcc -o bin/ej2-4 ej2-4.c -Wall -Werror -g
gcc -o bin/ej2-8 ej2-8.c -Wall -Werror -g
gcc -o bin/ej2-12 ej2-12.c -Wall -Werror -g
gcc -o bin/ej2-13 ej2-13.c -Wall -Werror -g
gcc -o bin/ej3-26 ej3-26.c -Wall -Werror -g
gcc -o bin/ej3-53 ej3-53.c -Wall -Werror -g
$
```
`make` es lo suficientemente inteligente para no volver a compilar un programa si el código fuente del mismo no fue modificado. Por lo tanto, si se ejecutará nuevamente `make` nos indicaría que no hay nada para hacer.
```
$ make
make: No se hace nada para 'all'.
$
```

## Como subir los ejercicios al repositorio
```
git commit -a
```
```
git push origin master
```

## Sistema Operativo _xv6_
