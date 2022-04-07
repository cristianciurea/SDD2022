#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int coloana, valoare;
	struct nodLS* next;
} nodLS;

typedef struct
{
	struct nodLS* inf;
	struct nodLP* next;
} nodLP;

int rara(int** mat, int nrLin, int nrCol)
{
	int nrNenule = 0;
	for (int i = 0; i < nrLin; i++)
		for (int j = 0; j < nrCol; j++)
			if (mat[i][j] != 0)
				nrNenule++;
	if (nrNenule / (float)(nrLin * nrCol) < 0.3)
		return nrNenule;
	else
		return 0;
}

void inserareLS(nodLS** capLS, int** mat, 
	int nrLin, int nrCol, int linie)
{
	for (int j = 0; j < nrCol; j++)
	{
		if (mat[linie][j] != 0 && rara(mat, nrLin, nrCol)!=0)
		{
			nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
			nou->coloana = j;
			nou->valoare = mat[linie][j];
			nou->next = NULL;
			if (*capLS == NULL)
				*capLS = nou;
			else
			{
				nodLS* temp = *capLS;
				while (temp->next)
					temp = temp->next;
				temp->next = nou;
			}
		}
	}
}

void inserareLP(nodLP** capLP, nodLS* capLS)
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->inf = capLS;
	nou->next = NULL;
	if (*capLP == NULL)
		*capLP = nou;
	else
	{
		nodLP* temp = *capLP;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		printf("Coloana=%d, Valoare=%d\n", 
			temp->coloana, temp->valoare);
		temp = temp->next;
	}
}

void traversareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	int i = 0;
	while (temp)
	{
		printf("Sublista: %d\n", i);
		traversareLS(temp->inf);
		temp = temp->next;
		i++;
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	while (temp)
	{
		nodLP* temp2 = temp->next;
		dezalocareLS(temp->inf);
		free(temp);
		temp = temp2;
	}
}

void main()
{
	int nrLin, nrCol;
	int** mat;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrLin);
	fscanf(f, "%d", &nrCol);
	mat = (int**)malloc(nrLin * sizeof(int*));
	for (int i = 0; i < nrLin; i++)
		mat[i] = (int*)malloc(nrCol * sizeof(int));
	for (int i = 0; i < nrLin; i++)
		for (int j = 0; j < nrCol; j++)
			fscanf(f, "%d", &mat[i][j]);
	fclose(f);

	nodLP* capLP = NULL;
	for (int i = 0; i < nrLin; i++)
	{
		nodLS* capLS = NULL;
		inserareLS(&capLS, mat, nrLin, nrCol, i);
		inserareLP(&capLP, capLS);
	}
	traversareLP(capLP);
	dezalocareLP(capLP);

	for (int i = 0; i < nrLin; i++)
		free(mat[i]);
	free(mat);
}