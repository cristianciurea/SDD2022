#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct 
{
	int zi, luna, an;
} dataTransmitere;

typedef struct
{
	dataTransmitere data;
	char* destinatar;
	float dimensiune;
} email;

typedef struct
{
	email inf;
	struct nodstiva* next;
} nodstiva;

void push(nodstiva** varf, email e)
{
	nodstiva* nou = (nodstiva*)malloc(sizeof(nodstiva));
	nou->inf.destinatar = (char*)malloc((strlen(e.destinatar) + 1) * sizeof(char));
	strcpy(nou->inf.destinatar, e.destinatar);

	nou->inf.data.zi = e.data.zi;
	nou->inf.data.luna = e.data.luna;
	nou->inf.data.an = e.data.an;

	nou->inf.dimensiune = e.dimensiune;

	nou->next = NULL;

	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

int pop(nodstiva** varf, email* e)
{
	if (*varf == NULL)
		return -1;
	else
	{
		(*e).destinatar = (char*)malloc((strlen((*varf)->inf.destinatar) + 1) * sizeof(char));
		strcpy((*e).destinatar, (*varf)->inf.destinatar);
		(*e).dimensiune = (*varf)->inf.dimensiune;
		(*e).data.zi = (*varf)->inf.data.zi;
		(*e).data.luna = (*varf)->inf.data.luna;
		(*e).data.an = (*varf)->inf.data.an;

		nodstiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->inf.destinatar);
		free(temp);

		return 0;
	}
}

void traversare(nodstiva* varf)
{
	nodstiva* temp = varf;
	while (temp)
	{
		printf("\nDestinatar: %s, Dimensiune: %5.2f, Data: %d-%d-%d", temp->inf.destinatar, temp->inf.dimensiune,
			temp->inf.data.zi, temp->inf.data.luna, temp->inf.data.an);
		temp = temp->next;
	}
}



void main()
{
	int n;
	nodstiva* varf = NULL;
	email e;
	char buffer[20];

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);

	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%s", buffer);
		e.destinatar = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(e.destinatar, buffer);

		fscanf(f, "%f", &e.dimensiune);
		fscanf(f, "%d", &e.data.zi);
		fscanf(f, "%d", &e.data.luna);
		fscanf(f, "%d", &e.data.an);

		push(&varf, e);
		free(e.destinatar);

		
	}
	fclose(f);
	traversare(varf);

	email e2;
	while (pop(&varf, &e2) == 0)
	{
		printf("\nAm sters %s", e2.destinatar);
		free(e2.destinatar);
	}
}