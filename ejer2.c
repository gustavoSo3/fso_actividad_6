#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

#define ITERS 1000000000
#define N_THREADS 4

pthread_mutex_t mutex;
double sum = 0.0;

struct log_args
{
	float x;
	int start;
	int end;
};

void *paralelized_log(void *args);

int main()
{
	clock_t start_ts, stop_ts;
	double elapsed_time;
	float x;
	pthread_t tid[N_THREADS];

	printf("Calcular el logaritmo natural de 1+x\n");
	printf("Dame el valor de x :");
	scanf("%f", &x);

	start_ts = clock(); // Tiempo inicial

	pthread_mutex_init(&mutex, NULL);
	for (int t = 0; t < N_THREADS; ++t)
	{
		struct log_args p;
		p.x = x;
		p.start = (ITERS / N_THREADS * t) + 1;
		p.end = (ITERS / N_THREADS * (t + 1)) + 1;
		pthread_create(&tid[t], NULL, paralelized_log, &p);
	}
	for (int t = 0; t < N_THREADS; ++t)
	{
		pthread_join(tid[t], NULL);
	}

	stop_ts = clock(); // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("Resultado = %.4lf\n", sum);
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %f segundos\n", elapsed_time / 1000);
}

void *paralelized_log(void *args)
{
	struct log_args cast_args = *((struct log_args *)args);
	double local_sum = 0.0;

	for (int n = cast_args.start; n < cast_args.end; n++)
	{
		double power = pow(-1, n + 1) * pow(cast_args.x, n) / n; // Separar cálculo para hacer paralelización
		local_sum += power;
	}
	pthread_mutex_lock(&mutex);
	sum += local_sum;
	pthread_mutex_unlock(&mutex);
}