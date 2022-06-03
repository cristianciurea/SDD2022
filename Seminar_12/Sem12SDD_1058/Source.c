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
	int idNodStart, idNodFinal, greutateArc;
	struct nodLista* next;
} nodLista;

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
		return -1;
	else
	{
		*val = (*varf)->inf;
		nodStiva* aux = *varf;
		*varf = (*varf)->next;
		free(aux);
		return 0;
	}
}

void parcurgereAdancime(int** mat, int nrNoduri, oras* vect, int idNodStart)
{
	int* vizitat = (int*)malloc(nrNoduri * sizeof(int));
	for (int i = 0; i < nrNoduri; i++)
		vizitat[i] = 0;

	nodStiva* varf = NULL;

	push(&varf, idNodStart);
	vizitat[idNodStart] = 1;
	while (varf != NULL)
	{
		pop(&varf, &idNodStart);
		printf("\n%d %s %d", idNodStart + 1,
			vect[idNodStart].denumire, vect[idNodStart].nrLocuitori);
		for(int k=0;k<nrNoduri;k++)
			if (mat[idNodStart][k] !=0 && vizitat[k] == 0)
			{
				push(&varf, k);
				vizitat[k] = 1;
			}
	}
}

nodLista* inserareLista(nodLista* cap, int idNodS, int idNodF, int gr)
{
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->idNodStart = idNodS;
	nou->idNodFinal = idNodF;
	nou->greutateArc = gr;
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
		printf("(%d, %d, %d) -> ", temp->idNodStart,
			temp->idNodFinal, temp->greutateArc);
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

void transformListaArce(int** mat, int nrNoduri, nodLista** cap)
{
	for(int i=0;i<nrNoduri;i++)
		for(int j=0;j<nrNoduri;j++)
			if (mat[i][j] != 0)
			{
				*cap = inserareLista(*cap, i + 1, j + 1, mat[i][j]);
			}
}

nodLista* arcGreutateMinima(nodLista* cap)
{
	nodLista* temp = cap;
	nodLista* min = cap;
	while (temp)
	{
		if (min->greutateArc > temp->greutateArc)
			min = temp;
		temp = temp->next;
	}
	return min;
}

void main()
{
	int nrNoduri, nrArce;
	char buffer[20];
	int** mat;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrNoduri);
	mat = (int**)malloc(nrNoduri * sizeof(int*));
	for (int i = 0; i < nrNoduri; i++)
		mat[i] = (int*)malloc(nrNoduri * sizeof(int));
	oras* vect = (oras*)malloc(nrNoduri * sizeof(oras));
	for (int i = 0; i < nrNoduri; i++)
	{
		fscanf(f, "%d", &vect[i].id);
		fscanf(f, "%s", buffer);
		vect[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(vect[i].denumire, buffer);
		fscanf(f, "%d", &vect[i].nrLocuitori);
	}
	for (int i = 0; i < nrNoduri; i++)
		for (int j = 0; j < nrNoduri; j++)
			mat[i][j] = 0;
	fscanf(f, "%d", &nrArce);
	int ii, jj, greutate;
	for (int i = 0; i < nrArce; i++)
	{
		fscanf(f, "%d", &ii);
		fscanf(f, "%d", &jj);
		fscanf(f, "%d", &greutate);
		mat[ii - 1][jj - 1] = greutate;
		//mat[jj - 1][ii - 1] = greutate;
	}
	fclose(f);

	int idNodStart;
	printf("Nod de pornire parcurgere adancime: ");
	scanf("%d", &idNodStart);
	parcurgereAdancime(mat, nrNoduri, vect, idNodStart);

	nodLista* cap = NULL;
	transformListaArce(mat, nrNoduri, &cap);
	afisareLista(cap);

	nodLista* min = arcGreutateMinima(cap);
	printf("Arc greutate minima (%d, %d, %d)", min->idNodStart,
		min->idNodFinal, min->greutateArc);

	dezalocareLista(cap);
}