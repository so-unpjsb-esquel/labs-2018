// 
// Ejercicio 3 - Problema del búfer limitado modificado
// 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

#define BUFFER_SIZE 10 // tamaño del buffer

// Mueve el cursor a la linea x, columna y (ver codigos ANSI)
#define xy(x, y) printf("\033[%d;%dH", x, y)

// Borra desde el cursor hasta el fin de la linea
#define clear_eol(x) print(x, 7, "\033[K")

// Borra la pantalla
#define clear() printf("\033[H\033[J")

static void* writer(void*);
static void* reader(void*);
static void draw(void);
static void draw1(int, int, int);

int counter;
int buffer[BUFFER_SIZE]; // buffer de lectura y escritura (circular)

int out = 0; // indice que usa el lector 
int in = 0;  // indice que usa el productor

sem_t sem_writer;
sem_t sem_reader;
pthread_mutex_t mutex;

static void* writer(void *p) 
{
    int item = 0;  // item a producir
    int num = 0;   // cantidad de items producidos
    
    while (num < counter) {
        buffer[in] = item;  // agregamos un nuevo item al buffer
        draw1(2, in, item);

        item = item + 1;  // valor del proximo item
        in = (in + 1) % BUFFER_SIZE;  // indice del proximo slot libre 
        num++;  // incrementamos el contador 

        sleep(rand() % 3);
    }
    
    pthread_exit(0);
}

static void* reader(void *p) 
{
    int num = 0;
    
    while (num < counter) {
        int item = buffer[out];  // lee un item del buffer
        draw1(5, out, item);

        out = (out + 1) % BUFFER_SIZE;  // indice del proximo item a leer 
        num++;

        sleep(rand() % 3);
    }
    
    pthread_exit(0);
}

static void draw(void)
{
    int i;
    xy(1,1), printf("Prod");
    xy(5,1), printf("Cons");

    xy(3,7);
    for(i = 0; i < BUFFER_SIZE; i++) {
        xy(3,7+(i*4)), printf("-");
    }

    xy(2,7), printf("x");
    xy(5,7), printf("x");

    xy(6,1), fflush(stdout);
}

static void draw1(int w, int i, int v)
{
    static pthread_mutex_t screen = PTHREAD_MUTEX_INITIALIZER;
    xy(3, 7+(i*4));
    printf("%d", v);
    xy(w, 7), printf("\033[K");
    xy(w, 7+(i*4));
    printf("x");
    if (w==2) {
        xy(3,7+(i*4));
        printf("%d",v);
    }
    xy(6,1), fflush(stdout);
    pthread_mutex_unlock(&screen);
}

int main(int argc, char** argv) 
{
    pthread_t writer_t;  // hilo escritor
    pthread_t reader_t;  // hilo lector

    if (argc < 2) {
        fprintf(stderr, "Uso: %s items\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    clear();

    // contador de items producidos
    counter = atoi(argv[1]);

    draw();
    
    pthread_create(&writer_t, NULL, writer, NULL);  // crea el hilo escritor
    pthread_create(&reader_t, NULL, reader, NULL);  // crea el hilo lector

    // esperamos que cada hilo finalice
    pthread_join(reader_t, NULL);  
    pthread_join(writer_t, NULL);
    
    pthread_exit(0);
}
