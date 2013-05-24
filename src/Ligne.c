#include "Ligne.h"

/**
 *
 */
Ligne *creer_Ligne(char numero, int nbStations) {
	Ligne *l = (Ligne*)malloc(sizeof(Ligne));
	if (l == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de la ligne\n");
		return NULL;
	}
	l->numero = numero;
	l->longueur = 0;
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
 *
 */
Ligne **creer_Tab_Ligne(int taille) {
	Ligne **l = NULL;
	if (taille <= 0) {
		fprintf(stderr, "La taille de 'ligne[]' est invalide\n");
		return NULL;
	}
	l = (Ligne**)calloc(taille, sizeof(Ligne*));
	if (l == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de 'ligne[]'\n");
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
 *
 */
void liberer_Tab_Ligne(Ligne **l, int taille) {
	int i;
	if (l != NULL) {
		for (i=0 ; i<taille ; ++i) {
			liberer_Ligne(l[i]);
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
	fprintf(sortie, "Ligne %c :  ", l->numero);	
	for (i=0 ; i<l->longueur ; i++) {
		fprintf(sortie, "%d ", l->stations[i]);	
	}
	fprintf(sortie, "\n");
}