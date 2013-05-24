#include "Tableau.h"

/**
 * Cette fonction réinitialise une chaîne en l'a remplissant de '\0'.
 * \param       chaine, une chaîne de caractères.
 * \param       taille, la taille de la chaîne de caractères. 
 */
void reinitialiser_Chaine(char *chaine, int taille) {
	int i;
	for (i=0 ; i<taille ; i++) {
		chaine[i] = '\0';
	}
} 

/**
 * Cette fonction crée une chaîne de caractères.
 * \param       taille, la taille de la nouvelle chaîne de caractères.
 * \return      la nouvelle chaîne de caractères, en cas de succès.
 * \return      NULL,  en cas d'erreurs. 
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
 * Cette fonction libère la mémoire allouée pour une chaîne de caractères.
 * \param       chaine, une chaîne de caractères.
 */
void liberer_Chaine(char *chaine) {
	free(chaine);
	chaine = NULL;
}

/**
 * Cette fonction crée un tableau d'entiers.
 * \param       taille, la taille du tableau.
 * \return      le nouveau tableau, en cas de succès.
 * \return      NULL, en cas d'erreurs.
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
 * Cette fonction libère la mémoire allouée pour la tableau d'entiers.
 * \param       tab, le tableau à libérer.s
 */
void liberer_Tableau(int *tab) {
	free(tab);
	tab = NULL;
}

/**
 * Cette fonction écrit sur la sortie, un tableau d'entiers.
 * \param       tab, un tableau d'entiers.
 * \param       taille, la taille du tableau.
 * \param       sortie, un déscripteur sur la sortie.
 */
void ecrire_Tableau(int *tab, int taille, FILE *sortie) {
	int i;
	for (i=0 ; i<taille ; ++i) {
		fprintf(sortie, " %d -> %d \n", i,tab[i]);
	}
	fprintf(sortie, "\n");
}

/**
 * Cette fonction crée une matrice carré d'entiers.
 * \param       taille, les dimensions de la matrice.
 * \return      une matrice, en cas de succès.
 * \return      NULL, en cas d'erreurs. 
 */
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

/**
 * Cette fonction libère la mémoire allouée pour une matrice.
 * \param       matrice, la matrice à libérer.
 * \param       taille, la taille de la matrice.
 */
void liberer_Matrice(int **matrice, int taille) {
	int i;
	for (i=0 ; i <taille ; ++i) {
		free(matrice[i]);
		matrice[i] = NULL;
	}
	free(matrice);
	matrice = NULL;
}
