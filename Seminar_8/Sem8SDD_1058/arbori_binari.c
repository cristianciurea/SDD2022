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

typedef struct
{
	Persoana inf;
	struct nodLista* next;
} nodLista;

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

nodArb* stergeRad(nodArb* rad)
{
	nodArb* aux = rad;
	if (rad->stanga != NULL)
	{
		rad = aux->stanga;
		if (aux->dreapta != NULL)
		{
			nodArb* temp = aux->stanga;
			while (temp->dreapta != NULL)
			{
				temp = temp->dreapta;
			}
			temp->dreapta = aux->dreapta;
		}
	}
	else
		if (aux->dreapta != NULL)
			rad = aux->dreapta;
		else
			rad = NULL;
	free(aux->inf.nume);
	free(aux);
	return rad;
}

nodArb* stergeNodIterativ(nodArb* rad, int cheie)
{
	if (rad == NULL)
		return NULL;
	else
		if (rad->inf.anNastere == cheie)
		{
			rad = stergeRad(rad);
			return rad;
		}
		else
		{
			nodArb* aux = rad;
			while (1)
			{
				if (cheie < aux->inf.anNastere)
					if (aux->stanga == NULL)
						break;
					else
					{
						nodArb* st = aux->stanga;
						if (st->inf.anNastere == cheie)
						{
							aux->stanga = stergeRad(aux->stanga);
						}
						else
							aux = aux->stanga;
					}
				else
					if (cheie > aux->inf.anNastere)
						if (aux->dreapta == NULL)
							break;
						else
						{
							nodArb* dr = aux->dreapta;
							if (dr->inf.anNastere == cheie)
							{
								aux->dreapta = stergeRad(aux->dreapta);
							}
							else
								aux = aux->dreapta;
						}
			}
			return rad;
		}
}

nodArb* stergeNodRecursiv(nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie < rad->inf.anNastere)
			rad->stanga = stergeNodRecursiv(rad->stanga, cheie);
		else
			if (cheie > rad->inf.anNastere)
				rad->dreapta = stergeNodRecursiv(rad->dreapta, cheie);
			else
				rad = stergeRad(rad);
		return rad;
	}
	else
		return NULL;
}

nodArb* stergeDupaNume(nodArb* rad, char* nume)
{
	if (rad != NULL)
	{
		if (strcmp(rad->inf.nume, nume) == 0)
		{
			rad = stergeNodRecursiv(rad, rad->inf.anNastere);
			return rad;
		}
		else
		{
			rad->stanga = stergeDupaNume(rad->stanga, nume);
			rad->dreapta = stergeDupaNume(rad->dreapta, nume);
			return rad;
		}
	}
	else
		return NULL;
}

nodLista* inserareLista(nodLista* cap, Persoana p)
{
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->inf.anNastere = p.anNastere;
	nou->inf.nume = (char*)malloc((strlen(p.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, p.nume);
	nou->inf.sex = p.sex;
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
		printf("\nAn nastere = %d, Nume = %s, Sex = %c",
			temp->inf.anNastere, temp->inf.nume, temp->inf.sex);
		temp = temp->next;
	}
}

void dezalocareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		nodLista* temp2 = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = temp2;
	}
}

void salvareListaLiteraG(nodArb* rad, nodLista** cap)
{
	if (rad != NULL)
	{
		if (rad->inf.nume[0] == 'G')
			*cap = inserareLista(*cap, rad->inf);
		salvareListaLiteraG(rad->stanga, cap);
		salvareListaLiteraG(rad->dreapta, cap);
	}
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

	int gradEchilibru = inaltimeArbore(rad->dreapta) - 
		inaltimeArbore(rad->stanga);
	if (gradEchilibru >= -1 && gradEchilibru <= 1)
		printf("\nArborele este echilibrat!");
	else
		printf("\nArborele nu este echilibrat!");

	//rad = stergeRad(rad);
	//rad = stergeNodIterativ(rad, 1990);
	//rad = stergeNodRecursiv(rad, 1985);
	//rad = stergeDupaNume(rad, "Gigel");
	//traversarePreordine(rad);

	nodLista* cap = NULL;
	salvareListaLiteraG(rad, &cap);
	traversareLista(cap);
	dezalocareLista(cap);

	dezalocare(rad);

}