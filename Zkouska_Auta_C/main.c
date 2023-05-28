#include "vozidlo.h"
int main() {
	tVozidlo* vozidla = nacti();
	vypis(vozidla);
	free(vozidla);
	return 0;
}