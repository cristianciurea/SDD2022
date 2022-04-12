#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int id;
	char* denumire;
	float salariu;
} job;

typedef struct
{
	job info;
	struct nodArb* stanga, * dreapta;
} nodArb;

nodArb* creareNod(job j, nodArb* st, nodArb* dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.id = j.id;
	nou->info.denumire = (char*)malloc((strlen(j.denumire) + 1) *
		sizeof(char));
	strcpy(nou->info.denumire, j.denumire);
	nou->info.salariu = j.salariu;
	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}

nodArb* inserareNod(job j, nodArb* rad)
{
	if (rad != NULL)
	{
		if (j.id < rad->info.id)
		{
			rad->stanga = inserareNod(j, rad->stanga);
			return rad;
		}
		else
			if (j.id > rad->info.id)
			{
				rad->dreapta = inserareNod(j, rad->dreapta);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(j, NULL, NULL);
}

void preordine(nodArb* rad)
{
	if (rad != NULL)
	{
		printf("\nId = %d, Denumire = %s, Salariu = %5.2f",
			rad->info.id, rad->info.denumire, rad->info.salariu);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

void inordine(nodArb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->stanga);
		printf("\nId = %d, Denumire = %s, Salariu = %5.2f",
			rad->info.id, rad->info.denumire, rad->info.salariu);
		inordine(rad->dreapta);
	}
}

nodArb* cautareJob(nodArb* rad, int id)
{
	if (rad != NULL)
	{
		if (id == rad->info.id)
			return rad;
		else
			if (id < rad->info.id)
				return cautareJob(rad->stanga, id);
			else
				return cautareJob(rad->dreapta, id);
	}
	else
		return NULL;
}

void postordine(nodArb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->stanga);
		postordine(rad->dreapta);
		printf("\nId = %d, Denumire = %s, Salariu = %5.2f",
			rad->info.id, rad->info.denumire, rad->info.salariu);
	}
}

void dezalocare(nodArb* rad)
{
	if (rad != NULL)
	{
		nodArb* st = rad->stanga;
		nodArb* dr = rad->dreapta;
		free(rad->info.denumire);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

void conversieArboreVector(nodArb* rad, job* vect, int* nr)
{
	if (rad != NULL)
	{
		vect[*nr] = rad->info;
		(*nr)++;
		conversieArboreVector(rad->stanga, vect, nr);
		conversieArboreVector(rad->dreapta, vect, nr);
	}
}

void salvareNoduriFrunzaVector(nodArb* rad, job* vect, int* nr)
{
	if (rad != NULL)
	{
		if (rad->stanga == NULL && rad->dreapta == NULL)
		{
			vect[*nr] = rad->info;
			(*nr)++;
		}
		salvareNoduriFrunzaVector(rad->stanga, vect, nr);
		salvareNoduriFrunzaVector(rad->dreapta, vect, nr);
	}
}

void nrJoburiSalariuPrag(nodArb* rad, float prag, int* nr)
{
	if (rad != NULL)
	{
		if (rad->info.salariu >= prag)
			(*nr)++;
		nrJoburiSalariuPrag(rad->stanga, prag, nr);
		nrJoburiSalariuPrag(rad->dreapta, prag, nr);
	}
}

void main()
{
	int n;
	nodArb* rad = NULL;
	char buffer[20];
	job j;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &j.id);
		fscanf(f, "%s", buffer);
		j.denumire = (char*)malloc((strlen(buffer) + 1) *
			sizeof(char));
		strcpy(j.denumire, buffer);
		fscanf(f, "%f", &j.salariu);

		rad = inserareNod(j, rad);
		free(j.denumire);
	}
	fclose(f);
	printf("\n--------preordine----------\n");
	preordine(rad);
	printf("\n--------inordine----------\n");
	inordine(rad);
	printf("\n--------postordine----------\n");
	postordine(rad);

	nodArb* nodCautat = NULL;
	nodCautat = cautareJob(rad, 66);
	printf("\nJobul cautat este %s", nodCautat->info.denumire);

	printf("\n--------Conversie vector----------\n");
	job* vect = (job*)malloc(n * sizeof(job));
	int nr = 0;
	//conversieArboreVector(rad, vect, &nr);
	salvareNoduriFrunzaVector(rad, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nId = %d, Denumire = %s, Salariu = %5.2f",
			vect[i].id, vect[i].denumire, vect[i].salariu);

	free(vect);

	int nrJoburi = 0;
	nrJoburiSalariuPrag(rad, 3000, &nrJoburi);
	printf("\nNr. joburi cu salariu peste prag: %d", nrJoburi);

	dezalocare(rad);
}