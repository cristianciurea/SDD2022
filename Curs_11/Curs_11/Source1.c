#include <stdio.h>
#include <malloc.h>

//definire nod lista simpla
typedef struct 
{
	int sursa, destinatie; //nodul de start si nodul terminal
	struct nod* next;
} nod;

//functie pentru reprezentarea unui graf prin lista simpla
nod* conversieMatriceLista(nod* cap, int** mat, int nr)
{
	nod* temp;
	//for(int i=0;i<nr;i++)
	//for(int j=0;j<nr;j++)
	for (int i = 0; i < nr - 1; i++)
		for (int j = i + 1; j < nr; j++)
		{
			if (mat[i][j])
			{
				nod* nou = (nod*)malloc(sizeof(nod));
				nou->sursa = i + 1;
				nou->destinatie = j + 1;
				nou->next = NULL;
				if (cap == NULL)
				{
					cap = nou;
				}
				else
				{
					for (temp = cap; temp->next; temp = temp->next);
					temp->next = nou;
					temp = nou;
				}
			}
		}
	return cap;
}

void afisareLista(nod* cap)
{
	nod* temp = cap;
	while (temp)
	{
		printf("(%d,%d) ", temp->sursa, temp->destinatie);
		temp = temp->next;
	}
}

void dezalocare(nod* cap)
{
	nod* temp, *temp2;
	temp = cap;
	while (temp)
	{
		temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

void main()
{
	int n;
	FILE* f = fopen("fisier1.txt", "r");
	//printf("Nr. de noduri=");
	fscanf(f, "%d", &n);

	int** mat = (int**)malloc(n*sizeof(int*));
	for (int i = 0; i < n; i++) 
		mat[i] = (int*)malloc(n*sizeof(int));

	//for (int i=0;i<n;i++)
	//for (int j=0;j<n;j++)
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
		{
			//printf("Matr[%d][%d]=", i + 1, j + 1);
			fscanf(f, "%d", &mat[i][j]);
		}
	fclose(f);

	nod* cap = NULL;
	cap = conversieMatriceLista(cap, mat, n);
	afisareLista(cap);
	dezalocare(cap);
	for (int i = 0; i < n; i++)
		free(mat[i]);
	free(mat);
}