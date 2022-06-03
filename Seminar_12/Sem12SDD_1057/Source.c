#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int id;
	char* denumire;
	int nrLocuitori;
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

typedef struct
{
	int idNodStart, idNodFinal, greutateArc;
	struct nodLista* next;
} nodLista;

void push(nodStiva** varf, int val)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf = val;
	nou->next = NULL;
	if (*varf == NULL)
	{
		*varf = nou;
	}
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

int get(nodCoada** prim, nodCoada** ultim, int *val)
{
	if (*prim != NULL && *ultim != NULL)
	{
		*val = (*prim)->inf;
		nodCoada* aux = *prim;
		*prim = (*prim)->next;
		free(aux);
		return 0;
	}
	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

void parcurgereAdancime(int** mat, int* vizitat, 
	oras* vect, int nrNoduri, int idNodStart)
{
	for (int i = 0; i < nrNoduri; i++)
		vizitat[i] = 0;

	nodStiva* varf = NULL;

	push(&varf, idNodStart);
	vizitat[idNodStart] = 1;
	while (varf != NULL)
	{
		pop(&varf, &idNodStart);
		printf("%d %s %d\n", idNodStart + 1,
			vect[idNodStart].denumire, vect[idNodStart].nrLocuitori);
		for(int k=0;k<nrNoduri;k++)
			if (mat[idNodStart][k] != 0 && vizitat[k] == 0)
			{
				push(&varf, k);
				vizitat[k] = 1;
			}
	}
}

void parcurgereLatime(int** mat, int* vizitat,
	oras* vect, int nrNoduri, int idNodStart)
{
	for (int i = 0; i < nrNoduri; i++)
		vizitat[i] = 0;

	nodCoada* prim = NULL, * ultim = NULL;

	put(&prim, &ultim, idNodStart);
	vizitat[idNodStart] = 1;
	while (prim != NULL)
	{
		get(&prim, &ultim, &idNodStart);
		printf("%d %s %d\n", idNodStart + 1,
			vect[idNodStart].denumire, vect[idNodStart].nrLocuitori);
		for (int k = 0; k < nrNoduri; k++)
			if (mat[idNodStart][k] != 0 && vizitat[k] == 0)
			{
				put(&prim, &ultim, k);
				vizitat[k] = 1;
			}
	}
}

nodLista* inserareLista(nodLista* cap, int nodStart, int nodFinal, int greutate)
{
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->idNodStart = nodStart;
	nou->idNodFinal = nodFinal;
	nou->greutateArc = greutate;
	nou->next = NULL;
	if (cap == NULL)
		cap = nou;
	else
	{
		nodLista* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

void afisareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		printf("(%d-%d-%d) ->", temp->idNodStart, temp->idNodFinal, temp->greutateArc);
		temp = temp->next;
	}
}

void dezalocareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		nodLista* temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

nodLista* transformListaArce(nodLista* cap, int** mat, int nr)
{
	for(int i=0;i<nr;i++)
		for(int j=0;j<nr;j++)
			if (mat[i][j] != 0)
			{
				cap = inserareLista(cap, i+1, j+1, mat[i][j]);
			}
	return cap;
}

void main()
{
	FILE* f = fopen("fisier.txt", "r");
	int nrNoduri;
	fscanf(f, "%d", &nrNoduri);
	oras* vect = (oras*)malloc(nrNoduri * sizeof(oras));
	char buffer[20];
	for (int i = 0; i < nrNoduri; i++)
	{
		fscanf(f, "%d", &vect[i].id);
		fscanf(f, "%s", buffer);
		vect[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(vect[i].denumire, buffer);
		fscanf(f, "%d", &vect[i].nrLocuitori);
	}

	int** mat = (int**)malloc(nrNoduri * sizeof(int*));
	for (int i = 0; i < nrNoduri; i++)
		mat[i] = (int*)malloc(nrNoduri * sizeof(int));

	for (int i = 0; i < nrNoduri; i++)
		for (int j = 0; j < nrNoduri; j++)
			mat[i][j] = 0;

	int ii, jj, nrArce, greutate;
	fscanf(f, "%d", &nrArce);
	for (int i = 0; i < nrArce; i++)
	{
		fscanf(f, "%d", &ii);
		fscanf(f, "%d", &jj);
		fscanf(f, "%d", &greutate);
		if (ii <= nrNoduri && jj <= nrNoduri)
		{
			mat[ii - 1][jj - 1] = greutate;
			//mat[jj - 1][ii - 1] = greutate;
		}
	}
	fclose(f);

	printf("\nMatrice de adiacenta:\n");
	for (int i = 0; i < nrNoduri; i++)
	{
		for (int j = 0; j < nrNoduri; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}

	nodLista* cap = NULL;
	cap = transformListaArce(cap, mat, nrNoduri);
	afisareLista(cap);
	dezalocareLista(cap);

	int* vizitat = (int*)malloc(nrNoduri * sizeof(int));

	printf("\nNod pornire traversare adancime: ");
	int nodStart;
	scanf("%d", &nodStart);
	parcurgereAdancime(mat, vizitat, vect, nrNoduri, nodStart);

	printf("Nod pornire traversare latime: ");
	scanf("%d", &nodStart);
	parcurgereLatime(mat, vizitat, vect, nrNoduri, nodStart);
}
