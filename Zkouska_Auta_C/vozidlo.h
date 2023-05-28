#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produkt {
	char nazev[20];
	int pocet;
	struct tProdukt* dalsi;
}tProdukt;

typedef struct vozidlo {
	char nazev[20];
	int kapacita;
	int aktKapa;
	struct vozidlo* dalsiVozidlo;
	tProdukt* dalsiProdukt;
}tVozidlo;

tProdukt* vytvorProdukt(char* nazev, int pocet);

tVozidlo* vytvorVozidlo(char* nazev, int kapacita);

// funkce nacita do lin seznamu vozidla ze souboru vozidla.csv, kdy pro kazde aktualne nactene
// vozidlo nacita ze souboru produkty.csv jednotlive produkty
tVozidlo* nacti();

// fce vypise vozidla a jejich produkty
void vypis(tVozidlo* v);