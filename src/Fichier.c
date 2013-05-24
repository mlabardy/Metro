#include "Fichier.h"

/**
 * Cette fonction ouvre un fichier selon le mode et initialise le descripteur 'fichier' 
 * \param 		fichier (un pointeur de type FILE).
 * \param		nomFichier (le nom du fichier à ouvrir).
 * \param		mode, mode pour le descripteur de fichier.
 */
void ouvrirFichier(FILE**fichier, char* nomFichier, char* mode) {
	(*fichier) = fopen(nomFichier, mode);
	if ((*fichier) == NULL) {
		fprintf(stderr, "Une erreur est survenue à l'ouverture du fichier '%s'\n", nomFichier);
	}
}

/**
 * Cette fonction ferme un fichier et réinitialise le descripteur du fichier.
 * \param 		fichier (un pointeur de type FILE, sur le fichier actuellement ouvert).
 */
void fermerFichier(FILE* fichier) {
	if (fichier != NULL) {
		fclose(fichier);
		fichier = NULL;
	}
}
