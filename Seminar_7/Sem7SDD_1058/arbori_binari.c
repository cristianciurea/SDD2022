#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int anNastere;
	char* nume;
	char sex;
} Persoana;

typedef struct
{
	Persoana inf;
	struct nodArb* stanga, * dreapta;
} nodArb;

nodArb* creareNod(Persoana p, nodArb* st, nodArb* dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.anNastere = p.anNastere;
	nou->inf.nume = (char*)malloc((strlen(p.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, p.nume);
	nou->inf.sex = p.sex;

	nou->stanga = st;
	nou->dreapta = dr;

	return nou;
}

nodArb* inserareNod(Persoana p, nodArb* rad)
{
	if (rad != NULL)
	{
		if (p.anNastere < rad->inf.anNastere)
		{
			rad->stanga = inserareNod(p, rad->stanga);
			return rad;
		}
		else
			if (p.anNastere > rad->inf.anNastere)
			{
				rad->dreapta = inserareNod(p, rad->dreapta);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(p, NULL, NULL);
}

void traversarePreordine(nodArb* rad)
{
	if (rad != NULL)
	{
		printf("\nAn nastere = %d, Nume = %s, Sex = %c",
			rad->inf.anNastere, rad->inf.nume, rad->inf.sex);
		traversarePreordine(rad->stanga);
		traversarePreordine(rad->dreapta);
	}
}

void traversareInordine(nodArb* rad)
{
	if (rad != NULL)
	{
		traversareInordine(rad->stanga);
		printf("\nAn nastere = %d, Nume = %s, Sex = %c",
			rad->inf.anNastere, rad->inf.nume, rad->inf.sex);
		traversareInordine(rad->dreapta);
	}
}

void traversarePostordine(nodArb* rad)
{
	if (rad != NULL)
	{
		traversarePostordine(rad->stanga);
		traversarePostordine(rad->dreapta);
		printf("\nAn nastere = %d, Nume = %s, Sex = %c",
			rad->inf.anNastere, rad->inf.nume, rad->inf.sex);
	}
}

void dezalocare(nodArb* rad)
{
	if (rad != NULL)
	{
		nodArb* st = rad->stanga;
		nodArb* dr = rad->dreapta;
		free(rad->inf.nume);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

nodArb* cautare(nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie == rad->inf.anNastere)
			return rad;
		else
			if (cheie < rad->inf.anNastere)
				return cautare(rad->stanga, cheie);
			else
				return cautare(rad->dreapta, cheie);
	}
	else
		return NULL;
}

void salvareVectorSex(nodArb* rad, char sex, Persoana* vect, int* nr)
{
	if (rad != NULL)
	{
		if (rad->inf.sex == sex)
		{
			vect[*nr] = rad->inf;
			(*nr)++;
		}
		salvareVectorSex(rad->stanga, sex, vect, nr);
		salvareVectorSex(rad->dreapta, sex, vect, nr);
	}
}

void salvareNoduriFrunza(nodArb* rad, Persoana* vect, int* nr)
{
	if (rad != NULL)
	{
		if (rad->stanga== NULL && rad->dreapta==NULL)
		{
			vect[*nr] = rad->inf;
			(*nr)++;
		}
		salvareNoduriFrunza(rad->stanga, vect, nr);
		salvareNoduriFrunza(rad->dreapta, vect, nr);
	}
}

int maxim(int a, int b)
{
	int max = a;
	if (max < b)
		max = b;
	return max;
}

int inaltimeArbore(nodArb* rad)
{
	if (rad != NULL)
		return 1 + maxim(inaltimeArbore(rad->stanga),
			inaltimeArbore(rad->dreapta));
	else
		return 0;
}

void main()
{
	nodArb* rad = NULL;
	Persoana p;
	char buffer[20];
	int n;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &p.anNastere);
		fscanf(f, "%s", buffer);
		p.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.nume, buffer);
		fscanf(f, " %c", &p.sex);

		rad = inserareNod(p, rad);
		free(p.nume);
	}
	fclose(f);

	printf("\n------------preordine----------\n");
	traversarePreordine(rad);
	printf("\n------------inordine----------\n");
	traversareInordine(rad);
	printf("\n------------postordine----------\n");
	traversarePostordine(rad);

	nodArb* nodCautat = cautare(rad, 1980);
	if (nodCautat != NULL)
		printf("\nPersoana cautata se numeste %s",
			nodCautat->inf.nume);
	else
		printf("\nNu exista!");

	printf("\n-----vector-----\n");
	Persoana* vect = (Persoana*)malloc(n * sizeof(Persoana));
	int nr = 0;
	//salvareVectorSex(rad, 'F', vect, &nr);
	salvareNoduriFrunza(rad, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nAn nastere = %d, Nume = %s, Sex = %c",
			vect[i].anNastere, vect[i].nume, vect[i].sex);
	free(vect);

	printf("\nInaltime arbore: %d", inaltimeArbore(rad));

	dezalocare(rad);

}