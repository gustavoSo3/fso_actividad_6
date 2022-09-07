#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

#define ITERS 1000000000

int main()
{
    clock_t start_ts, stop_ts;
    double elapsed_time;
	int n;
	double sum = 0.0;
	float x;

	printf("Calcular el logaritmo natural de 1+x\n");
	printf("Dame el valor de x :");
	scanf("%f",&x);

    start_ts = clock(); // Tiempo inicial

	for(n=1;n<ITERS;n++) {
        double power = pow(-1,n+1) * pow(x,n) / n; // Separar cálculo para hacer paralelización
		sum = sum + power;
    }

    stop_ts = clock(); // Tiempo final

	elapsed_time = stop_ts - start_ts;
	printf("Resultado = %.4lf\n",sum);
	printf("------------------------------\n");
	printf("TIEMPO TOTAL, %f segundos\n",elapsed_time/1000);
}
