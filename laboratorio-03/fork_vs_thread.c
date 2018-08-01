// Fork vs. Thread
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main_fork(void);
void main_thread(void);

static int count;

int main(int argc, char *argv[])
{
    int modo;

    if (argc < 3) {
        fprintf(stderr, "Uso: %s MODO COUNT\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    modo = atoi(argv[1]);
    count = atoi(argv[2]);

    if (count <= 0) {
        fprintf(stderr, "%s: count debe ser mayor que cero.\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (modo == 1) {
        printf("Testing with fork()...\n");
        main_fork();
    } else if (modo == 2) {
        printf("Testing with pthread_create()...\n");
        main_thread();
    } else {
        fprintf(stderr,
                "%s: modo invalido - usar 1 (fork) o 2 (threads)\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

//==========================================================================
//C Code for fork() creation test
//==========================================================================
void do_nothing_fork()
{
    int i;
    i = 0;
    i++;
}

void main_fork()
{
    int pid, j, status;

    for (j = 0; j < count; j++) {

  /*** error handling ***/
        if ((pid = fork()) < 0) {
            printf("fork failed with error code= %d\n", pid);
            exit(0);
        }

  /*** this is the child of the fork ***/
        else if (pid == 0) {
            do_nothing_fork();
            exit(0);
        }

  /*** this is the parent of the fork ***/
        else {
            waitpid(pid, &status, 0);
        }
    }
}

//==========================================================================
//C Code for pthread_create() test
//==========================================================================

void *do_nothing_thread(void *null)
{
    int i;
    i = 0;
    i++;
    pthread_exit(NULL);
}

void main_thread()
{
    int rc, j;
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (j = 0; j < count; j++) {
        rc = pthread_create(&tid, &attr, do_nothing_thread, NULL);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }

        /* Wait for the thread */
        rc = pthread_join(tid, NULL);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr);
    pthread_exit(NULL);

}
