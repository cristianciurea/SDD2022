#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

typedef struct {
	int cod;
	char* nume;
	float medie;
	char* programStudiu;
} candidat;

typedef struct {
	candidat info;
	struct nodLS* next;
} nodLS;

typedef struct {
	struct nodLS** vect;
	int dim;
} hashT;

int functieDispersie(hashT tabela, char nume[20])
{
	return nume[0] % tabela.dim;
}

int inserare(hashT tabela, candidat c)
{
	int pozitie = 0;
	if (tabela.vect != NULL)
	{
		pozitie = functieDispersie(tabela, c.nume);

		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->info.cod = c.cod;
		nou->info.nume = (char*)malloc((strlen(c.nume) + 1) * sizeof(char));
		strcpy(nou->info.nume, c.nume);
		nou->info.medie = c.medie;
		nou->info.programStudiu = (char*)malloc((strlen(c.programStudiu) + 1) * sizeof(char));
		strcpy(nou->info.programStudiu, c.programStudiu);

		nou->next = NULL;
		if (tabela.vect[pozitie] == NULL)
		{
			tabela.vect[pozitie] = nou;
		}
		else //situatie de coliziune
		{
			nodLS* temp = tabela.vect[pozitie];
			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = nou;
		}
	}
	return pozitie;
}

void traversareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.dim; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				printf("\npozitie = %d", i);
				nodLS* temp = tabela.vect[i];
				while (temp)
				{
					printf("\ncod = %d, nume = %s, medie = %5.2f, program = %s",
						temp->info.cod, temp->info.nume, temp->info.medie, temp->info.programStudiu);
					temp = temp->next;
				}
			}
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
				nodLS* temp = tabela.vect[i];
				while (temp)
				{
					nodLS* temp2 = temp->next;
					free(temp->info.nume);
					free(temp->info.programStudiu);
					free(temp);
					temp = temp2;
				}
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
	{
		tabela.vect[i] = NULL;
	}

	char buffer[20];
	int n;
	candidat c;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &c.cod);
		fscanf(f, "%s", buffer);
		c.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.nume, buffer);
		fscanf(f, "%f", &c.medie);
		fscanf(f, "%s", buffer);
		c.programStudiu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.programStudiu, buffer);

		inserare(tabela, c);
		free(c.nume);
		free(c.programStudiu);
	}
	fclose(f);

	traversareTabela(tabela);
	dezalocareTabela(tabela);



}