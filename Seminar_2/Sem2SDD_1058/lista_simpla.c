#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>

//lista simpla
typedef struct {
	int nrMatricol;
	char* nume;
	float medie;

}student;

typedef struct {

	student inf;
	struct nodLs* next;

}nodLs;

nodLs* inserare(nodLs* cap, student s) {
	//alocam spatiu ptr nod
	nodLs* nou = (nodLs*)malloc(sizeof(nodLs));
	//initializare info utila

	//nou->inf = s; nu e ok(shallow copy ptr nume)
	nou->inf.nrMatricol = s.nrMatricol;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;

	//initializare pointer de legatura
	nou->next = NULL;
	if (cap == NULL)
	{
		cap = nou;
	}
	else
	{
		//inseram la final
		nodLs* aux = cap;
		while (aux->next != NULL)
		{
			aux = aux->next;
		}
		aux->next = nou;
	}
	return cap;
}

void traversare(nodLs* cap) {

	nodLs* aux = cap;
	while (aux != NULL)//parcurgere si ultimul nod
	{
		printf("\nNr. matricol=%d, nume=%s , medie=%5.2f", aux->inf.nrMatricol, aux->inf.nume, aux->inf.medie);
		aux = aux->next;
	}
}

void dezalocare(nodLs* cap) {

	nodLs* aux = cap;
	while (aux != NULL)
	{
		nodLs* urmator = aux->next;
		free(aux->inf.nume);
		free(aux);
		aux = urmator;
	}
}
void main()
{
	int n;//nr stud
	//printf("Nr studenti: ");
	//scanf("%d", &n);
	nodLs* cap = NULL;
	student s;
	char buffer[20];
	/*for (int i = 0; i < n; i++) {
		printf("Nr. matricol: ");
		scanf("%d", &s.nrMatricol);
		printf("Nume: ");
		scanf("%s",buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		printf("Medie: ");
		scanf("%f", &s.medie);
		cap = inserare(cap, s);
		free(s.nume);

	}*/
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);

	for (int i = 0; i < n; i++) {

		fscanf(f, "%d", &s.nrMatricol);

		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);

		fscanf(f, "%f", &s.medie);
		cap = inserare(cap, s);
		free(s.nume);

	}
	fclose(f);
	traversare(cap);
	dezalocare(cap);



}