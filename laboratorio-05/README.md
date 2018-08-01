# Laboratorio 5 - Sincronización

## Ejercicio 1
El programa `glob.c`, crea dos hilos que repetidamente incrementan la variable global `glob`, copiando primero su valor en una variable automática (local), incrementando el valor de dicha variable, y copiando luego el nuevo valor en `glob`. Cada hilo incrementa `glob` el número de veces indicado en la línea de comandos.
* Compilar y ejecutar el programa, probando valores hasta que se encuentre una condiciones de carrera.
* ¿Por qué ocurre esta situación de carrera? ¿Cómo se podría evitar?
* Evitar la condición de carrera mediante el uso de mutexes (`pthread_mutex_t`).
* Evitar la condición de carrera mediante un semáforo (`sem_t`) en lugar del mutex.

## Ejercicio 2
Completar los programas `sem_open.c`, `sem_wait.c`, `sem_post.c` y `sem_unlink.c`. Ejecutar el _script_ `test_sem.sh` para probar que los programas funcionan correctamente.

## Ejercicio 3
El programa `buf.c` implementa un ejemplo del problema del productor-consumidor, haciendo uso de un búfer limitado. El programa no es correcto, ya que no utiliza mecanismos de sincronización. Esto puede ocasionar problemas, por ejemplo una condición de carrera. Modificar el programa para sincronizar el acceso al recurso compartido (el _buffer_) por parte de los hilos productor y consumidor, empleando semáforos y mutexes.

## Ejercicio 4
El programa `philo.c`, implementa un ejemplo del problema de la _cena de los filósofos_. Durante la ejecución del programa puede ocurrir una condición de carrera y/o de interbloqueo. Modificarlo para evitar esta condición, mediante el uso de semáforos y mutexes.

## Ejercicio 5
Modificado de: https://pdos.csail.mit.edu/6.828/2017/homework/lock.html

En este ejercicio exploraremos la programación paralela, utilizando hilos, exclusión mutua y una tabla _hash_. Para lograr un paralelismo real, se debe ejecutar este programa en una computadora con dos o más núcleos. 

En primer lugar, compilar y ejecutar el programa `ph.c`:
```
$ make ph
$ ./ph 2
```
El número 2 especifica el número de hilos que realizaran operaciones _put_ y _get_ sobre una tabla _hash_. Cuando termine de ejecutar, el programa debe generar una salida similar a la siguiente:
```
0: put time = 2.871728
1: put time = 2.957073
1: get time = 12.731078
1: 1 keys missing
0: get time = 12.731874
0: 1 keys missing
completion time = 15.689165
```
Cada hilo ejecuta dos fases. En la primera, almacena claves en la tabla,
y en la segunda fase trata de recuperar dichas claves de la tabla. La salida del programa indica cuanto tiempo duro cada fase para cada hilo. La última linea ("_completion time_") indica el tiempo total de ejecución del programa. En la salida de ejemplo anterior, el programa ejecutó durante aproximadamente 16 segundos.

Por ejemplo, si ejecutaramos nuevamente el programa, pero con un único hilo:
```
$ ./a.out 1
0: put time = 5.350298
0: get time = 11.690395
0: 0 keys missing
completion time = 17.040894
```
Vemos que el tiempo total de ejecución es levemente mayor que para el caso de ejecución con dos hilos (~17s contra ~15.6s). Sin embargo, notar que al utilizar dos hilos se realizó el doble de trabajo en la fase _get_, lo que representa un mejora de casi 2x (¡nada mal!). En cambio, para la fase _put_ se logró una mejora mucho más pequeña, ya que entre ambos hilos guardaron el mismo número de claves en algo menos de la mitad de tiempo (~2.9s contra ~5.3s).

Independientemente de si al ejecutar el programa en sus computadoras logran un incremento de velocidad, o la magnitud del mismo, notarán que el programa no funciona correctamente. Al ejecutar el mismo utilizando dos hilos, algunas claves posiblemente no puedan ser recuperadas. En el ejemplo anterior, una de las claves se perdió ("_1 keys missing_").

Esto empeora cuando incrementamos el número de hilos:
```
2: put time = 1.516581
1: put time = 1.529754
0: put time = 1.816878
3: put time = 2.113230
2: get time = 15.635937
2: 21 keys missing
3: get time = 15.694796
3: 21 keys missing
1: get time = 15.714341
1: 21 keys missing
0: get time = 15.746386
0: 21 keys missing
completion time = 17.866878
```
Dos consideraciones:
- El tiempo total de ejecución es aproxidamente el mismo que para el caso de dos hilos. Sin embargo, se realizó casi el doble de operaciones _get_, lo que indica que se esta obteniendo una buena paralelización.
- Más claves se han perdido. Es posible, sin embargo, que en una ejecución particular se pierdan más o menos claves, o incluso que no se pierda ninguna. ¿Por qué? Identificar la secuencia de eventos que pueden llevar a que se pierda una clave en el caso de dos o más hilos.

Para evitar la pérdida de claves, es necesario emplear exclusión mutua, durante las operaciones _put_ y _get_. Las funciones a utilizar son:
```
pthread_mutex_t lock;     // declare a lock
pthread_mutex_init(&lock, NULL);   // initialize the lock
pthread_mutex_lock(&lock);  // acquire lock
pthread_mutex_unlock(&lock);  // release lock
```

Se pide:
1. Modificar el código del programa `ph.c` de manera que no se pierdan claves al utilizar dos o más hilos. ¿Es aún la versión de dos hilos más rápida que la versión con un único hilo? De no ser así, ¿por qué?
2. Modificar el código para que las operaciones _get_ puedan ejecutarse en paralelo. (Tip: ¿Es necesario utilizar exclusión mútua al realizar una operación _get_?)
3. Modificar el código para que algunas de las operaciones _put_ puedan ejecutar en paralelo.

## Ejercicio 6 (Opcional)
Un problema clásico de IPC es el problema del peluquero dormido. Una peluquería tiene *n* peluqueros, y *m* sillas donde los clientes esperan su turno. Si no hay clientes, los peluqueros duermen (se bloquean). Cuando arriba un cliente, alguno de los peluqueros se despierta, y realiza el corte de pelo. Si todos los peluqueros estuvieran todos ocupados, y hubiera sillas disponibles, el cliente se sienta a esperar su turno (es decir, se bloquea a la espera de su turno). Caso contrario, se retira. Implementar en `peluquero.c` un ejemplo de este problema. Emplear semáforos para manejar sincronización y mutexes para garantizar la exclusión mutua.

---

¡Fin del Laboratorio 5!