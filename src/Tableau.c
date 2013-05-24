#include "Tableau.h"

/**
 *
 */
void reinitialiser_Chaine(char *chaine, int taille) {
	int i;
	for (i=0 ; i<taille ; i++) {
		chaine[i] = '\0';
	}
} 

/**
 *
 */
char *creer_Chaine(int taille) {
	char *chaine = NULL;
	if (taille <= 0) {
		fprintf(stderr, "La taille de 'chaine[]' est invalide \n");
		return NULL;
	}
	chaine = (char*)calloc(taille, sizeof(char));
	if (chaine == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de 'chaine[]'\n");
	}
	return chaine;
}

/**
 *
 */
void liberer_Chaine(char *chaine) {
	free(chaine);
	chaine = NULL;
}

/**
 *
 */
int *creer_Tableau(int taille) {
	int *tab = NULL;
	if (taille <= 0) {
		fprintf(stderr, "La taille de 'tab[]' est invalide \n");
		return NULL;
	}
	tab = (int*)calloc(taille, sizeof(int));
	if (tab == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de 'tab[]'\n");
	}
	return tab;
}

/**
 *
 */
void liberer_Tableau(int *tab) {
	free(tab);
	tab = NULL;
}

/**
 *
 */
void ecrire_Tableau(int *tab, int taille, FILE *sortie) {
	int i;
	for (i=0 ; i<taille ; ++i) {
		fprintf(sortie, " %d -> %d \n", i,tab[i]);
	}
	fprintf(sortie, "\n");
}

int **creer_Matrice(int taille) {
	int i, j;
	int **matrice = (int**)calloc(taille, sizeof(int*));
	if (matrice == NULL) {
		return NULL;
	}
	for (i=0 ; i <taille ; ++i) {
		matrice[i] = (int*)calloc(taille, sizeof(int));
		if (matrice[i] == NULL) {
			for (j=0 ; j<i ; ++j) {
				free(matrice[j]);
				matrice[j] = NULL;
			}
			free(matrice);
			matrice = NULL;
			return NULL;
		}
	}
	return matrice;
}

void liberer_Matrice(int **matrice, int taille) {
	int i;
	for (i=0 ; i <taille ; ++i) {
		free(matrice[i]);
		matrice[i] = NULL;
	}
	free(matrice);
	matrice = NULL;
}