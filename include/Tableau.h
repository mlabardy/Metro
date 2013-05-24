#ifndef TABLEAU_H
#define TABLEAU_H

#include <stdio.h>
#include <stdlib.h>

/* Cette fonction réinitialise une chaîne en l'a remplissant de '\0'. */
void reinitialiser_Chaine(char *chaine, int taille);

/* Cette fonction crée une chaîne de caractères. */
char *creer_Chaine(int taille);

/* Cette fonction libère la mémoire allouée pour une chaîne de caractères. */
void liberer_Chaine(char *chaine);

/* Cette fonction crée un tableau d'entiers. */
int *creer_Tableau(int taille);

/* Cette fonction libère la mémoire allouée pour la tableau d'entiers. */
void liberer_Tableau(int *tab);

/* Cette fonction écrit sur la sortie, un tableau d'entiers. */
void ecrire_Tableau(int *tab, int taille, FILE *sortie);

/* Cette fonction crée une matrice carré d'entiers. */
int **creer_Matrice(int taille);

/* Cette fonction libère la mémoire allouée pour une matrice. */
void liberer_Matrice(int **matrice, int taille);

#endif
