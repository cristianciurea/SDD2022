#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct {
	int nrMatricol;
	char* nume;
	float medie;
} student;

typedef struct {
	student inf;
	struct nodls* prev;
	struct nodls* next;
} nodls;

nodls* inserare(nodls* cap, nodls** coada, student s) {
	// alocam spatiu
	nodls* nou = (nodls*)malloc(sizeof(nodls));

	// initializare info utila
	// nou->inf = s; nu e ok (SHALLOW COPY PENTRU NUME)
	nou->inf.nrMatricol = s.nrMatricol;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;

	// initializare pointer de legatura
	nou->next = NULL;
	nou->prev = NULL;

	if (cap == NULL) {
		cap = nou;
		*coada = nou;
	}
	else {
		// inseram la final
		nodls* aux = cap;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = nou;
		nou->prev = aux;
		*coada = nou;
	}

	return cap;
}

void traversare(nodls* cap) {
	nodls* aux = cap;
	// pentru a parcurge si ultimul nod
	while (aux != NULL) {
		printf("\nNr. matricol=%d, nume=%s, medie=%5.2f", aux->inf.nrMatricol, aux->inf.nume, aux->inf.medie);
		aux = aux->next;
	}
}

void traversareInversa(nodls* coada) {
	nodls* aux = coada;
	// pentru a parcurge si ultimul nod
	while (aux != NULL) {
		printf("\nNr. matricol=%d, nume=%s, medie=%5.2f", aux->inf.nrMatricol, aux->inf.nume, aux->inf.medie);
		aux = aux->prev;
	}
}

void dezalocare(nodls* cap) {
	nodls* aux = cap;
	while (aux != NULL) {
		nodls* urmator = aux->next;
		free(aux->inf.nume);
		free(aux);
		aux = urmator;
	}
}

void main() {
	int n; // nr de studenti
	//printf("Nr. studenti: ");
	//scanf("%d", &n);

	nodls* cap = NULL;
	nodls* coada = NULL;

	student s;
	char buffer[20];
	/*for (int i = 0; i < n; i++) {
		printf("Nr. matricol: ");
		scanf("%d", &s.nrMatricol);

		printf("Nume: ");
		scanf("%s", buffer);
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

		cap = inserare(cap, &coada, s);

		free(s.nume);
	}

	fclose(f);

	printf("Traversare lista dubla:");
	traversare(cap);

	printf("\n\nTraversare inversa lista dubla:");
	traversareInversa(coada);
	dezalocare(cap);
}