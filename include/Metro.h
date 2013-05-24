#ifndef METRO_H
#define METRO_H

#include <stdio.h>
#include <stdlib.h>
#include "Ligne.h"
#include "Parcours.h"
#include "Correspondance.h"

#define A_TEMPS 1
#define S_TEMPS 0

typedef struct {
	int nbStations;
	Parcours **p;
	Correspondance **c;
	char *lignes;
	int *nbAdj;
	Ligne **l;
	int nbLignes;
} Metro;

typedef struct {
	int *debut;
	int *fin;
	int heure;
} Pprofondeur;

/* Cette fonction alloue de la mémoire pour un métro. */
Metro *creer_Metro(int totalStations, int nbLignes);

/* Cette fonction lit sur son entrée un métro et le stocke dans la structure Metro. */
void lire_Metro(Metro **m, FILE *entree);

/* Cette fonction libère la mémoire allouée pour un métro. */
void liberer_Metro(Metro *m);

/* Cette fonction écrit sur la sortie un metro. */
void ecrire_Metro(Metro *m, FILE *sortie);

/* Cette fonction classe les stations dans leur ligne de métro respectif. */
void lire_Lignes(Metro **m);

/* Cette fonction effectue un parcours en profondeur sur toutes les lignes du métro. */
void parcoursProfondeurLigne(Metro **m, int station, Pprofondeur **p, char ligne, int *tmp1, int origine, int *tmp2, int *indice, int ligneC);

/* Cette fonction alloue la structure Pprofondeur. */
Pprofondeur *creer_Pprofondeur(int taille);

/* Cette fonction linère la mémoire allouée pour Pprofondeur. */
void liberer_Pprofondeur(Pprofondeur *p);

int verifierAdjLigne(Metro *m, int station, char ligne);

/* Cette fonction inverse l'ordre des stations si le premier terminus est supérieur au dernier. */
void ajusterTerminus(Metro *m);

/* Cette fonction détermine si un métro est eulérien, puis inscrit le resultat sur la sortie. */
int estEulerien(Metro *m, FILE *sortie);

/* Cette fonction écrit sur la sortie, les lignes de métro par lignes. */
void ecrire_Lignes(Metro *m, FILE *sortie);

/* Cette fonction effectue un parcours en profondeur à partir d'un sommet souhaité. */
void parcoursProfondeur(Parcours **m, int station, Pprofondeur **p, Parcours **liste, FILE *sortie);

/* Cette fonction met à jour le tableau de parcours, en y inserant les plus petites valuations en fonction de la station courante. */
void maj_Distances(Metro* m, Parcours **p, int origine, int type);

/* Cette fonction initialise le tableau de parcours. */
void initialiser_Distances(Metro *m, Parcours **p, int depart, int *ensemble);

/* Cette fonction affiche sur la sortie toutes les plus courtes distances depuis le depart vers toutes les autres stations. */
int PlusCourtesDistances(Metro* m, Parcours **p, FILE *sortie, int depart, int type);

/* Cette fonction ecrit le plus court chemin depuis une station depart vers les autres sommets successifs. */
void ecrire_PlusCourtChemin(Parcours **p, FILE *sortie, int i, int depart, int stationD, char ligneP, int stationS, int nbAdjD);

/* Cette fonction ecrit le plus court chemin depuis une station depart vers toutes les stations. */
void ecrire_PlusCourtsChemins(Parcours **p, FILE *sortie, int depart, int taille, int nbAdjD);

/* Cette fonction effectue un parcours en profondeur sur tout le graphe. */
void ExplorerProfondeur(Pprofondeur **p, Parcours **m, Parcours **liste, int taille, FILE *sortie);

/* Cette fontion determine les composantes fortements connexes de métro et les affiche sur la sortie. */
Parcours **composanteFConnexe(Metro *m);

#endif