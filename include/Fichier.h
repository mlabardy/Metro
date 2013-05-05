#ifndef FICHIER_H
#define FICHIER_H

#include <stdio.h>
#include <stdlib.h>

/* Cette fonction ouvre un fichier selon le mode. */
void ouvrirFichier(FILE**fichier, char* nomFichier, char* mode);

/* Cette fonction ferme un fichier. */
void fermerFichier(FILE* fichier);

#endif
