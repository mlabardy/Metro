#include "Parcours.h"

/**
 * Cette fonction crée un parcours. 
 * \param		tempsParcours, le temps de parcours entre entre stations de métro.
 * \param		ligne, la ligne de métro reliant deux stations de métro.
 * \param		stationAdj, la station à atteindre.  
 * \return 		p, le nouveau parcours.
 */
Parcours *creer_Parcours(int stationAdj, char ligne, int tempsParcours) {
	Parcours *p = NULL;
	p = (Parcours*)calloc(1, sizeof(Parcours));
	if (p == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de 'parcours'\n");
		return NULL;
	}
	p->stationAdj = stationAdj;
	p->ligne = ligne;
	p->tempsParcours = tempsParcours;
	p->suivant = NULL;
	return p;
}

/**
 * Cette fonction crée un tableau de parcours. 
 * \param		taille, la taille du tableau de parcours.  
 * \return 		p, le nouveau tableau parcours.
 */
Parcours **creer_Tab_Parcours(int taille) {
	Parcours **p = NULL;
	if (taille <= 0) {
		fprintf(stderr, "La taille pour l'allocation de 'parcours[]'\n");
		return NULL;
	}
	p = (Parcours**)calloc(taille, sizeof(Parcours*));
	if (p == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de 'parcours[]'\n");
		return NULL;
	}
	return p;
}

/**
 * Cette fonction ajoute dans une liste de parcours une nouvelle station.
 * \param		p, la liste de parcours à 
 * \param		stationAdj, la nouvelle station adjacente à rajouter. 
 * \param		ligne, la ligne par laquelle est atteinte la stataion adjacente. 
 * \param		tempsParcours, le temps pour atteindre la station adjacente. 
 * \return		1, en cas de succès. 
 * \return		0, en cas d'echec. 
 */
int ajouter_Parcours(Parcours **p, int stationAdj, char ligne, int tempsParcours) {
	Parcours *tmp;
	tmp = creer_Parcours(stationAdj, ligne, tempsParcours);
	if ((*p) == NULL) {
		(*p) = tmp;
		if ((*p) == NULL)
			return -1;
	}
	else {
		tmp->suivant = (*p);
		(*p) = tmp;
	}
	return 0;
}

/**
 * Cette fonction libère un parcours. 
 * \param		p, un parcours.
 */
void liberer_Parcours(Parcours *p) {
	Parcours *tmp;
	if (p != NULL) {
		while (p != NULL) {
			tmp = p;
			p = tmp->suivant;
			free(tmp);
		}
	}
}

/**
 * Cette fonction libère le tableau de parcours .
 * \param		p, un tableau de parcours.
 * \param		taille, le nombre de stations.
 */
void liberer_Tab_Parcours(Parcours **p, int taille) {
	int i;
	if (p != NULL) {
		for (i=0 ; i<taille ; ++i) {
			liberer_Parcours(p[i]);
		}
		free(p);
		p = NULL;
	}
}

/**
 * Cette fonction écrit un parcours sur la sortie souhaitée.
 * \param		p, un parcours.
 * \param		sortie, un descripteur sur la sortie. 
 */
void ecrire_Parcours(Parcours *p, FILE *sortie) {
	if (p != NULL) {
		while (p != NULL) {
			fprintf(sortie, "%d ", p->stationAdj);
			p = p->suivant;
		}
	}
	fprintf(sortie, "\n");
}

/**
 * Cette fonction lit un parcours depuis une entree et le stocke dans le tableau de parcours.
 * \param		p, le tableau de parcours.
 * \param		entree, l'entrée pour la lecture du parcours.
 * \param		taille, la taille du tableau de parcours.
 * \return 		0 en cas de succès.
 * \return 		-1 en cas d'erreur de taille.
 * \return 		-2 en cas d'erreur d'allocation.
 */
int lire_Parcours(Parcours **p, FILE *entree, int taille) {
	int stationAdj, tempsParcours, i, j, compteur = 1;
	char ligne, tmp[10], tmp2[4];
	if (taille == 0)
		return -2;
	while (taille != 0) {
		fscanf(entree, "%s", tmp);
		if (tmp[0] == '(') {
			i = 0;
			compteur = 1;
			while (tmp[i] != ')') {
				switch (compteur) {
					case 1:
						i++;
						j = 0;
						reinitialiser_Chaine(tmp2, 4);
						while (tmp[i] != ',' && tmp[i] != ')') {
							tmp2[j] = tmp[i];
							j++;
							i++;
						}
						tmp2[j] = '\0';
						stationAdj = atoi(tmp2);
					break;
					case 2:
						ligne = tmp[i];
						i++;
					break;
					case 3:
						j = 0;
						reinitialiser_Chaine(tmp2, 4);
						while (tmp[i] != ',' && tmp[i] != ')') {
							tmp2[j] = tmp[i];
							j++;
							i++;
						}
						i -= 2;
						tmp2[j] = '\0';
						tempsParcours = atoi(tmp2);
					break;
				}
				compteur++;
				i++;
			}
		}
		taille--;
		if (-1 == (ajouter_Parcours(p, stationAdj, ligne, tempsParcours))) {
			liberer_Parcours(*p);
			return -1;
		}
	}
	return 0;
}

/**
 * Cette fonction écrit un tableau de parcours sur la sortie.
 * \param		p, le tableau de parcours.
 * \param		sortie, un descripteur sur la sortie.
 * \param		taille, la taille du tableau de parcours.
 */
void ecrire_Tab_Parcours(Parcours **p, int taille, FILE *sortie) {
	int i;
	for (i=0 ; i<taille ; ++i) {
		ecrire_Parcours(p[i], sortie);
	}
}

/**
 * Cette fonction effectue la transposée d'une matrice.
 * \param		p, le tableau de parcours destination.
 * \param		m, le tableau de parcours origine.
 * \param		taille, la taille du tableau de parcours.
 * \return 		0 en cas de succès.
 * \return 		-1 en cas d'erreur.
 */
int transposee(Parcours **m, Parcours **p, int taille) {
	int i, station;
	Parcours *tmp = NULL;
	if (p == NULL) {
		return -1;
	}
	for (i=0 ; i<taille ; ++i) {
		tmp = m[i];
		while (tmp != NULL) {
			station = tmp->stationAdj;
			ajouter_Parcours(&p[station], i, tmp->ligne, tmp->tempsParcours);
			tmp = tmp->suivant;
		}
	}
	/return 0;
}

/**
 * Cette fonction transforme un graphe orienté en graphe non orienté.
 * \param		destination, le tableau de parcours destination.
 * \param		origine, le tableau de parcours origine.
 * \param		taille, la taille du tableau de parcours.
 * \return 		0 en cas de succès.
 * \return 		-1 en cas d'erreur. 
 */
int copier_ParcoursNonOriente(Parcours **origine, Parcours **destination, int taille) {
	int i, station;
	Parcours *tmp = NULL;
	if (destination == NULL) {
		return -1;
	}
	for (i=0 ; i<taille ; ++i) {
		tmp = origine[i];
		while (tmp != NULL) {
			station = tmp->stationAdj;
			ajouter_Parcours(&destination[station], i, tmp->ligne, tmp->tempsParcours);
			tmp = tmp->suivant;
		}
	}
	return 0;
}

/**
 * Cette fonction determine la valuation minimale dans le tableau de parcours et retourne la station associée.
 * \param		p, tableau de stations.
 * \param		ensemble, un tableau indiquant l'ensemble des stations déjà visités.
 * \param		taille, le nombre de stations.
 * \return 		la station ayant la valuation minimale. 
 */
int min_Distances(Parcours **p, int* ensemble, int taille) {
	int i, indice = 0, min = INFINI;
	for(i=0 ; i<taille ; ++i) {	
		if (min > p[i]->tempsParcours && ensemble[i] == 0) {
			min = p[i]->tempsParcours;
			indice = i;
		}
	}
	ensemble[indice] = 1;
	return indice;
}
