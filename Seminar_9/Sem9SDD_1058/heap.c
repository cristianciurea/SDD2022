#include<stdio.h>
#include <malloc.h>

typedef struct
{
	int prioritate;
	char* denumire;
} activitate;

typedef struct 
{
	activitate* vect;
	int nrElem;
} heap;

void filtrare(heap h, int index)
{
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrElem && 
		h.vect[indexSt].prioritate > h.vect[indexRad].prioritate)
		indexRad = indexSt;
	if (indexDr < h.nrElem &&
		h.vect[indexDr].prioritate > h.vect[indexRad].prioritate)
		indexRad = indexDr;

	if (indexRad != index)
	{
		activitate temp = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = temp;

		filtrare(h, indexRad);
	}
}

heap inserare(heap h, activitate val)
{
	activitate* vectNou = (activitate*)malloc((h.nrElem + 1) * 
		sizeof(activitate));
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	vectNou[h.nrElem] = val;
	h.nrElem++;
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

heap extragere(heap h, activitate* val)
{
	activitate* vectNou = (activitate*)malloc((h.nrElem - 1) * 
		sizeof(activitate));
	activitate temp = h.vect[0];
	h.vect[0] = h.vect[h.nrElem - 1];
	h.vect[h.nrElem - 1] = temp;
	*val = h.vect[h.nrElem - 1];
	h.nrElem--;
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

void afisareHeap(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		printf("\n%d %s", h.vect[i].prioritate, h.vect[i].denumire);
	printf("\n");
}

void dezalocareHeap(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		free(h.vect[i].denumire);
	free(h.vect);
}

void main()
{
	heap h;
	FILE* f = fopen("fisier.txt", "r");
	//printf("Nr. elemente: ");
	fscanf(f, "%d", &h.nrElem);
	h.vect = (activitate*)malloc(h.nrElem * sizeof(activitate));
	char buffer[20];
	for (int i = 0; i < h.nrElem; i++)
	{
		//printf("Element %d: ", i);
		fscanf(f, "%d", &h.vect[i].prioritate);
		fscanf(f, "%s", buffer);
		h.vect[i].denumire = (char*)malloc((strlen(buffer) + 1) *
			sizeof(char));
		strcpy(h.vect[i].denumire, buffer);
	}
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	afisareHeap(h);

	activitate aNou;
	aNou.prioritate = 20;
	aNou.denumire = (char*)malloc((strlen("ceva") + 1) * sizeof(char));
	strcpy(aNou.denumire, "ceva");
	h = inserare(h, aNou);
	afisareHeap(h);

	activitate valExtras;
	h = extragere(h, &valExtras);
	printf("Valoarea extrasa: %d %s\n", valExtras.prioritate,
		valExtras.denumire);
	afisareHeap(h);

	activitate* vectSortat = (activitate*)malloc(h.nrElem * 
		sizeof(activitate));
	int nr = h.nrElem;
	for (int i = 0; i < nr; i++)
	{
		h = extragere(h, &valExtras);
		vectSortat[i] = valExtras;
	}
	printf("\nVector sortat: \n");
	for (int i = 0; i < nr; i++)
		printf("\n%d %s", vectSortat[i].prioritate, 
			vectSortat[i].denumire);
	free(vectSortat);

	dezalocareHeap(h);
}