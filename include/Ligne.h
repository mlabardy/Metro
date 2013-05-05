#ifndef LIGNE_H
#define LIGNE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char numero;
	int *stations;
	int nbStations;
} Ligne;
/*
Ligne creer_Ligne(char numero, int nbStations);

void liberer_Ligne(Ligne l);

void ecrire_Ligne(Ligne l, FILE *sortie);
*/
/* Cette fonction crée une ligne de métro. */
Ligne *creer_Ligne(char numero, int nbStations);
 
/* Cette fonction désalloue une ligne de métro. */
void liberer_Ligne(Ligne *l);

/* Cette fonction écrit, sur la sortie souhaitée, une ligne de métro. */
void ecrire_Ligne(Ligne *l, FILE *sortie);

#endif