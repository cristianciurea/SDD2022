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

nodStiva* push(nodStiva* varf, notificare n) {
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->info.id = n.id;
	nou->info.denumireAplicatie = (char*)malloc((strlen(n.denumireAplicatie)+1) * sizeof(char));
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

void main() {
	int nr; // nr de notificari
	nodStiva* varf = NULL;
	char buffer[20];
	notificare notif;
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
		free(notif.denumireAplicatie);
	}
	fclose(f);
	afisare(varf);
	while (pop(&varf, &notif) == 0) {
		free(notif.denumireAplicatie);
	}
}