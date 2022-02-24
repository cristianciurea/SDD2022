#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int *cod;
	char* den;
	float pret;
	float cant;
} produs;

void citireVector(produs* vp, int n)
{
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("Cod=");
		vp[i].cod = (int*)malloc(1 * sizeof(int));
		scanf("%d", vp[i].cod);
		printf("Denumire=");
		scanf("%s", buffer);
		vp[i].den = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(vp[i].den, buffer);
		printf("Pret=");
		scanf("%f", &vp[i].pret);
		printf("Cant=");
		scanf("%f", &vp[i].cant);
	}
}

void citire4Vectori(int *coduri, char **denumiri, float* preturi, float *cantitati, int n)
{
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("Cod=");
		scanf("%d", &coduri[i]);
		printf("Denumire=");
		scanf("%s", buffer);
		denumiri[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(denumiri[i], buffer);
		printf("Pret=");
		scanf("%f", &preturi[i]);
		printf("Cant=");
		scanf("%f", &cantitati[i]);
	}
}

void afisareVector(produs* vp, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("Cod = %d", *(vp[i].cod));
		printf(", Denumire = %s", vp[i].den);
		printf(", Pret = %5.2f", vp[i].pret);
		printf(", Cant = %5.2f", vp[i].cant);
		printf("\n");
	}
}

void afisare4Vectori(int* coduri, char** denumiri, float* preturi, float* cantitati, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("Cod = %d", coduri[i]);
		printf(", Denumire = %s", denumiri[i]);
		printf(", Pret = %5.2f", preturi[i]);
		printf(", Cant = %5.2f", cantitati[i]);
		printf("\n");
	}
}

void dezalocareVector(produs* vp, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(vp[i].cod);
		free(vp[i].den);
	}
	free(vp);
}

void dezalocare4Vector(int* coduri, char** denumiri, float* preturi, float* cantitati, int n)
{
	for (int i = 0; i < n; i++)
		free(denumiri[i]);
	free(denumiri);
	free(coduri);
	free(preturi);
	free(cantitati);
}

void citireMatrice(float** mat, char** denumiri, int n)
{
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("Denumire=");
		scanf("%s", buffer);
		denumiri[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(denumiri[i], buffer);
		for (int j = 0; j < 3; j++)
		{
			printf("mat[%d][%d]=", i, j);
			scanf("%f", &mat[i][j]);
		}
	}
}

void afisareMatrice(float** mat, char **denumiri, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("Denumire = %s  ", denumiri[i]);
		for (int j = 0; j < 3; j++)
			printf("%5.2f  ", mat[i][j]);
		printf("\n");
	}
}

void dezalocareMatrice(float** mat, char** denumiri, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(denumiri[i]);
		free(mat[i]);
	}
	free(mat);
	free(denumiri);
}

float sumaProduseVector(produs *vp, int n)
{
	float suma = 0.0f;
	for (int i = 0; i < n; i++)
		suma += vp[i].pret * vp[i].cant;
	return suma;
}

float sumaProduse4Vectori(int* coduri, char** denumiri, float* preturi, float* cantitati, int n)
{
	float suma = 0.0f;
	for (int i = 0; i < n; i++)
		suma += preturi[i] * cantitati[i];
	return suma;
}

float sumaProduseMatrice(float** mat, int n)
{
	float suma = 0.0f;
	for (int i = 0; i < n; i++)
		suma += mat[i][1] * mat[i][2];
	return suma;
}

void main()
{
	int n;
	printf("Nr. produse: ");
	scanf("%d", &n);
	produs* vp = (produs*)malloc(n * sizeof(produs));
	citireVector(vp, n);
	afisareVector(vp, n);
	dezalocareVector(vp, n);
	/*int* coduri = (int*)malloc(n * sizeof(int));
	char** denumiri = (char**)malloc(n * sizeof(char*));
	float* preturi = (float*)malloc(n * sizeof(float));
	float* cantitati = (float*)malloc(n * sizeof(float));
	citire4Vectori(coduri, denumiri, preturi, cantitati, n);
	afisare4Vectori(coduri, denumiri, preturi, cantitati, n);
	dezalocare4Vector(coduri, denumiri, preturi, cantitati, n);*/

	/*char** denumiri = (char**)malloc(n * sizeof(char*));
	float** mat = (float**)malloc(n * sizeof(float*));
	for (int i = 0; i < n; i++)
		mat[i] = (float*)malloc(3 * sizeof(float));
	citireMatrice(mat, denumiri, n);
	afisareMatrice(mat, denumiri, n);

	printf("Suma totala produse: %5.2f", sumaProduseMatrice(mat, n));

	dezalocareMatrice(mat, denumiri, n);*/
}