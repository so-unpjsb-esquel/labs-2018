//
// Ejercicio 4
// 

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>             // exit()
#include <unistd.h>             // sleep()

void *hilo(void *);

int main(int argc, char *argv[])
{
    pthread_t id;

    /*
     * Completar, usando pthread_create() para crear un hilo.
     */
    if (pthread_create()) {
        perror("pthread_create");
    }

    /*
     * Completar aquí la invocación a pthread_join() para esperar que el hilo finalice.
     */
    pthread_join();

    exit(EXIT_SUCCESS);
}

void *hilo(void *param)
{
    int i;

    for (i = 0; i < 5; i++) {
        printf("Hilo - Instancia %d\n", i);
        sleep(1);
    }

    return (void *) 0;
}
