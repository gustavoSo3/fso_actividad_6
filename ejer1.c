#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

#define SIZE 4000

#define INICIAL 900000000
#define FINAL 1000000000
#define N_THREADS 2

int mat[SIZE][SIZE];

struct pair
{
    int start;
    int end;
};

void initmat(int matrix[][SIZE]);

void printnonzeroes(int matrix[SIZE][SIZE]);

int isprime(int n);

void *process_section(void *args);

int main()
{
    clock_t start_ts, stop_ts;
    double elapsed_time;
    pthread_t tid[N_THREADS];

    // Inicializa la matriz con números al azar
    initmat(mat);

    start_ts = clock(); // Tiempo inicial

    // Eliminar de la matriz todos los números que no son primos
    // Esta es la parte que hay que paralelizar
    for (int t = 0; t < N_THREADS; ++t)
    {
        struct pair p;
        p.start = SIZE / N_THREADS * t;
        p.end = SIZE / N_THREADS * (t + 1);
        pthread_create(&tid[t], NULL, process_section, &p);
    }
    for (int t = 0; t < N_THREADS; ++t)
    {
        pthread_join(tid[t], NULL);
    }

    // Hasta aquí termina lo que se tiene que hacer en paralelo
    stop_ts = clock(); // Tiempo final
    elapsed_time = stop_ts - start_ts;

    // printnonzeroes(mat);
    printf("------------------------------\n");
    printf("TIEMPO TOTAL, %f segundos\n", elapsed_time / 1000);
}

void *process_section(void *args)
{
    struct pair p = *((struct pair *)args);
    for (int i = p.start; i < p.end; i++)
        for (int j = p.start; j < p.end; j++)
            if (!isprime(mat[i][j]))
                mat[i][j] = 0;
}

void initmat(int matrix[][SIZE])
{
    int i, j;

    srand(getpid());

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            matrix[i][j] = INICIAL + rand() % (FINAL - INICIAL);
}

void printnonzeroes(int matrix[SIZE][SIZE])
{
    int i, j;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            if (matrix[i][j] != 0)
                printf("%d\n", matrix[i][j]);
}

int isprime(int n)
{
    int d = 3;
    int prime = 0;
    int limit = sqrt(n);

    if ((n < 2) || (n % 2 == 0))
        prime = 0;
    else if (n == 2)
        prime = 1;
    else
    {
        while (d <= limit && n % d)
            d += 2;
        prime = d > limit;
    }
    return (prime);
}