#include "Ligne.h"
/*
Ligne creer_Ligne(char numero, int nbStations) {
	Ligne l;
	l.nbStations = nbStations;
	l.numero = numero;
	l.stations = (int*)calloc(nbStations, sizeof(int));
	if (l.stations == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de ligne.stations\n");
		exit(EXIT_FAILURE);
	}
	return l;
}

void liberer_Ligne(Ligne l) {
	if (l.stations != NULL) {
		free(l.stations);
		l.stations = NULL;
	}
}

void ecrire_Ligne(Ligne l, FILE *sortie) {
	int i;
	for (i=0 ; i<l.nbStations ; i++) {
		fprintf(sortie, "%d ", l.stations[i]);	
	}
	fprintf(sortie, "\n");
}
*/
/**
 * Cette fonction crée une ligne de métro.
 * Ses stations sont initialisées à 0.
 * \param		numero, le numéro de la ligne.
 * \param		nbStations, le nombre de stations dans la ligne.
 * \return 		l, la nouvelle ligne de métro en cas de succès.
 * \return 		NULL, en cas d'erreur.
 */
Ligne *creer_Ligne(char numero, int nbStations) {
	Ligne *l = (Ligne*)malloc(sizeof(Ligne));
	if (l == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de la ligne\n");
		return NULL;
	}
	l->nbStations = nbStations;
	l->numero = numero;
	l->stations = (int*)calloc(nbStations, sizeof(int));
	if (l->stations == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de ligne.stations\n");
		free(l);
		l = NULL;
		return NULL;
	}
	return l;
}

/**
 * Cette fonction désalloue une ligne de métro.
 * Le tableau de stations est d'abord libéré puis la ligne est désallouée.
 * \param		l, la ligne à libérer.
 */
void liberer_Ligne(Ligne *l) {
	if (l != NULL) {
		if (l->stations != NULL) {
			free(l->stations);
			l->stations = NULL;
		}
		free(l);
		l = NULL;
	}
}

/**
 * Cette fonction écrit, sur la sortie souhaitée, une ligne de métro.
 * \param		l, la ligne de métro.
 * \param		sortie, un déscripteur.
 */
void ecrire_Ligne(Ligne *l, FILE *sortie) {
	int i;
	fprintf(sortie, "Ligne : %c ", l->numero);	
	for (i=0 ; i<l->nbStations ; i++) {
		fprintf(sortie, "%d ", l->stations[i]);	
	}
	fprintf(sortie, "\n");
}