#include "Correspondance.h"

/*
typedef struct {
	int station;
	int nbLignes;
	int **correspondance;
	int *association;
} Correspondance;
*/

/**
 * Cette fonction crée une correspondance.
 * \param		station, la station de départ. 
 * \param		nbLignes, le nombre de ligne de métro.
 * \return 		c, la nouvelle correspondance en cas de succès.
 * \return 		NULL, en cas d'erreur.
 */
Correspondance *creer_Correspondance(int station, int nbLignes) {
	Correspondance *c = NULL;
	int i, j;
	c = (Correspondance*)calloc(1, sizeof(Correspondance));
	if (c == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de correspondance\n");
		return NULL;
	}
	c->correspondance = (int**)calloc(nbLignes, sizeof(int*));
	if (c->correspondance == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de c->correspondance\n");
		free(c);
		c = NULL;
		return NULL;
	}
	for (i=0 ; i<nbLignes ; i++) {
		c->correspondance[i] = (int*)calloc(nbLignes, sizeof(int));
		if (c->correspondance[i] == NULL) {
			fprintf(stderr, "Une erreur est survenue lors de l'allocation de c->correspondance[i]\n");
			for (j=0 ; j<i; j++) {
				free(c->correspondance[j]);
				c->correspondance[j] = NULL;
			}
			free(c->correspondance);
			c->correspondance = NULL;
			free(c);
			c = NULL;
			return NULL;
		}
	}
	c->association = (int*)calloc(nbLignes, sizeof(int));
	if (c->association == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de c->association\n");
		for (j=0 ; j<nbLignes; j++) {
			free(c->correspondance[j]);
			c->correspondance[j] = NULL;
		}
		free(c->correspondance);
		c->correspondance = NULL;
		free(c);
		c = NULL;
		return NULL;
	}
	c->nbLignes = nbLignes;
	c->station = station;
	return c;
}

/**
 * Cette fonction désalloue la mémoire allouée pour une correspondance.
 * \param		c, une correspondance.
 */
void liberer_Correspondance(Correspondance *c) {
	int j;
	if (c != NULL) {
		if (c->correspondance != NULL) {
			for (j=0 ; j<c->nbLignes; j++) {
				free(c->correspondance[j]);
				c->correspondance[j] = NULL;
			}
			free(c->correspondance);
			c->correspondance = NULL;
		}
		if (c->association != NULL) {
			free(c->association);
			c->association = NULL;
		}
		free(c);
		c = NULL;
	}
}

void ajouter_Ligne_Correspondance(Correspondance *c, char ligne, int position) {
	c->association[position] = ligne;
}

void ecrire_association_Correspondance(Correspondance *c, FILE *sortie) {
	int i;
	for (i=0 ; i<c->nbLignes ; i++) {
		fprintf(sortie, "%c ", c->association[i]);
	}
	fprintf(sortie, "\n");
}
/*
void ajouter_Correspondance(Correspondance **c, char origine, char destination, int tempsCorresp) {
	if ((*c) == NULL) {
		fprintf(stderr, "Erreur\n");
		return;
	}
	(*c)->correspondance[origine][destination] = 
}*/