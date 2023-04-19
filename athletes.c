#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _athlete
{
	int m, f;
} athlete;

typedef struct _athletes
{
	int N;
	athlete *atl;
} athletes;

////////// Prototypes //////////
void createRandAthletes(athletes*);
void athletesSort(athletes*);
athletes getHighestAthletesTower(athletes*);
void athletesPrint(athletes*);


int main()
{
	srand(time(0));
	athletes atls;

	createRandAthletes(&atls);
	athletesPrint(&atls);

	athletes highestTower = getHighestAthletesTower(&atls);
	athletesPrint(&highestTower);

	free(atls.atl);
	free(highestTower.atl);
	return 0;
}


////////// Functions //////////
void createRandAthletes(athletes *atls)
{
	atls->N = rand()%20 + 1;
	atls->atl = (athlete*)calloc(atls->N, sizeof(athlete));
	for (int i = 0; i < atls->N; i++)
		atls->atl[i].m = rand()%50 + 1;

	athletesSort(atls);
	atls->atl[0].f = rand()%5 + 1;
	for (int i = 1; i < atls->N; i++)
	{
		atls->atl[i].f = atls->atl[i-1].f + rand()%5;
		atls->atl[i].f += atls->atl[i].m - atls->atl[i-1].m;
	}
}

void athletesSort(athletes *atls)
{
	athlete min;
	for (int i = 0; i < (atls->N) - 1; i++)
	{
		min = atls->atl[i];
		for (int j = i; j < atls->N; j++)
		{
			if (atls->atl[j].m <= min.m)
			{
				atls->atl[i] = atls->atl[j];
				atls->atl[j] = min;
				min = atls->atl[i];
			}
		}
	}
} // May need optimization

athletes getHighestAthletesTower(athletes *atls)
{
	int currentWeight = 0, count = 0, isOk = 0;
	int index[atls->N];

	do {
		for (int i = 0; i < atls->N; i++)
		{
			isOk = 0;

			if (atls->atl[i].f >= currentWeight)
			{
				currentWeight += atls->atl[i].m;
				index[count] = i;
				count++;
				isOk = 1;
			}
		}	
	} while (isOk);

	athletes highestTower;
	highestTower.N = count;
	highestTower.atl = (athlete*)calloc(highestTower.N, sizeof(athlete));
	for (int i = 0; i < count; i++)
		highestTower.atl[i] = atls->atl[index[i]];


	return highestTower;
}

void athletesPrint(athletes *atls)
{
	printf("\n");
	for (int i = 0; i < atls->N; i++)
	{
		printf("%3d) mass – %3d", i+1, atls->atl[i].m);
		printf("   force – %3d\n", atls->atl[i].f);
	}
	printf("\n");
	printf("N = %d \n\n\n", atls->N);
}