#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct {
	int id;
	char* denumireAplicatie;
	int ora;
	int minut;
} notificare;

typedef struct {
	notificare info;
	struct nodStiva* next;
} nodStiva;

typedef struct {
	notificare info;
	struct nodCoada* next;
} nodCoada;

void put(nodCoada** prim, nodCoada** ultim, notificare n) {
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->info.id = n.id;
	nou->info.denumireAplicatie = (char*)malloc((strlen(n.denumireAplicatie) + 1) * sizeof(char));
	strcpy(nou->info.denumireAplicatie, n.denumireAplicatie);
	nou->info.ora = n.ora;
	nou->info.minut = n.minut;

	nou->next = NULL;
	if (*prim == NULL && *ultim == NULL) {
		*prim = nou;
		*ultim = nou;
	}
	else {
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

int get(nodCoada** prim, nodCoada** ultim, notificare* n) {
	if (*prim != NULL && *ultim != NULL) {
		(*n).id = (*prim)->info.id;
		(*n).denumireAplicatie = (char*)malloc((strlen((*prim)->info.denumireAplicatie) + 1) * sizeof(char));
		strcpy((*n).denumireAplicatie, (*prim)->info.denumireAplicatie);
		(*n).ora = (*prim)->info.ora;
		(*n).minut = (*prim)->info.minut;

		nodStiva* temp = *prim;
		*prim = (*prim)->next;

		free(temp->info.denumireAplicatie);
		free(temp);
		return 0;
	}
	else {
		if (*prim == NULL) {
			*ultim = NULL;
			return -1;
		}
	}
}

nodStiva* push(nodStiva* varf, notificare n) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->info.id = n.id;
	nou->info.denumireAplicatie = (char*)malloc((strlen(n.denumireAplicatie) + 1) * sizeof(char));
	strcpy(nou->info.denumireAplicatie, n.denumireAplicatie);
	nou->info.ora = n.ora;
	nou->info.minut = n.minut;

	nou->next = NULL;
	if (varf == NULL) {
		varf = nou;
	}
	else {
		nou->next = varf;
		varf = nou;
	}
	return varf;
}

int pop(nodStiva** varf, notificare* n) {
	if (*varf == NULL) {
		return -1;
	}
	else {
		(*n).id = (*varf)->info.id;
		(*n).denumireAplicatie = (char*)malloc((strlen((*varf)->info.denumireAplicatie) + 1) * sizeof(char));
		strcpy((*n).denumireAplicatie, (*varf)->info.denumireAplicatie);
		(*n).ora = (*varf)->info.ora;
		(*n).minut = (*varf)->info.minut;

		nodStiva* temp = *varf;
		*varf = (*varf)->next;

		free(temp->info.denumireAplicatie);
		free(temp);

		return 0;
	}
}

void afisare(nodStiva* varf) {
	nodStiva* temp = varf;
	while (temp) {
		printf("\nID = %d, Denumire aplicatie = %s, Ora = %d, Minut = %d", temp->info.id,
			temp->info.denumireAplicatie, temp->info.ora, temp->info.minut);
		temp = temp->next;
	}
}

void afisareCoada(nodCoada* prim) {
	nodCoada* temp = prim;
	while (temp) {
		printf("\nID = %d, Denumire aplicatie = %s, Ora = %d, Minut = %d", temp->info.id,
			temp->info.denumireAplicatie, temp->info.ora, temp->info.minut);
		temp = temp->next;
	}
}

void conversieStivaVector(nodStiva** varf, notificare* vect, int* nr) {
	notificare notif;
	while (pop(varf, &notif) == 0) {
		vect[*nr] = notif;
		(*nr)++;
	}
}

void main() {
	int nr; // nr de notificari
	nodStiva* varf = NULL;
	char buffer[20];
	notificare notif;
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++) {
		fscanf(f, "%d", &notif.id);
		fscanf(f, "%s", buffer);
		notif.denumireAplicatie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(notif.denumireAplicatie, buffer);
		fscanf(f, "%d", &notif.ora);
		fscanf(f, "%d", &notif.minut);
		varf = push(varf, notif);
		put(&prim, &ultim, notif);
		free(notif.denumireAplicatie);
	}
	fclose(f);
	printf("Stiva:");
	afisare(varf);
	printf("\nCoada:");
	afisareCoada(prim);

	notificare* vect = (notificare*)malloc(nr * sizeof(notificare));
	int nrConv = 0;

	/*printf("\nConversie:");
	conversieStivaVector(&varf, vect, &nrConv);
	for (int i = 0; i < nrConv; i++) {
		printf("\nID = %d, Denumire aplicatie = %s, Ora = %d, Minut = %d", vect[i].id,
			vect[i].denumireAplicatie, vect[i].ora, vect[i].minut);
	}
	for (int i = 0; i < nrConv; i++) {
		free(vect[i].denumireAplicatie);
	}
	free(vect);*/

	while (get(&prim, &ultim, &notif) == 0) {
		free(notif.denumireAplicatie);
	}
}