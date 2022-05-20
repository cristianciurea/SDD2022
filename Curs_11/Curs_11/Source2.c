#include <stdio.h>
#include <malloc.h>

typedef struct 
{
	int id;
	char* denumire;
} oras;

typedef struct 
{
	int inf;
	struct nodStiva* next;
} nodStiva;

typedef struct 
{
	int inf;
	struct nodCoada* next;
} nodCoada;

void push(nodStiva** varf, int val)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf = val;
	nou->next = NULL;
	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

void pop(nodStiva** varf, int* val)
{
	if (*varf == NULL)
		return;
	else
	{
		*val = (*varf)->inf;
		nodStiva* aux = *varf;
		*varf = (*varf)->next;
		free(aux);
	}
}

void put(nodCoada** prim, nodCoada** ultim, int val)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf = val;
	nou->next = NULL;
	if (*prim == NULL && *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

void get(nodCoada** prim, nodCoada** ultim, int* val)
{
	if (*prim != NULL && *ultim != NULL)
	{
		*val = (*prim)->inf;
		nodCoada* aux = *prim;
		*prim = (*prim)->next;
		free(aux);
	}
	if (*prim == NULL)
		*ultim = NULL;
}

void parcurgereAdancime(int** mat, int* vizitat, oras *vect, int nr, int nod)
{
	for (int i = 0; i < nr; i++)
		vizitat[i] = 0;

	nodStiva* varf = NULL;

	push(&varf, nod);
	vizitat[nod] = 1;

	while (varf != NULL)
	{
		pop(&varf, &nod);
		printf("%d %s - ", nod+1, vect[nod].denumire);
		for (int k = 0; k < nr; k++)
			if (mat[nod][k] == 1 && vizitat[k] == 0)
			{
				push(&varf, k);
				vizitat[k] = 1;
			}
	}
}

void parcurgereLatime(int** mat, int* vizitat, oras* vect, int nr, int nod)
{
	for (int i = 0; i < nr; i++)
		vizitat[i] = 0;

	nodCoada* prim = NULL, * ultim = NULL;

	put(&prim, &ultim, nod);
	vizitat[nod] = 1;

	while (prim != NULL)
	{
		get(&prim, &ultim, &nod);
		printf("%d %s - ", nod+1, vect[nod].denumire);
		for (int k = 0; k < nr; k++)
			if (mat[nod][k] == 1 && vizitat[k] == 0)
			{
				put(&prim, &ultim, k);
				vizitat[k] = 1;
			}
	}
}

void main()
{
	FILE* f = fopen("fisier2.txt", "r");
	int nr;
	fscanf(f, "%d", &nr);
	oras* vect = (oras*)malloc(nr*sizeof(oras));

	char buffer[20];
	for (int i = 0; i < nr; i++)
	{
		fscanf(f, "%d", &vect[i].id);
		fscanf(f, "%s", buffer);
		vect[i].denumire = (char*)malloc((strlen(buffer) + 1)*sizeof(char));
		strcpy(vect[i].denumire, buffer);
	}

	int** mat = (int**)malloc(nr * sizeof(int*));
	for (int i = 0; i < nr; i++)
		mat[i] = (int*)malloc(nr * sizeof(int));

	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nr; j++)
			mat[i][j] = 0;

	int n, ii, jj;
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &ii);
		fscanf(f, "%d", &jj);
		if (ii <= n && jj <= n)
		{
			mat[ii - 1][jj - 1] = 1;
			mat[jj - 1][ii - 1] = 1;
		}
	}

	fclose(f);

	int* vizitat = (int*)malloc(nr * sizeof(int));

	int nod;
	printf("\nParcurgere in adancime de la nodul: ");
	scanf("%d", &nod);
	parcurgereAdancime(mat, vizitat, vect, nr, nod);

	printf("\nParcurgere in latime de la nodul: ");
	scanf("%d", &nod);
	parcurgereLatime(mat, vizitat, vect, nr, nod);

	free(vect);
	free(vizitat);
	for (int i = 0; i < nr; i++)
		free(mat[i]);
	free(mat);
}