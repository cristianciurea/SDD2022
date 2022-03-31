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
	produs** vect;
	int dim; //101
} hashT;

int functieHash(hashT tabela, char cheie[20])
{
	return cheie[0] % tabela.dim;
}

int inserareTabela(hashT tabela, produs* p)
{
	int pozitie = 0;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash(tabela, (*p).denumire);
		//inserare
		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = p;
		else
		{
			//coliziune
			int index = 1;
			while (pozitie + index < tabela.dim)
			{
				if (tabela.vect[pozitie + index] == NULL)
				{
					tabela.vect[pozitie + index] = p;
					pozitie += index;
					break;
				}
				index++;
			}
		}
	}
	return pozitie;
}

void traversareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.dim; i++)
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie: %d", i);
				printf("\nCod = %d, Denumire = %s, Pret = %5.2f, Cantitate = %5.2f",
					tabela.vect[i]->cod, tabela.vect[i]->denumire,
					tabela.vect[i]->pret, tabela.vect[i]->cantitate);
			}
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
				free(tabela.vect[i]->denumire);
				free(tabela.vect[i]);
			}
		}
		free(tabela.vect);
	}
}

void main()
{
	hashT tabela;
	tabela.dim = 101;
	tabela.vect = (produs**)malloc(tabela.dim * sizeof(produs*));
	for (int i = 0; i < tabela.dim; i++)
		tabela.vect[i] = NULL;

	int n;
	char buffer[20];
	produs *p;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		p = (produs*)malloc(sizeof(produs));
		fscanf(f, "%d", &p->cod);
		fscanf(f, "%s", buffer);
		p->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p->denumire, buffer);
		fscanf(f, "%f", &p->pret);
		fscanf(f, "%f", &p->cantitate);

		inserareTabela(tabela, p);
	}
	fclose(f);

	traversareTabela(tabela);
	dezalocareTabela(tabela);
}