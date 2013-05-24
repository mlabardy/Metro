#include <string.h>
#include "Metro.h"

/**
 * Cette fonction alloue de la mémoire pour un métro.
 * \param 		nbStations, le nombre de stations dans le métro.
 * \param		lignes, le nombre de lignes dans le métro.
 * \return 		NULL, en cas d'echec.
 * \return 		m, un nouveau métro en cas de succès.
 */
Metro *creer_Metro(int nbStations, int lignes) {
	Metro *m = (Metro*)calloc(1, sizeof(Metro));
	if (m == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de 'metro'\n");
		return NULL;
	}
	m->nbStations = nbStations;
	m->nbLignes = lignes;
	m->p = creer_Tab_Parcours(m->nbStations);
	if (m->p == NULL) {
		liberer_Metro(m);
		return NULL;
	}
	m->c = creer_Tab_Correspondance(m->nbStations);
	if (m->c == NULL) {
		liberer_Metro(m);
		return NULL;
	}
	m->lignes = creer_Chaine(m->nbLignes);
	if (m->lignes == NULL) {
		liberer_Metro(m);
		return NULL;
	}
	m->nbAdj = creer_Tableau(m->nbStations);
	if (m->lignes == NULL) {
		liberer_Metro(m);
		return NULL;
	}
	m->l = creer_Tab_Ligne(m->nbLignes);
	if (m->l == NULL) {
		liberer_Metro(m);
		return NULL;
	}
	return m;
}

/**
 * Cette fonction libère la mémoire allouée pour un métro.
 * \param		m, le métro à libérer.
 */
void liberer_Metro(Metro *m) {
	if (m != NULL) {
		liberer_Tab_Parcours(m->p, m->nbStations);
		if (m->c != NULL) {
			liberer_Tab_Correspondance(m->c, m->nbStations);
		}
		if (m->lignes != NULL) {
			liberer_Chaine(m->lignes);
		}
		if (m->nbAdj != NULL) {
			liberer_Tableau(m->nbAdj);
		}
		liberer_Tab_Ligne(m->l, m->nbLignes);
		free(m);
		m = NULL;
	}
}

/**
 * Cette fonction lit sur son entrée un métro et le stocke dans la structure Metro.
 * \param		m, le nouveau métro.
 * \param		entree, entrée pour la lecture.
 */
void lire_Metro(Metro **m, FILE *entree) {
	char tmp[20];
	int i = 0;
	int nbStations, station;
	int nbLignes, j = 0;
	int compteur = 1;
	if ((*m) != NULL) {
		return;
	}
	fscanf(entree, "%s", tmp);
	nbStations = atoi(tmp);
	fscanf(entree, "%s", tmp);
	nbLignes = atoi(tmp);
	(*m) = creer_Metro(nbStations, nbLignes);
	nbStations--;
	while ((fscanf(entree, "%s", tmp)) != EOF) {
		switch (compteur) {
			case 1:
				if (i == nbStations) {
					compteur++;
				}
				(*m)->nbAdj[i] = atoi(tmp);
				if ((*m)->nbAdj[i] != 0) {
					if (0 != (lire_Parcours(&(*m)->p[i], entree, (*m)->nbAdj[i]))) {
						fprintf(stderr, "Erreur sur la syntaxe du fichier\n");
						return;
					}
				}
				i++;
			break;
			case 2:
				if (j == 1) {
					station = atoi(tmp);
					j = 0;
				}
				if (tmp[0] == 'c' || tmp[0] == 'C') {
					j = 1;
				}
				if (tmp[1] == ':') {
					if (0 != (lire_Correspondance(&(*m)->c[station], entree, tmp[0], (*m)->lignes, nbLignes))) {
						fprintf(stderr, "Erreur sur la syntaxe du fichier\n");
						return;
					}
				}
			break;
		}
	}
}

/**
 * Cette fonction écrit sur la sortie un metro.
 * \param		m, le métro à ecrire.
 * \param		sortie, la sortie pour l'affichage de metro.
 */
void ecrire_Metro(Metro *m, FILE *sortie) {
	int i;
	for (i=0 ; i<m->nbStations ; ++i) {
		ecrire_Parcours(m->p[i], sortie);	
	}
	for (i=0 ; i<m->nbStations ; ++i) {
		if (m->c[i] != NULL) {
			fprintf(sortie, "correspondance : %d\n", i);
			ecrire_Correspondance(m->c[i], sortie);	
		}
	}
	for (i=0 ; i<m->nbStations ; ++i) {
		fprintf(sortie, "%d\n", m->nbAdj[i]);	
	}
}

/**
 * Cette fonction renvoie le nombre d'adjacents pour une station à une ligne donnée.
 * \param		m, le métro.
 * \param		station, la station de départ.
 * \param		ligne, la ligne. 
 */
int verifierAdjLigne(Metro *m, int station, char ligne) {
	int compteur = 0;
	Parcours *tmp = NULL;
	tmp = m->p[station];
	while (tmp != NULL) {
		if (tmp->ligne == ligne) {
			compteur++;
		}
		tmp = tmp->suivant;
	}
	return compteur;
}

/**
 * Cette fonction classe les stations dans leur ligne de métro respectif.
 * \param		m, le métro.
 */
void lire_Lignes(Metro **m) {
	Pprofondeur *p;
	int tmp1 = -1, tmp2 = 0, j = 0, k = 0; 
	int i = 0;
	while(j < (*m)->nbLignes) {
		if (0 != verifierAdjLigne(*m, i, (*m)->lignes[j])) {
			(*m)->l[j] = creer_Ligne((*m)->lignes[j], (*m)->nbStations);
			p = creer_Pprofondeur((*m)->nbStations);
			tmp1 = -1;
			tmp2 = 0;
			parcoursProfondeurLigne(m, i, &p, (*m)->lignes[j], &tmp1, i, &tmp2, &k, j);
			liberer_Pprofondeur(p);
			j++;
			k = 0;
		}
		else
			i++;
	}
}

/**
 * Cette fonction effectue un parcours en profondeur sur toutes les lignes du métro,
 * et enregistre les stations appartenant à une même ligne dans 'Metro'.
 * \param		m, contenant toutes les stations à lire.
 * \param		station, station de départ pour le parcours en profondeur.
 * \param		p, permet le marquage des stations déjà visités.
 * \param		ligne, la ligne recherché.
 * \param		tmp1, un compteur permettant le tri des station par ordre de visite sur une ligne de métro 
 				(detection des stations précédant la station origine).
 * \param		origine, première station visité lors du parcours en profondeur.
 * \param		tmp2, un compteur permettant le tri des station par ordre de visite sur une ligne de métro.
 *				(detection des stations suivant la station origine).
 * \param		indice, l'indice du tableau pour l'enregistrement des stations.
 * \param		ligneC, l'indice du tableau de lignes.
 */
void parcoursProfondeurLigne(Metro **m, int station, Pprofondeur **p, char ligne, int *tmp1, int origine, int *tmp2, int *indice, int ligneC) {
	Parcours *tmp = NULL;
	int compteur;
	(*p)->heure++;
	(*p)->debut[station] = (*p)->heure;
	tmp = (*m)->p[station];
	if (station == origine) {
		compteur = verifierAdjLigne(*m, station, ligne);
		if (compteur >= 2) {
			(*tmp1) = compteur;
		}
		else if (compteur == 1) {
			(*m)->l[ligneC]->stations[*indice] = station;
			(*m)->l[ligneC]->longueur++;
			(*indice)++;
		}
	}
	if (station != origine && (*tmp1) == -1) {
		(*m)->l[ligneC]->stations[*indice] = station;
		(*m)->l[ligneC]->longueur++;
		(*indice)++;
	}
	while (tmp != NULL) {
		if ((*p)->debut[tmp->stationAdj] == 0 && tmp->ligne == ligne) {
			(*tmp2)++;
			parcoursProfondeurLigne(m, tmp->stationAdj, p, ligne, tmp1, origine, tmp2, indice, ligneC);
		}
		tmp = tmp->suivant;
	}
	if (station != origine && (*tmp1) != -1) {
		(*tmp2)--;
		(*m)->l[ligneC]->stations[*indice] = station;
		(*m)->l[ligneC]->longueur++;
		(*indice)++;
	}
	if ((*tmp1) != -1 && (*tmp2) == 0) {
		(*tmp1) = -1;
		(*m)->l[ligneC]->stations[*indice] = origine;
		(*m)->l[ligneC]->longueur++;
		(*indice)++;
	}
}

/**
 * Cette fonction inverse l'ordre des stations si le premier terminus est supérieur au dernier.
 * \param		m, le métro contenant le tableau de lignes de métro.
 */
void ajusterTerminus(Metro *m) {
	int i, j = 0, taille, tmp, tmp2 = 0;
	for (i=0 ; i<m->nbLignes ; ++i) {
		j = 0;
		if (m->l[i]->stations[0] > m->l[i]->stations[tmp2]) {
			tmp2 = m->l[i]->longueur - 1;
			if (m->l[i]->longueur%2 == 0) {
				taille = m->l[i]->longueur/2;
				tmp2 = m->l[i]->longueur - 1;
				for (j=0 ; j<taille ; j++) {
					tmp2 -= j;
					tmp = m->l[i]->stations[j];
					m->l[i]->stations[j] = m->l[i]->stations[tmp2];
					m->l[i]->stations[tmp2] = tmp;
				}		
			}
			else {
				taille = (m->l[i]->longueur-1)/2;
				tmp2 = m->l[i]->longueur - 1;
				for (j=0 ; j<taille ; j++) {
					tmp2 -= j;
					tmp = m->l[i]->stations[j];
					m->l[i]->stations[j] = m->l[i]->stations[tmp2];
					m->l[i]->stations[tmp2] = tmp;
				}
			}
		}
	}
	ecrire_Lignes(m, stdout);
}

/**
 * Cette fonction effectue un parcours en profondeur à partir d'un sommet souhaité.
 * \param		m, tableau de Parcours.
 * \param		station, station de départ pour le parcours en profondeur.
 * \param		p, permet de marquer les stations déjà visitées.
 * \param		liste, contenant l'ordre de visite des stations (trié par ordre décroissant).
 * \param		sortie, un descripteur sur la sortie.
 */
void parcoursProfondeur(Parcours **m, int station, Pprofondeur **p, Parcours **liste, FILE *sortie) {
	Parcours *tmp = NULL;
	(*p)->heure++;
	(*p)->debut[station] = (*p)->heure;
	tmp = m[station];
	while (tmp != NULL) {
		if ((*p)->debut[tmp->stationAdj] == 0) {
			parcoursProfondeur(m, tmp->stationAdj, p, liste, sortie);
		}
		tmp = tmp->suivant;
	}
	if (sortie != NULL)
		fprintf(sortie, "%d ", station);
	(*p)->heure++;
	(*p)->fin[station] = (*p)->heure;
	if (liste != NULL)
		ajouter_Parcours(liste, station, '\0', (*p)->fin[station]);
}

/**
 * Cette fonction effectue un parcours en profondeur sur tout le graphe.
 * \param		p, permet de marquer les stations déjà visitées.
 * \param		m, tableau de Parcours.
 * \param		liste, contenant l'ordre de visite des stations (trié par ordre décroissant).
 * \param		taille, le nombre de stations.
 */
void ExplorerProfondeur(Pprofondeur **p, Parcours **m, Parcours **liste, int taille, FILE *sortie) {
	int i = 0;
	for (i=0 ; i<taille ; i++) {
		if ((*p)->debut[i] == 0) {
			parcoursProfondeur(m, i, p, liste, sortie);
		}
	}
}

/**
 * Cette fontion determine les composantes fortements connexes de métro et les affiche sur la sortie.
 * \param		m, le métro à parcourir.
 * \return 		un tableau de Parcours contenant les composantes en cas de succès.
 * \return		NULL en cas d'erreur. 
 */
Parcours **composanteFConnexe(Metro *m) {
	Parcours **resultat = NULL;
	Parcours *tmp = NULL;
	Parcours *liste = NULL;
	Parcours **t = creer_Tab_Parcours(m->nbStations);
	Pprofondeur *p = creer_Pprofondeur(m->nbStations);
	Pprofondeur *a = creer_Pprofondeur(m->nbStations);
	int compteur = 0, indice =0, precedent;
	liste = creer_Parcours(-1, '\0', -1);
	ExplorerProfondeur(&p, m->p, &liste, m->nbStations, NULL);
	transposee(m->p, t, m->nbStations);
	tmp = liste;
	while (tmp != NULL) {
		if (a->debut[tmp->stationAdj] == 0 && tmp->suivant->stationAdj == -1) {
			parcoursProfondeur(t, tmp->stationAdj, &a, resultat, NULL);
		}
		else
			break;
		tmp = tmp->suivant;
	}
	resultat = creer_Tab_Parcours(m->nbStations);
	if (resultat == NULL) {
		return NULL;
	}
	if (resultat != NULL) {
		tmp = liste;
		while (tmp->suivant != NULL) {
			if (compteur == 0) {
				ajouter_Parcours(&resultat[indice], tmp->stationAdj, '\0', 0);

				compteur++;
			}
			else if (tmp->tempsParcours == precedent-1) {
				ajouter_Parcours(&resultat[indice], tmp->stationAdj, '\0', 0);	

			}
			else {
				indice++;
				ajouter_Parcours(&resultat[indice], tmp->stationAdj, '\0', 0);

			}
			precedent = tmp->tempsParcours;
			tmp = tmp->suivant;
		}
	}
	liberer_Parcours(liste);
	liberer_Tab_Parcours(t, m->nbStations);
	liberer_Pprofondeur(p);
	liberer_Pprofondeur(a);
	return resultat;
}

/**
 * Cette fonction alloue la structure Pprofondeur.
 * \param		taille, la taille des tableaux de Pprofondeur.
 * \return 		pointeur sur la structure, en cas de succès.
 * \return 		NULL, en cas d'echec.
 */
Pprofondeur *creer_Pprofondeur(int taille) {
	Pprofondeur *p = NULL;
	p = (Pprofondeur*)calloc(1, sizeof(Pprofondeur));
	if (p == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de Pprofondeur\n");
		return NULL;
	}
	p->debut = (int*)calloc(taille, sizeof(int));
	if (p->debut == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de Pprofondeur->debut\n");
		free(p);
		p = NULL;
		return NULL;
	}
	p->fin = (int*)calloc(taille, sizeof(int));
	if (p->fin == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de Pprofondeur->debut\n");
		free(p->debut);
		p->debut = NULL;
		free(p);
		p = NULL;
		return NULL;
	}
	p->heure = 0;
	return p;
}

/**
 * Cette fonction linère la mémoire allouée pour Pprofondeur.
 * \param		p, l'adresse sur la structure à désallouer.
 */
void liberer_Pprofondeur(Pprofondeur *p) {
	if (p != NULL) {
		if (p->debut != NULL) {
			free(p->debut);
			p->debut = NULL;
		}
		if (p->fin != NULL) {
			free(p->fin);
			p->fin = NULL;
		}
		free(p);
		p = NULL;
	}
}

/**
 * Cette fonction détermine si un métro est eulérien, puis inscrit le resultat sur la sortie.
 * \param		m, le métro.
 * \param		sortie, le descripteur sur la sortie.
 */
int estEulerien(Metro *m, FILE *sortie) {
	int i = 0;
	Pprofondeur *p = NULL;
	while (i < m->nbStations) {
		if (m->nbAdj[i]%2 != 0) {
			fprintf(sortie, "Le graphe n'est pas eulérien\n");
			return 0;
		}
		i++;
	}
	fprintf(sortie, "Le graphe est eulérien\n");
	p = creer_Pprofondeur(m->nbStations);
	parcoursProfondeur(m->p, 0, &p, NULL, sortie); 
	liberer_Pprofondeur(p);
	fprintf(sortie, "\n");
	return 1;
}

/**
 * Cette fonction écrit sur la sortie, les lignes de métro par lignes.
 * \param		m, le métro contenant le tableau de lignes.
 * \param		sortie, un descripteur sur la sortie.
 */
void ecrire_Lignes(Metro *m, FILE *sortie) {
	int i;
	for (i=0 ; i<m->nbLignes ; ++i) {
		ecrire_Ligne(m->l[i], sortie);
	}
}

/**
 * Cette fonction met à jour le tableau de parcours, en y inserant les plus petites valuations en fonction de la station courante.
 * \param		m, le métro, l'ensemble des stations.
 * \param		p, le tableau de parcours à mettre à jour.
 * \param		origine, la station en cours.
 * \param		type, A_TEMPS ou 1 : les temps sur les correspondances sont pris en comptes.
 *					  S_TEMPS ou 1 : les temps sur les correspondances ne sont pas pris en comptes.
 */
void maj_Distances(Metro* m, Parcours **p, int origine, int type) {
	Parcours *tmp = m->p[origine];
	int distance, i = 0, compteur = 0, j = 0, ligne1 = -1, ligne2 = -1;
	while (tmp != NULL) {
		switch(type) {
			case 0:
				distance = tmp->tempsParcours + p[origine]->tempsParcours;
			break;
			case 1:
				if (tmp->ligne == p[origine]->ligne) {
					distance = tmp->tempsParcours + p[origine]->tempsParcours;
				}
				else if (tmp->ligne != p[origine]->ligne) {
					ligne1 = -1, ligne2 = -1;
					i = 0; j = 0;
					compteur = 0;
					while (compteur != 2 && i != m->nbLignes) {
						if (m->lignes[i] == p[origine]->ligne) {
							ligne1 = i;
							compteur++;
						}
						if (m->lignes[j] == tmp->ligne) {
							ligne2 = j;
							compteur++;
						}
						i++;
						j++;
					}
					distance = tmp->tempsParcours + p[origine]->tempsParcours + m->c[origine]->correspondance[ligne1][ligne2];
				}		
			break;
		}
		if (distance < p[tmp->stationAdj]->tempsParcours) {
			p[tmp->stationAdj]->stationAdj = origine;
			p[tmp->stationAdj]->tempsParcours = distance;
			p[tmp->stationAdj]->ligne = tmp->ligne;
		}
		tmp = tmp->suivant;
	}	
}

/**
 * Cette fonction initialise le tableau de parcours.
 * \param		m, le métro comptant tous les stations du graphe.
 * \param		p, le tableau de parcours.
 * \param		depart, la station de départ.
 * \param  		ensemble, l'ensemble des stations déjà visités.
 */
void initialiser_Distances(Metro *m, Parcours **p, int depart, int *ensemble) {
	int i = 0;
	Parcours *tmp = NULL;
	tmp = m->p[depart];
	for (i=0 ; i<m->nbStations ; ++i) {
		p[i] = creer_Parcours(-1, '\0', INFINI);
	}
	i = 0;
	while (tmp != NULL) {
		p[tmp->stationAdj]->stationAdj = depart;
		p[tmp->stationAdj]->ligne = tmp->ligne;
		p[tmp->stationAdj]->tempsParcours = tmp->tempsParcours;
		tmp = tmp->suivant;
		i++;
	}
	p[depart]->tempsParcours = 0;
	ensemble[depart] = 1;
}

/**
 * Cette fonction affiche sur la sortie toutes les plus courtes distances depuis le depart vers toutes les autres stations
 * \param 		m, le métro comptant toutes les stations du graphe.
 * \param 		p, le tableau de parcours.
 * \param		sortie, un descriteur sur la sortie.
 * \param 		depart, le départ de la visite.
 * \param		type, A_TEMPS ou 1 : les temps sur les correspondances sont pris en comptes.
 *					  S_TEMPS ou 1 : les temps sur les correspondances ne sont pas pris en comptes.
 */
int PlusCourtesDistances(Metro* m, Parcours **p, FILE *sortie, int depart, int type) {
	int i = 0, station;
	int *ensemble = NULL;
	if (sortie == NULL || p == NULL) {
		return -2;
	}	
	ensemble = creer_Tableau(m->nbStations);
	if (ensemble == NULL) {
		return -1;
	}
	initialiser_Distances(m, p, depart, ensemble);
	for(i=1 ; i<m->nbStations ; i++) {
		station = min_Distances(p, ensemble, m->nbStations);
		maj_Distances(m, p, station, type);
	}
	liberer_Tableau(ensemble);
	return 0;
}

/**
 * Cette fonction ecrit le plus court chemin depuis une station depart vers les autres sommets successifs.
 * \param		p, un tableau de parcours.
 * \param		sortie, un descriteur sur la sortie.
 * \param		i, un compteur permettant de detecter la première station entré en paramètre.
 * \param		depart, la station courante.
 * \param 		stationD, la station de départ.
 * \param 		ligneP, la ligne de la station précedente.
 * \param 		stationS, la station suivante.
 * \param 		nbAdjD, nombre de stations adjacente pour la station de depart.
 */
void ecrire_PlusCourtChemin(Parcours **p, FILE *sortie, int i, int depart, int stationD, char ligneP, int stationS, int nbAdjD) {
	int precedent;
	if (nbAdjD == 0) {
		fprintf(sortie, "%d\n", depart);
		return;
	}
	if (depart != stationD) {
		if (i != 0) {
			precedent = i;
			i = 0;
			ecrire_PlusCourtChemin(p, sortie, i, p[depart]->stationAdj, stationD, p[depart]->ligne, precedent, nbAdjD);
		}
		else 
			ecrire_PlusCourtChemin(p, sortie, i, p[depart]->stationAdj, stationD, p[depart]->ligne, stationS, nbAdjD);
		if (p[depart]->ligne != ligneP) {
			fprintf(sortie, "%d\n", depart);
			fprintf(sortie, "Ligne %c ", ligneP);
		}
		fprintf(sortie, "%d ", depart);
		if (depart == stationS) {
			fprintf(sortie, "\n");
		}
	}
	else 
		fprintf(sortie, "Ligne %c %d ", ligneP, depart);
}

/**
 * Cette fonction ecrit le plus court chemin depuis une station depart vers toutes les stations.
 * \param		p, un tableau de parcours.
 * \param		sortie, un descriteur sur la sortie.
 * \param		depart, la station de départ.
 * \param 		taille, le nombre de stations.
 * \param 		nbAdjD, nombre de stations adjacente pour la station de depart.
 */
void ecrire_PlusCourtsChemins(Parcours **p, FILE *sortie, int depart, int taille, int nbAdjD) {
	int i;
	for (i=0 ; i<taille ; ++i) {
		if (i == depart)
			continue;
		if (p[i]->tempsParcours != INFINI) {
			fprintf(sortie, "\nTemps %d\n", p[i]->tempsParcours);
			ecrire_PlusCourtChemin(p, sortie, i, i, depart, p[i]->ligne, i, nbAdjD);
			fprintf(sortie, "\n");
		}
		else
			fprintf(sortie, "Station %d non accessible\n", i);
	}
}