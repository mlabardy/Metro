#include "Parcours.h"

/**
 * Cette fonction crée un parcours. 
 * \param		tempsParcours, le temps de parcours entre entre stations de métro.
 * \param		ligne, la ligne de métro reliant deux stations de métro.
 * \return 		p, le nouveau parcours.
 */
Parcours creer_Parcours(int tempsParcours, char ligne) {
	Parcours p;
	p.tempsParcours = tempsParcours;
	p.ligne = ligne;
	return p;
}

/**
 * Cette fonction écrit un parcours sur la sortie souhaitée.
 * \param		p, un parcours.
 * \param		sortie, un descripteur. 
 */
void ecrire_Parcours(Parcours p, FILE *sortie) {
	fprintf(sortie, "%d %c 	 \n", p.tempsParcours, p.ligne);
}