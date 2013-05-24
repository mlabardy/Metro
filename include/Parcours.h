#ifndef PARCOURS_H
#define PARCOURS_H

#include <stdio.h>
#include <stdlib.h>
#include "Tableau.h"

#define INFINI 10000

typedef struct p {
	int stationAdj;
	char ligne;
	int tempsParcours;
	struct p * suivant;
} Parcours;

/* Cette fonction crée un parcours.  */
Parcours *creer_Parcours(int stationAdj, char ligne, int tempsParcours);

/* Cette fonction crée un tableau de parcours. */
Parcours **creer_Tab_Parcours(int taille);

/* Cette fonction ajoute dans une liste de parcours une nouvelle station. */
int ajouter_Parcours(Parcours **p, int stationAdj, char ligne, int tempsParcours);

/* Cette fonction libère un parcours. */
void liberer_Parcours(Parcours *p);

/* Cette fonction écrit un parcours sur la sortie souhaitée. */
void ecrire_Parcours(Parcours *p, FILE *sortie);

/* Cette fonction lit un parcours depuis une entree et le stocke dans le tableau de parcours. */
int lire_Parcours(Parcours **p, FILE *entree, int taille);

void lire_UnParcours(Parcours **p, FILE *entree);

/* Cette fonction libère le tableau de parcours . */
void liberer_Tab_Parcours(Parcours **p, int taille);

/* Cette fonction écrit un tableau de parcours sur la sortie. */
void ecrire_Tab_Parcours(Parcours **p, int taille, FILE *sortie);

int copier_ParcoursNonOriente(Parcours **origine, Parcours **destination, int taille);

/* Cette fonction effectue la transposée d'une matrice. */
int transposee(Parcours **m, Parcours **p, int taille); 

/* Cette fonction determine le valuation minimale dans le tableau de parcours et retourne la station associée. */
int min_Distances(Parcours **p, int* ensemble, int taille);

#endif