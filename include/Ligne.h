#ifndef LIGNE_H
#define LIGNE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char numero;
	int *stations;
	int longueur;
} Ligne;

/* Cette fonction crée une ligne de métro. */
Ligne *creer_Ligne(char numero, int nbStations);

/* Cette fonction alloue une structure pour stocker les éléments d'une ligne de métro. */
Ligne **creer_Tab_Ligne(int taille);

/* Cette fonction désalloue une ligne de métro. */
void liberer_Ligne(Ligne *l);

/* Cette fonction écrit, sur la sortie souhaitée, une ligne de métro. */
void ecrire_Ligne(Ligne *l, FILE *sortie);

/* Cette fonction libère le tableau de lignes alloué. */
void liberer_Tab_Ligne(Ligne **l, int taille);

#endif
