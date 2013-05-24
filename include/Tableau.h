#ifndef TABLEAU_H
#define TABLEAU_H

#include <stdio.h>
#include <stdlib.h>

/*  */
void reinitialiser_Chaine(char *chaine, int taille);

/*  */
char *creer_Chaine(int taille);

/*  */
void liberer_Chaine(char *chaine);

/*  */
int *creer_Tableau(int taille);

/*  */
void liberer_Tableau(int *tab);

/*  */
void ecrire_Tableau(int *tab, int taille, FILE *sortie);

/*  */
int **creer_Matrice(int taille);

/*  */
void liberer_Matrice(int **matrice, int taille);

#endif