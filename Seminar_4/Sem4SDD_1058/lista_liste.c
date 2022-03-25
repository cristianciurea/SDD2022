#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* denumire;
	float pret;
	char* categorie;
} produs;

typedef struct
{
	produs inf;
	struct nodLS* next;
} nodLS;

typedef struct
{
	struct nodLS* inf;
	struct nodLP* next;
} nodLP;

void inserareLS(nodLS** capLS, produs p)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.categorie = (char*)malloc((strlen(p.categorie) + 1) * sizeof(char));
	strcpy(nou->inf.categorie, p.categorie);
	nou->next = NULL;
	if (*capLS == NULL)
		*capLS = nou;
	else
	{
		nodLS* temp = *capLS;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}


void inserareLP(nodLP** capLP, nodLS* capLS)
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->inf = capLS;
	nou->next = NULL;
	if (*capLP == NULL)
		*capLP = nou;
	else
	{
		nodLP* temp = *capLP;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void traversareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		printf("\nCod = %d, Denumire = %s, Pret = %5.2f, Categorie = %s",
			temp->inf.cod, temp->inf.denumire, temp->inf.pret, temp->inf.categorie);
		temp = temp->next;
	}
}

void traversareLP(nodLP* cap)
{
	nodLP* temp = cap;
	int i = 1;
	while (temp != NULL)
	{
		printf("\nSublista: %d", i);
		traversareLS(temp->inf);
		temp = temp->next;
		i++;
	}
}

void dezalocareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		nodLS* temp2 = temp->next;
		free(temp->inf.denumire);
		free(temp->inf.categorie);
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodLP* cap)
{
	nodLP* temp = cap;
	while (temp != NULL)
	{
		nodLP* temp2 = temp->next;
		dezalocareLS(temp->inf);
		free(temp);
		temp = temp2;
	}
}

void main()
{
	int n;
	nodLS* capLS1 = NULL, * capLS2 = NULL, * capLS3 = NULL;
	nodLP* capLP = NULL;
	produs p;
	char buffer[20];

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);
		fscanf(f, "%f", &p.pret);
		fscanf(f, "%s", buffer);
		p.categorie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.categorie, buffer);

		if (strcmp(p.categorie, "lactate") == 0)
			inserareLS(&capLS1, p);
		else
			if (strcmp(p.categorie, "panificatie") == 0)
				inserareLS(&capLS2, p);
			else
				if (strcmp(p.categorie, "bauturi") == 0)
					inserareLS(&capLS3, p);

		free(p.denumire);
		free(p.categorie);
	}
	fclose(f);

	inserareLP(&capLP, capLS1);
	inserareLP(&capLP, capLS2);
	inserareLP(&capLP, capLS3);

	traversareLP(capLP);
	dezalocareLP(capLP);
}

