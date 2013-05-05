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

#endif