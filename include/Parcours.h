#ifndef PARCOURS_H
#define PARCOURS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int tempsParcours;
	char ligne;
} Parcours;

/* Cette fonction crée un parcours. */
Parcours creer_Parcours(int tempsParcours, char ligne);

/* Cette fonction écrit un parcours sur la sortie souhaitée. */
void ecrire_Parcours(Parcours p, FILE *sortie);

#endif