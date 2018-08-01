//
// Ejercicio 1
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>             // exit()
#include <unistd.h>             // sleep()

void *hilo(void *);

static pthread_t *hilos;

static int count = 0;

int main(int argc, char *argv[])
{
    // guardara el valor de retorno del hilo
    int retorno = 0;
    int n;
    int i;

    if (argc < 3) {
        fprintf(stderr, "Uso: %s NRO_HILOS CONTADOR\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    n = atoi(argv[1]);

    if (n <= 0) {
        fprintf(stderr, "NRO_HILOS debe ser mayor que cero.\n");
        exit(EXIT_FAILURE);
    }

    count = atoi(argv[2]);

    if (count <= 0) {
        fprintf(stderr, "CONTADOR debe ser mayor que cero.\n");
        exit(EXIT_FAILURE);
    }

    hilos = (pthread_t *) malloc(n * sizeof(pthread_t));

    for (i = 0; i < n; ++i) {
        // Crear el hilo, guardando su identificador en hilos y
        // pasandole i como parámetro.
        if (pthread_create()) {
            perror("pthread_create");
        }

    }

    // Espera por el resto de los hilos, y recupera el valor
    // de retorno de cada uno.
    for (i = 0; i < n; ++i) {
        pthread_join();
        printf("Hilo %d retorno %d\n", i, retorno);
    }

    free(hilos);

    pthread_exit(NULL);
}

void *hilo(void *param)
{
    int i;
    // intptr_t: Integer type capable of holding a value converted from a 
    // void pointer and then be converted back to that type with a value 
    // that compares equal to the original pointer.
    int id = (intptr_t) param;

    for (i = 0; i < count; i++) {
        printf("Hilo %d: Instancia %d\n", id, i);
        sleep(1);
    }

    pthread_exit((void *) (intptr_t) i);
}
