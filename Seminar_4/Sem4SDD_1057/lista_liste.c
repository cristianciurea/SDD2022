#include<stdio.h>
#include <malloc.h>

typedef struct
{
	int capacitateMotor;
	char* marca;
	char* motorizare;
} masina;

typedef struct
{
	masina inf;
	struct nodLS* next;
} nodLS;

typedef struct
{
	struct nodLS* inf;
	struct nodLP* next;
} nodLP;

void inserareLS(nodLS** cap, masina m)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.capacitateMotor = m.capacitateMotor;
	nou->inf.marca = (char*)malloc((strlen(m.marca) + 1) * 
		sizeof(char));
	strcpy(nou->inf.marca, m.marca);
	nou->inf.motorizare = (char*)malloc((strlen(m.motorizare) + 1) *
		sizeof(char));
	strcpy(nou->inf.motorizare, m.motorizare);
	nou->next = NULL;
	if (*cap == NULL)
		*cap = nou;
	else
	{
		nodLS* temp = *cap;
		while (temp->next != NULL)
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
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
}

void traversareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		printf("\nMarca = %s, Capacitate motor = %d, Motorizare = %s",
			temp->inf.marca, temp->inf.capacitateMotor, temp->inf.motorizare);
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
	while (temp)
	{
		nodLS* temp2 = temp->next;
		free(temp->inf.marca);
		free(temp->inf.motorizare);
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodLP* cap)
{
	nodLP* temp = cap;
	while (temp)
	{
		nodLP* temp2 = temp->next;
		dezalocareLS(temp->inf);
		free(temp);
		temp = temp2;
	}
}

void main()
{
	nodLP* capLP = NULL;
	nodLS* capLS1 = NULL, * capLS2 = NULL, * capLS3 = NULL;
	int n;
	char buffer[20];
	masina m;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &m.capacitateMotor);
		fscanf(f, "%s", buffer);
		m.marca = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(m.marca, buffer);
		fscanf(f, "%s", buffer);
		m.motorizare = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(m.motorizare, buffer);

		if (strcmp(m.motorizare, "BENZINA") == 0)
			inserareLS(&capLS1, m);
		else
			if (strcmp(m.motorizare, "HYBRID") == 0)
				inserareLS(&capLS2, m);
			else
				if (strcmp(m.motorizare, "ELECTRIC") == 0)
					inserareLS(&capLS3, m);
	}
	fclose(f);

	inserareLP(&capLP, capLS1);
	inserareLP(&capLP, capLS2);
	inserareLP(&capLP, capLS3);

	traversareLP(capLP);
	dezalocareLP(capLP);
}