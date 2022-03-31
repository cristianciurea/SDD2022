#include<stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* denumire;
	float pret;
	float cantitate;
} produs;

typedef struct
{
	produs inf;
	struct nodLS* next;
} nodLS;

typedef struct
{
	struct nodLS** vect;
	int dim; //101
} hashT;

int functieHash(hashT tabela, char cheie[20])
{
	return cheie[0] % tabela.dim;
}

int inserareTabela(hashT tabela, produs p)
{
	int pozitie = 0;
	if (tabela.vect != NULL)
	{
		//calcul pozitie vector
		pozitie = functieHash(tabela, p.denumire);
		//creare si initializare nod lista
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->inf.cod = p.cod;
		nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
		strcpy(nou->inf.denumire, p.denumire);
		nou->inf.pret = p.pret;
		nou->inf.cantitate = p.cantitate;
		nou->next = NULL;
		//inserare in vector
		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = nou;
		else
		{
			//situatie de coliziune - inserare in lista
			nodLS* temp = tabela.vect[pozitie];
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = nou;
		}
	}
	return pozitie;
}

void traversareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		printf("\nCod = %d, Denumire = %s, Pret = %5.2f, Cantitate = %5.2f",
			temp->inf.cod, temp->inf.denumire, temp->inf.pret, temp->inf.cantitate);
		temp = temp->next;
	}
}

void traversareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for(int i=0;i<tabela.dim;i++)
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie: %d", i);
				traversareLista(tabela.vect[i]);
			}
	}
}

void dezalocareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		nodLS* temp2 = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = temp2;
	}
}

void dezalocareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.dim; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				dezalocareLista(tabela.vect[i]);
			}
		}
		free(tabela.vect);
	}
}

void main()
{
	hashT tabela;
	tabela.dim = 101;
	tabela.vect = (nodLS**)malloc(tabela.dim * sizeof(nodLS*));
	for (int i = 0; i < tabela.dim; i++)
		tabela.vect[i] = NULL;

	int n;
	char buffer[20];
	produs p;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);
		fscanf(f, "%f", &p.pret);
		fscanf(f, "%f", &p.cantitate);

		inserareTabela(tabela, p);
		free(p.denumire);
	}
	fclose(f);

	traversareTabela(tabela);
	dezalocareTabela(tabela);
}