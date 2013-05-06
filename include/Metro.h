#ifndef METRO_H
#define METRO_H

#include <stdio.h>
#include <stdlib.h>
#include "Ligne.h"
#include "Parcours.h"
#include "Correspondance.h"

typedef struct {
	int totalStations;
	int nbCorresp;
	Parcours **p;
	Ligne **l;
	Correspondance **c;
} Metro;

Metro *creer_Metro(int totalStations, int nbLignes);
void liberer_Metro(Metro *m);
void lire_Metro(Metro **m, FILE *entree);

#endif