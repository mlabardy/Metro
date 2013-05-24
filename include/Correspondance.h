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

/*  */
void ajouter_Ligne(char ligne, char *lignes, int nbLignes);

void ajouter_Correspondance(Correspondance *c, char origine, char destination, int tempsCorresp, char *lignes);

void ecrire_association_Correspondance(int nbLignes, char *lignes, FILE *sortie);

void ecrire_Correspondance(Correspondance *c, FILE *sortie);

int lire_Correspondance(Correspondance **c, FILE *entree, char ligneD, char *lignes, int nbLignes);

void liberer_Tab_Correspondance(Correspondance **c, int taille);

Correspondance **creer_Tab_Correspondance(int taille);

#endif
