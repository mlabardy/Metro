#include "Correspondance.h"

/**
 * Cette fonction crée une correspondance.
 * \param		station, la station de départ. 
 * \param		nbLignes, le nombre de ligne de métro.
 * \return 		c, la nouvelle correspondance en cas de succès.
 * \return 		NULL, en cas d'erreur.
 */
Correspondance *creer_Correspondance(int nbLignes, int nbStations) {
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
	c->nbLignes = nbLignes;
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
		free(c);
		c = NULL;
	}
}

/**
 * Cette fonction crée un tableau de correspondances.
 * \param       taille, le nombre de correspondances.
 * \return      le tableau de correspondance, en cas de succès.
 * \return      NULL, en cas d'erreurs.
 */
Correspondance **creer_Tab_Correspondance(int taille) {
	Correspondance **c = NULL;
	if (taille <= 0) {
		fprintf(stderr, "La taille de 'correspondance[]' est invalide \n");
		return NULL;
	}
	c = (Correspondance**)calloc(taille, sizeof(Correspondance*));
	if (c == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de 'correspondance[]'\n");
		return NULL;
	}
	return c;
}

/**
 * Cette fonction désalloue la mémoire allouée pour une correspondance.
 * \param		c, une correspondance.
 */
void liberer_Tab_Correspondance(Correspondance **c, int taille) {
	int j;
	if (c != NULL) {
		for (j=0 ; j<taille ; j++) {
			liberer_Correspondance(c[j]);	
		}
		free(c);
		c = NULL;
	}
}

/**
 *
 *//*
void ajouter_Ligne(char ligne, char *lignes, int nbLignes) {
	int i = 0;
	if (nbLignes <= 0) {
		fprintf(stderr, "la taille lignes[] est invalide\n");
		return;
	}
	while (i<nbLignes) {
		if (lignes[i] == ligne) {
			return;
		}
		if (lignes[i] == 0) {
			lignes[i] = ligne;
			return;
		}
		i++;
	}
}
*/
/**
 * Cette fonction permet d'afficher sur la sortie, l
 *//*
void ecrire_association_Correspondance(int nbLignes, char *lignes, FILE *sortie) {
	int i;
	for (i=0 ; i<nbLignes ; i++) {
		fprintf(sortie, "%c ", lignes[i]);
	}
	fprintf(sortie, "\n");
}*/

/**
 * Cette fonction ajoute le temps de changement de lignes entre deux lignes.
 * \param       c, la correspondance concernée.
 * \param       origine, la ligne d'arrivée.
 * \param       destination, la ligne de sortie.
 * \param       tempsCorresp, le temps de changemenst entre les deux lignes.
 * \param       lignes, le tableau de lignes.
 */
void ajouter_Correspondance(Correspondance *c, char origine, char destination, int tempsCorresp, char *lignes) {
	int i, x, y, tmp = 0;
	if (c == NULL) {
		fprintf(stderr, "Erreur\n");
		return;
	}
	for (i=0 ; i<c->nbLignes ; i++) {
		if (tmp != 2) {
			if (lignes[i] == origine) {
				x = i;
				tmp++;
			}
			else if (lignes[i] == destination) {
				y = i;
				tmp++;
			}
		}
		else 
			break;
	}
	c->correspondance[x][y] = tempsCorresp;
}

/**
 * Cette fonction affiche sur la sortie une correspondance.
 * \param       c, une correspondance à afficher.
 * \param       sortie, la sortie pour l'affichage.
 */
void ecrire_Correspondance(Correspondance *c, FILE *sortie) {
	int i, j;
	for (i=0 ; i<c->nbLignes ; i++) {
		for (j=0 ; j<c->nbLignes ; j++) {
			fprintf(sortie, "%d ", c->correspondance[i][j]);
		}
		fprintf(sortie, "\n");
	}
	fprintf(sortie, "\n");
} 

/**
 * Cette fonction lit une correspondance depuis une entrée, et stocke ces informations dans la structure Correspondance
 * \param       c, une correspondance à modifier.
 * \param       entree, l'entrée pour la lecture de la correspondance.
 * \param       ligneD, la ligne à insérer.
 * \param       lignes, le tableau contenant les lignes metro, il permet de faire d'associer une ligne à un indice.
 * \param       nbLignes, le nombre total de lignes.
 * \return      -1 en cas d'erreurs.
 * \return      0 en cas de succès.
 */
int lire_Correspondance(Correspondance **c, FILE *entree, char ligneD, char *lignes, int nbLignes) {
	char tmp[10], tmp2[4];
	char ligneA;
	int taille = 0, tempsCorresp = 0, i, j;
	if (lignes == NULL) {
		fprintf(stderr, "Le tableau lignes[] est vide\n");
		return -1;
	}
	ajouter_Ligne(ligneD, lignes, nbLignes);
	fscanf(entree, "%s", tmp);
	taille = atoi(tmp);
	if (taille == 0) {
		return -1;
	}
	while (taille != 0) {
		if ((*c) == NULL) {
			(*c) = creer_Correspondance(nbLignes, nbLignes);
			if ((*c) == NULL) {
				return -1;
			}
		}
		fscanf(entree, "%s", tmp);
		ligneA = tmp[1];
		ajouter_Ligne(ligneA, lignes, nbLignes);
		i = 3;
		j = 0;
		reinitialiser_Chaine(tmp2, taille);
		while (tmp[i] != ')') {
			tmp2[j] = tmp[i];
			i++;
			j++;
		}
		tmp2[j] = '\0';
		tempsCorresp = atoi(tmp2);
		ajouter_Correspondance((*c), ligneD, ligneA, tempsCorresp, lignes);
		taille--;
	}
	return 0;
}
