#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void factorial(void *ptr)
{
	long nro = *((long*)ptr), resultado = 1;
	
	for(; nro > 0; nro--)
		resultado *= nro;
	
	int res = (int) resultado; //No se porque pero esta linea "innecesaria" hace que retorne corretamente el numero
	return (void*) resultado;
}

int nroElementos(char *arg)
{
	int i = 0, n = 0;
	while((char)arg[i++] != '\0')
		n++;
		
	return n;
}

void convertir(char **argv, long *numeros, int n)
{
	int i;
	for(i = 1; i <= n; i++)
		numeros[i-1] = (long)atoi(argv[i]);
}

int main(int argc, char **argv)
{
	int i = 0, n = 0;
	void *res;
	
	n = argc-1;
	if(n < 1)
		return 0;
	
	long numeros[n];
	convertir(argv, numeros, n);
	int result[n];
	
   	pthread_t hilo[n];
   	
   	for(i = 0; i < n; i++)
   		pthread_create(&hilo[i], NULL, (void*)&factorial, (void*)&numeros[i]);
   		
   	for(i = 0; i < n; i++)
   	{
   		pthread_join(hilo[i], &res);
   		result[i] = (int)res;
   	}
   		
   	for(i = 0; i < n; i++)
   		printf("Factorial de %ld: %d\n", numeros[i], result[i]);
	
	return 0;
}
