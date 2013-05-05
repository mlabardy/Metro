#include "Main.h"

int main (int argc, char **argv) {
	/*Ligne l = creer_Ligne('a', 5);
	ecrire_Ligne(l, stdout);
	liberer_Ligne(l);*/
	/*Ligne *l = creer_Ligne('a', 5);
	ecrire_Ligne(l, stdout);
	liberer_Ligne(l);*/

/*
	Parcours p = creer_Parcours(2, 'a');
	ecrire_Parcours(p, stdout);
	exit(EXIT_SUCCESS);
*/
/*
	Correspondance *c = creer_Correspondance(2, 5);
	liberer_Correspondance(c);
*/

	Metro * m = NULL;
	FILE* f;
	ouvrirFichier(&f, "Metro", "r");
	lire_Metro(&m, f);
	fermerFichier(f);
	liberer_Metro(m);
	exit(EXIT_SUCCESS);
}