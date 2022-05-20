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
	int BF;
	job info;
	struct nodArb* stanga, * dreapta;
} nodArb;

typedef struct
{
	job info;
	struct nodLista* next;
} nodLista;

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
		printf("\nId = %d, Denumire = %s, Salariu = %5.2fy, BF = %d",
			rad->info.id, rad->info.denumire, rad->info.salariu, rad->BF);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

void inordine(nodArb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->stanga);
		printf("\nId = %d, Denumire = %s, Salariu = %5.2f, BF = %d",
			rad->info.id, rad->info.denumire, rad->info.salariu, rad->BF);
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
		printf("\nId = %d, Denumire = %s, Salariu = %5.2f, BF = %d",
			rad->info.id, rad->info.denumire, rad->info.salariu, rad->BF);
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

nodArb* stergeRad(nodArb* rad)
{
	nodArb* aux = rad;
	if (rad->stanga != NULL)
	{
		rad = aux->stanga;
		if (aux->dreapta != NULL)
		{
			nodArb* maxS = aux->stanga;
			while (maxS->dreapta != NULL)
				maxS = maxS->dreapta;
			maxS->dreapta = aux->dreapta;
		}
	}
	else
		if (aux->dreapta != NULL)
			rad = aux->dreapta;
		else
			rad = NULL;
	free(aux->info.denumire);
	free(aux);
	return rad;
}

nodArb* stergeNodRecursiv(nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie < rad->info.id)
			rad->stanga = stergeNodRecursiv(rad->stanga, cheie);
		else
			if (cheie > rad->info.id)
				rad->dreapta = stergeNodRecursiv(rad->dreapta, cheie);
			else
				rad = stergeRad(rad);
		return rad;
	}
	else
		return NULL;
}

nodArb* stergeDupaDenumire(nodArb* rad, char* denumire)
{
	if (rad != NULL)
	{
		if (strcmp(rad->info.denumire, denumire) == 0)
		{
			rad = stergeNodRecursiv(rad, rad->info.id);
			return rad;
		}
		else
		{
			rad->stanga = stergeDupaDenumire(rad->stanga, denumire);
			rad->dreapta = stergeDupaDenumire(rad->dreapta, denumire);
			return rad;
		}
	}
	else
		return NULL;
}

void calculBF(nodArb* rad)
{
	if (rad != NULL)
	{
		rad->BF = inaltimeArbore(rad->dreapta) - inaltimeArbore(rad->stanga);
		calculBF(rad->stanga);
		calculBF(rad->dreapta);
	}
}

nodLista* inserareLista(nodLista* cap, job j)
{
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->info.id = j.id;
	nou->info.denumire = (char*)malloc((strlen(j.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, j.denumire);
	nou->info.salariu = j.salariu;
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

void traversareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		printf("\nId = %d, Denumire = %s, Salariu = %5.2f",
			temp->info.id, temp->info.denumire, temp->info.salariu);
		temp = temp->next;
	}
}

void dezalocareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		nodLista* temp2 = temp->next;
		free(temp->info.denumire);
		free(temp);
		temp = temp2;
	}
}

void salvareListaDenumire(nodArb* rad, nodLista** cap, char litera)
{
	if (rad != NULL)
	{
		if (rad->info.denumire[0] == litera)
			*cap = inserareLista(*cap, rad->info);
		salvareListaDenumire(rad->stanga, cap, litera);
		salvareListaDenumire(rad->dreapta, cap, litera);
	}
}

nodArb* rotatie_dreapta(nodArb* rad)
{
	printf("\nRotatie dreapta\n");
	nodArb* nod1 = rad->stanga;
	rad->stanga = nod1->dreapta;
	nod1->dreapta = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_stanga(nodArb* rad)
{
	printf("\nRotatie stanga\n");
	nodArb* nod1 = rad->dreapta;
	rad->dreapta = nod1->stanga;
	nod1->stanga = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_dreapta_stanga(nodArb* rad)
{
	printf("\nRotatie dreapta-stanga\n");
	nodArb* nod1 = rad->dreapta;
	nodArb* nod2 = nod1->stanga;
	nod1->stanga = nod2->dreapta;
	nod2->dreapta = nod1;
	rad->dreapta = nod2->stanga;
	nod2->stanga = rad;
	rad = nod2;
	return rad;
}

nodArb* rotatie_stanga_dreapta(nodArb* rad)
{
	printf("\nRotatie stanga-dreapta\n");
	nodArb* nod1 = rad->stanga;
	nodArb* nod2 = nod1->dreapta;
	nod1->dreapta = nod2->stanga;
	nod2->stanga = nod1;
	rad->stanga = nod2->dreapta;
	nod2->dreapta = rad;
	rad = nod2;
	return rad;
}

nodArb* reechilibrare(nodArb* rad)
{
	calculBF(rad);
	nodArb* stanga = rad->stanga;
	nodArb* dreapta = rad->dreapta;
	if (rad->BF <= -2 && stanga->BF <= -1)
	{
		rad = rotatie_dreapta(rad);
		calculBF(rad);
	}
	else
		if (rad->BF <= -2 && stanga->BF >= 1)
		{
			rad = rotatie_stanga_dreapta(rad);
			calculBF(rad);
		}
		else
			if (rad->BF >= 2 && dreapta->BF >= 1)
			{
				rad = rotatie_stanga(rad);
				calculBF(rad);
			}
			else
				if (rad->BF >= 2 && dreapta->BF <= -1)
				{
					rad = rotatie_dreapta_stanga(rad);
					calculBF(rad);
				}
	return rad;
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
		
		rad = reechilibrare(rad);
	}
	fclose(f);
	//calculBF(rad);
	

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

	printf("\nInaltime arbore: %d", inaltimeArbore(rad));

	int gradEchilibru = inaltimeArbore(rad->dreapta) -
		inaltimeArbore(rad->stanga);
	if (gradEchilibru <= 1 && gradEchilibru >= -1)
		printf("\nArbore echilibrat!");
	else
		printf("\nArbore neechilibrat!");

	//printf("\nDupa stergere:\n");
	//rad = stergeRad(rad);
	//preordine(rad);

	printf("\nDupa stergere:\n");
	rad = stergeNodRecursiv(rad, 99);
	//rad = stergeDupaDenumire(rad, "Pictor");
	//calculBF(rad);
	rad = reechilibrare(rad);
	preordine(rad);

	nodLista* cap = NULL;
	salvareListaDenumire(rad, &cap, 'A');
	traversareLista(cap);
	dezalocareLista(cap);

	dezalocare(rad);
}