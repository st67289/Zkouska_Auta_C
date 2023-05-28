#include "vozidlo.h"

tProdukt* vytvorProdukt(char* nazev, int pocet) {
	tProdukt* produkt = (tProdukt*)malloc(sizeof(tProdukt));
	strcpy(produkt->nazev, nazev, sizeof(nazev) - 1);
	produkt->pocet = pocet;
	produkt->dalsi = NULL;
	return produkt;
}

tVozidlo* vytvorVozidlo(char* nazev, int kapacita) {
	tVozidlo* vozidlo = (tVozidlo*)malloc(sizeof(tVozidlo));
	strcpy(vozidlo->nazev, nazev, sizeof(nazev) - 1);
	vozidlo->aktKapa = 0;
	vozidlo->kapacita = kapacita;
	vozidlo->dalsiVozidlo = NULL;
	vozidlo->dalsiProdukt = NULL;

	return vozidlo;
}

tVozidlo* nacti() {
	FILE* fileV = fopen("vozidla.csv", "r");
	if (fileV == NULL)
	{
		printf("Chyba pri otevirani souboru vozidla.csv");
		return NULL;
	}
	FILE* fileP = fopen("produkty.csv", "r");
	if (fileP == NULL)
	{
		printf("Chyba pri otevirani souboru produkty.csv");
		return NULL;
	}

	char lineV[1024];
	char lineP[1024];

	//read headers from files
	fgets(lineV, 1024, fileV);
	fgets(lineP, 1024, fileP);

	tVozidlo* prvniV = NULL;
	tProdukt* prvniP = NULL;
	tProdukt* zbylyP = NULL;
	tVozidlo* aktualniV = NULL;
	
	// read vozidla
	while (fgets(lineV, 1024, fileV) != NULL)
	{
		
		char nazevV[20];
		int kapacita;
		strcpy(nazevV, strtok(lineV, ";"));
		kapacita = atoi(strtok(NULL, ";"));
		tVozidlo* voz = vytvorVozidlo(nazevV, kapacita);
		
		// kdyz je zbyly produkt tak ho narvu hned od auta kdyz se vejde
		if (zbylyP != NULL) {
			if (voz->kapacita <= zbylyP->pocet)
			{
			zbylyP->dalsi = prvniP;
			voz->dalsiProdukt = zbylyP;
			voz->aktKapa += zbylyP->pocet;
			zbylyP = NULL;
			}
			
		}

		// read lines from produkty.csv
		while (fgets(lineP, 1024, fileP) != NULL)
		{
			char nazevP[20];
			int pocet;

			strcpy(nazevP, strtok(lineP, ";"));
			pocet = atoi(strtok(NULL, ";"));
			// new produkt
			tProdukt* prod = vytvorProdukt(nazevP, pocet);

			// jestli se produkt vejde
			if ((voz->kapacita - voz->aktKapa) >= prod->pocet)
			{
				// kdyz je list produktu ve voze NULL
				if (voz->dalsiProdukt == NULL)
				{
					voz->dalsiProdukt = prod;
				}
				// kdyz neni tak vlozim produkt na prvni misto listu
				else {
					tProdukt* prvni = voz->dalsiProdukt;
					prod->dalsi = prvni;
					voz->dalsiProdukt = prod;
				}
				// zvetsi aktulani kapacitu vozu
				voz->aktKapa += prod->pocet;
				
			}
			// kdyz se nevejde zbylyP bude ten produkt ktery se nevejde a break pro while
			else {
				zbylyP = prod;
				break;
			}
		}

		// kdyz je prvni vuz null tzn prazdny list
		if (prvniV == NULL) {
			prvniV = voz;
			aktualniV = voz;
		}
		// kdyz neni prazdny list
		// projedu list dokud nenajdu posledni 
		// za posledni vlozim vuz aktualni
		else {
			aktualniV = prvniV;
			while (aktualniV->dalsiVozidlo != NULL)
			{
				aktualniV = aktualniV->dalsiVozidlo;
			}
			aktualniV->dalsiVozidlo = voz;
		}
	}
	fclose(fileV);
	fclose(fileP);
	return prvniV;
}

void vypis(tVozidlo* v) {
	while (v != NULL) {
		printf("auto: %s kap:%d aktKap:%d\n", v->nazev, v->kapacita, v->aktKapa);
		tProdukt* p = v->dalsiProdukt;
		while (p != NULL) {
			printf("%s %d\n", p->nazev, p->pocet);
			p = p->dalsi;
		}
		printf("-------------------\n");
		v = v->dalsiVozidlo;
	}
}


