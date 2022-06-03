#include <stdio.h>
#include <malloc.h>

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

int pop(nodStiva** varf, int* val)
{
	if (*varf == NULL)
		return 0;
	else
	{
		*val = (*varf)->inf;
		nodStiva* aux = *varf;
		*varf = (*varf)->next;
		free(aux);
		return 1;
	}
}

void put(nodCoada** prim, nodCoada** ultim, int val)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf = val;
	nou->next = NULL;
	if (*prim == NULL || *ultim == NULL)
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

int get(nodCoada** prim, nodCoada** ultim, int* val)
{
	if (*prim != NULL && *ultim!=NULL)
	{
		*val = (*prim)->inf;
		nodCoada* aux = *prim;
		*prim = (*prim)->next;
		free(aux);
		return 0;
	}
	else
	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

void parcurgereAdancime(int** mat, int* vizitat, int nr, int nod)
{
	for (int i = 0; i < nr; i++)
		vizitat[i] = 0;

	nodStiva* varf = NULL;

	push(&varf, nod);
	vizitat[nod] = 1;

	while (varf != NULL)
	{
		pop(&varf, &nod);
		printf("%d-", nod + 1);
		for (int k = 0; k < nr; k++)
			if (mat[nod][k] == 1 && vizitat[k] == 0)
			{
				push(&varf, k);
				vizitat[k] = 1;
			}
	}
}

void parcurgereLatime(int** mat, int* vizitat, int nr, int nod)
{
	for (int i = 0; i < nr; i++)
		vizitat[i] = 0;

	nodCoada* prim = NULL, * ultim = NULL;

	put(&prim, &ultim, nod);
	vizitat[nod] = 1;

	while (prim != NULL)
	{
		get(&prim, &ultim, &nod);
		printf("%d-", nod + 1);
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
	FILE* f = fopen("fisier.txt", "r");
	int nr;
	fscanf(f, "%d", &nr);

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
	parcurgereAdancime(mat, vizitat, nr, nod);

	printf("\nParcurgere in latime de la nodul: ");
	scanf("%d", &nod);
	parcurgereLatime(mat, vizitat, nr, nod);

	//numar componente conexe
	printf("\n----------------------\n");
	for (int i = 0; i < nr; i++)
		vizitat[i] = 0;

	int nrComponente = 0;
	for (int j = 0; j < nr; j++)
		if (vizitat[j] == 0)
		{
			nrComponente++;
			parcurgereLatime(mat, vizitat, nr, j);
		}

	if (nrComponente == 1) 
		printf("\nGraful este conex!");
	else 
		printf("\nGraful nu este conex! El are %d componente conexe!", nrComponente);

	free(vizitat);
	for (int i = 0; i < nr; i++)
		free(mat[i]);
	free(mat);
}