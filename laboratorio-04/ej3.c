#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sched.h>              // CPU_ZERO, CPU_SET
#include <unistd.h>

int *ar;
int pos = 0;

void print_sched_policy(pthread_t thread)
{
    int policy;
    struct sched_param param;

    pthread_getschedparam(thread, &policy, &param);

    printf("Scheduling policy: %s - priority: %d\n",
           (policy == SCHED_OTHER) ? "SCHED_OTHER" :
           (policy == SCHED_FIFO) ? "SCHED_FIFO" :
           (policy == SCHED_RR) ? "SCHED_RR" : "?", param.sched_priority);
}

void *BusyWork(void *t)
{
    long i;
    double result = 0.0;

    int r = (rand() % 100) * 1000;

    for (i = 0; i < r; i++) {
        result = result + sin(i) * tan(i);
    }

    ar[(intptr_t) t] = pos++;

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t *hilos;
    pthread_attr_t attr;
    int rc;
    long t;

    int num_hilos = 0;
    int modo;

    if (argc != 3) {
        fprintf(stderr,
                "Uso: %s NUM_HILOS SCHED_POLICY [0 (SCHED_OTHER) | 1 (SCHED_FIFO)]\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    num_hilos = atoi(argv[1]);
    modo = atoi(argv[2]);

    if (num_hilos <= 0) {
        fprintf(stderr, "NUM_HILOS debe ser mayor que cero.\n");
        exit(EXIT_FAILURE);
    }

    /* Allocate memory for threads results */
    ar = malloc(num_hilos * sizeof(int));
    hilos = malloc(num_hilos * sizeof(pthread_t));

    /* Initialize thread attribute */
    pthread_attr_init(&attr);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    if (modo == 0) {
        pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
    } else if (modo == 1) {
        pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    } else {
        printf("Invalid scheduling policy.\n");
        exit(EXIT_FAILURE);
    }

    /* Configure CPU set. */
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);          // Clear the CPU set
    CPU_SET(0, &cpuset);        // Only run on CPU 0

    /* Set the process' CPU affinity */
    sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpuset);

    struct sched_param sp;

    /* Set main thread scheduling to FIFO. */
    sp.sched_priority = 2;
    sched_setscheduler(getpid(), SCHED_FIFO, &sp);
    print_sched_policy(pthread_self());

    printf("Main: creating threads...\n");

    sp.sched_priority = modo;

    for (t = 0; t < num_hilos; t++) {
        pthread_attr_setschedparam(&attr, &sp);

        rc = pthread_create(&hilos[t], &attr, BusyWork, (void *) t);
        if (rc) {
            fprintf(stderr, "pthread_create(): %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    /* We're done with the attribute object, so we can destroy it */
    pthread_attr_destroy(&attr);

    /* Wait for all the threads to finish */
    for (t = 0; t < num_hilos; t++) {
        pthread_join(hilos[t], NULL);
    }

    /* Print thread execution order */
    for (t = 0; t < num_hilos; t++) {
        printf("Hilo %ld termino %d\n", t, ar[t]);
    }

    printf("Main: program completed. Exiting.\n");

    free(ar);
    free(hilos);

    pthread_exit(0);
}
