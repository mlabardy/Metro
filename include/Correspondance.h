#ifndef CORRESPONDANCE_H
#define CORRESPONDANCE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int station;
	int nbLignes;
	int **correspondance;
	int *association;
} Correspondance;

/* Cette fonction crée une correspondance. */
Correspondance *creer_Correspondance(int station, int nbLignes);

/* Cette fonction désalloue la mémoire allouée pour une correspondance. */
void liberer_Correspondance(Correspondance *c);

void ajouter_Ligne_Correspondance(Correspondance *c, char ligne, int position);

void ecrire_association_Correspondance(Correspondance *c, FILE *sortie);

#endif