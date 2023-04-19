#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	clock_t begin = clock();


	int N;
	printf("Введите диапазон чисел: ");
	scanf("%d", &N);
	int *sieve;
	sieve = (int*)calloc(N, sizeof(int));
	if (!sieve)
	{
		printf("Allocation failure.");
		exit(1);
	}

	for (int i = 2; i*i < N; i++)
		if (sieve[i] == 0)
			for (int k = i*i; k < N; k += i)
				sieve[k] = 1;

	int prime_count = 0;
	for (int i = 2; i < N; i++)
		if (sieve[i] == 0)
			prime_count++;
	
	free(sieve);
	sieve = NULL;


	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("\nДиапазон чисел: %d\n", N);
	printf("Кол-во простых чисел: %d\n", prime_count);
	printf("Затраченное время: %f с.\n", time_spent);

	return 0;
}