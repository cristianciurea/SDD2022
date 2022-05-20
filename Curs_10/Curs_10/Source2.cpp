#include <stdio.h>
#include <iostream>
#include <fstream>
#define GRAD_ARBORE 4
#define MAX_CHEI 2*GRAD_ARBORE
using namespace std;

const int DA = 1;
const int NU = 0;

struct NodArboreB
{
	int chei[MAX_CHEI];
	int NrChei;
	NodArboreB* NodParinte;
	NodArboreB* NodFiu[MAX_CHEI + 1];
};

//functie pentru a localiza pozitia unei valori in lista de chei a unui nod
int pozitieCheie(NodArboreB* NodCurent, int ValCheie)
{
	int nrCheiNod = NodCurent->NrChei;
	for (int i = 0; i < nrCheiNod; i++)
		if (ValCheie < NodCurent->chei[i])
			return i;
	return nrCheiNod; //noua cheie are cea mai mare valoare
}

// functie pentru a cauta o cheie intr-un arbore B
// daca gaseste valoarea intoarce Nodgasit si pozCheie in acel nod
// daca nu gaseste valoarea intoarce Nodgasit = NULL si pozCheie = -1
void cautaValoare(NodArboreB*& NodStart, int ValCheie, NodArboreB*& NodGasit, int& pozCheie)
{
	int i;
	if (NodStart)
	{
		int nrCheiNod = NodStart->NrChei;
		if ((ValCheie < NodStart->chei[0]) && (ValCheie > NodStart->chei[nrCheiNod - 1]))
			if ((NodStart->NodFiu[0] == NULL) && (NodStart->NodFiu[nrCheiNod]))
			{
				printf("\n Cheie inexistenta!");
				return;
			}
		for (i = 0; i < nrCheiNod; i++)
			if (ValCheie == NodStart->chei[i])
			{
				NodGasit = NodStart;
				pozCheie = i;
				return;
			}
		pozCheie = pozitieCheie(NodStart, ValCheie);
		if ((ValCheie < NodStart->chei[i]) && (NodStart->NodFiu[i] != NULL))
			cautaValoare(NodStart->NodFiu[i], ValCheie, NodGasit, pozCheie);
		if ((ValCheie > NodStart->chei[i - 1]) && (NodStart->NodFiu[i] != NULL))
			cautaValoare(NodStart->NodFiu[i], ValCheie, NodGasit, pozCheie);
	}
	else {
		NodGasit = NULL;
		pozCheie = -1;
	}
};

// functie pentru a sparge un nod NodSpart in 2 construind un nou nod NodNou la stanga sa
// primeste noua cheie, pozitia acesteia in nod si legatura catre fiu stanga de pe acea pozitie
int SpargeNod(NodArboreB* NodSpart, NodArboreB* NodNou, NodArboreB* NodFiuStanga, int ValCheieNoua, int pozCheieNoua)
{
	int i = 0, j = 0;
	int inserareElementMijloc = NU;
	int cheieMijloc;
	//se construieste noul nod stanga si se insereaza in acesta si noua cheie daca este cazul
	while (i < GRAD_ARBORE)
	{
		if ((inserareElementMijloc == NU) && (j == pozCheieNoua))
		{
			NodNou->chei[i] = ValCheieNoua;
			NodNou->NodFiu[i] = NodFiuStanga;
			++i;
			inserareElementMijloc = DA;
		}
		else
		{
			NodNou->chei[i] = NodSpart->chei[j];
			NodNou->NodFiu[i] = NodSpart->NodFiu[j];
			++i;
			++j;
		}
	}
	//se determina inregistrarea din mijloc si se verifica daca acesta nu este chiar noua cheie
	if ((inserareElementMijloc == NU) && (j == pozCheieNoua))
	{
		cheieMijloc = ValCheieNoua;
		NodNou->NodFiu[i] = NodFiuStanga;
		inserareElementMijloc = DA;
	}
	else
	{
		cheieMijloc = NodSpart->chei[j];
		NodNou->NodFiu[i] = NodSpart->NodFiu[j];
		++j;
	}
	// se reinitializeaza legaturile catre parinte
	if (NodNou->NodFiu[0] != NULL)
		for (i = 0; i <= GRAD_ARBORE; i++)
			NodNou->NodFiu[i]->NodParinte = NodNou;
	// se reinitializeaza nodul din dreapta (nodul existent) si se insereaza noua cheie daca este cazul
	i = 0;
	while (i < GRAD_ARBORE)
	{
		if ((inserareElementMijloc == NU) && (j == pozCheieNoua))
		{
			NodSpart->chei[i] = ValCheieNoua;
			NodSpart->NodFiu[i] = NodFiuStanga;
			++i;
			inserareElementMijloc = DA;
		}
		else
		{
			NodSpart->chei[i] = NodSpart->chei[j];
			NodSpart->NodFiu[i] = NodSpart->NodFiu[j];
			++i;
			++j;
		}
	}
	NodSpart->NodFiu[i] = NodSpart->NodFiu[j];
	// se reinitializeaza legaturile catre parinte
	if (NodSpart->NodFiu[0] != NULL)
		for (i = 0; i < GRAD_ARBORE; i++)
			NodSpart->NodFiu[i]->NodParinte = NodSpart;
	return cheieMijloc;
}

// functie pentru adaugarea unei noi chei int-un nod
// daca arborele este vid atunci creeaza o noua radacina
// daca un nod devine plin, inainte de a se face inserarea este spart in 2
void AdaugaCheieNod(NodArboreB*& NodInserare, NodArboreB* NodFiuStanga, NodArboreB* NodFiuDreapta, int ValCheieNoua, NodArboreB*& NodRadacina)
{
	NodArboreB* NodNou;
	int cheieMijloc;
	int pozCheieNoua, i, nrCheiNod;
	//daca nodul nu exista se construieste un nou nod radacina
	if (NodInserare == NULL)
	{
		NodNou = new NodArboreB;
		NodNou->chei[0] = ValCheieNoua;
		NodNou->NodFiu[0] = NodFiuStanga;
		NodNou->NodFiu[1] = NodFiuDreapta;
		NodNou->NodParinte = NULL;
		if ((NodFiuDreapta != NULL) && (NodFiuStanga != NULL))
		{
			NodFiuStanga->NodParinte = NodNou;
			NodFiuDreapta->NodParinte = NodNou;
		}
		NodNou->NrChei = 1;
		NodRadacina = NodNou;
		return;
	}
	pozCheieNoua = pozitieCheie(NodInserare, ValCheieNoua);
	if (NodInserare->NrChei < MAX_CHEI)
	{
		//inserare cheie noua
		nrCheiNod = NodInserare->NrChei;
		//se muta legaturile catre dreapta incepand cu pozitia noii chei
		NodInserare->NodFiu[nrCheiNod + 1] = NodInserare->NodFiu[nrCheiNod];
		for (i = nrCheiNod; i > pozCheieNoua; i--)
		{
			NodInserare->NodFiu[i] = NodInserare->NodFiu[i - 1];
			NodInserare->chei[i] = NodInserare->chei[i - 1];
		}
		NodInserare->chei[pozCheieNoua] = ValCheieNoua;
		NodInserare->NodFiu[pozCheieNoua] = NodFiuStanga;
		NodInserare->NodFiu[pozCheieNoua + 1] = NodFiuDreapta;
		NodInserare->NrChei += 1;
	}
	else
		//se sparge nodul in 2
	{
		NodNou = new NodArboreB;
		NodNou->NodParinte = NodInserare->NodParinte;
		NodNou->NrChei = GRAD_ARBORE;
		NodInserare->NrChei = GRAD_ARBORE;
		cheieMijloc = SpargeNod(NodInserare, NodNou, NodFiuStanga, ValCheieNoua, pozCheieNoua);
		AdaugaCheieNod(NodInserare->NodParinte, NodNou, NodInserare, cheieMijloc, NodRadacina);
	}
}

//adauga o noua cheie in arborele B
void AdaugaCheieArbore(int ValCheieNoua, NodArboreB*& NodRadacina)
{
	NodArboreB* nodArbore;
	int i, NrCheiNod, pozCheie;
	cautaValoare(NodRadacina, ValCheieNoua, nodArbore, pozCheie);
	nodArbore = NodRadacina;
	while (nodArbore != NULL)
	{
		NrCheiNod = nodArbore->NrChei;
		i = 0;
		while (i<NrCheiNod && ValCheieNoua>nodArbore->chei[i])
			++i;
		if (nodArbore->NodFiu[i] != NULL)
			nodArbore = nodArbore->NodFiu[i];
		else
			break;
	}
	AdaugaCheieNod(nodArbore, NULL, NULL, ValCheieNoua, NodRadacina);
}

void main()
{
	NodArboreB* radacina = NULL;
	NodArboreB* nodArb = NULL;
	int n, val, pozCheie, valg;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &val);
		AdaugaCheieArbore(val, radacina);
	}
	fclose(f);

	printf("Valoare de gasit=");
	scanf("%d", &valg);
	cautaValoare(radacina, valg, nodArb, pozCheie);
	if (nodArb != NULL)
		printf("Pozitie=%d, Nr.chei=%d, Valoare=%d", pozCheie, nodArb->NrChei, nodArb->chei[pozCheie]);
	else
		printf("\n Cheia nu exista!");

	printf("\nValoare de gasit=");
	scanf("%d", &valg);
	cautaValoare(radacina, valg, nodArb, pozCheie);
	if (nodArb != NULL)
		printf("Pozitie=%d, Nr.chei=%d, Valoare=%d", pozCheie, nodArb->NrChei, nodArb->chei[pozCheie]);
	else
		printf("\n Cheia nu exista!");

	printf("\nValoare de gasit=");
	scanf("%d", &valg);
	cautaValoare(radacina, valg, nodArb, pozCheie);
	if (nodArb != NULL)
		printf("Pozitie=%d, Nr.chei=%d, Valoare=%d", pozCheie, nodArb->NrChei, nodArb->chei[pozCheie]);
	else
		printf("\n Cheia nu exista!");
}
