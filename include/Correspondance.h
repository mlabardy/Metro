#ifndef CORRESPONDANCE_H
#define CORRESPONDANCE_H

#include <stdio.h>
#include <stdlib.h>
#include "Tableau.h"

typedef struct {
	int nbLignes;
	int **correspondance;
	int nbStations;
} Correspondance;

/* Cette fonction crée une correspondance. */
Correspondance *creer_Correspondance(int nbLignes, int nbStations);

/* Cette fonction désalloue la mémoire allouée pour une correspondance. */
void liberer_Correspondance(Correspondance *c);

/* Cette fonction permet d'ajouter une ligne de métro dans le tableau de lignes. */
void ajouter_Ligne(char ligne, char *lignes, int nbLignes);

/* Cette fonction ajoute le temps de changement de lignes entre deux lignes. */
void ajouter_Correspondance(Correspondance *c, char origine, char destination, int tempsCorresp, char *lignes);

/* Cette fonction affiche sur la sortie une correspondance. */
void ecrire_Correspondance(Correspondance *c, FILE *sortie);

/* Cette fonction lit une correspondance depuis une entrée, et stocke ces informations dans la structure Correspondance. */
int lire_Correspondance(Correspondance **c, FILE *entree, char ligneD, char *lignes, int nbLignes);

/* Cette fonction désalloue la mémoire allouée pour une correspondance. */
void liberer_Tab_Correspondance(Correspondance **c, int taille);

/* Cette fonction crée un tableau de correspondances. */
Correspondance **creer_Tab_Correspondance(int taille);

#endif
