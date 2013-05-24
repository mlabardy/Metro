#include "Ligne.h"

/**
 * Cette fonction alloue une structure pour stocker les éléments d'une ligne de métro.
 * \param       numero, le nom de la ligne.
 * \param       nbStation, le nombre de stations présents dans la ligne.
 * \return      la nouvelle ligne, en cas de succès.
 * \return      NULL, en cas d'erreur.
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
 * Cette fonction crée un tableau de lignes.
 * \param       taille, le nombre de lignes.
 * \return      le tableau de ligne, en cas de succès.
 * \return      NULL, en cas d'erreur.
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
 * Cette fonction libère le tableau de lignes alloué.
 * \param       l, le tableau de lignes.
 * \param       taille, le nombre de lignes.
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
 * \param		sortie, un déscripteur sur la sortie. 
 */
void ecrire_Ligne(Ligne *l, FILE *sortie) {
	int i;
	fprintf(sortie, "Ligne %c :  ", l->numero);	
	for (i=0 ; i<l->longueur ; i++) {
		fprintf(sortie, "%d ", l->stations[i]);	
	}
	fprintf(sortie, "\n");
}
