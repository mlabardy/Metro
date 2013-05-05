#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int totalStations;
	Parcours **p;
	Ligne *l;
	Correspondance *c;
} Metro;

typedef struct {
	int tempsParcours;
	char ligne;
} Parcours;

typedef struct {
	char numero;
	int *stations;
	int nbStations;
} Ligne;

typedef struct {
	int station;
	int nbLignes;
	int **correspondance;
	int *association;
} Correspondance;

#endif
