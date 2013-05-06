#include <string.h>
#include "Metro.h"

Metro *creer_Metro(int totalStations, int nbLignes) {
	int i, j;
	Metro *m = (Metro*)calloc(1, sizeof(Metro));
	if (m == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de metro\n");
		return NULL;
	}
	m->totalStations = totalStations;
	m->p = (Parcours**)calloc(totalStations, sizeof(Parcours*));
	if (m->p == NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'allocation de metro->parcours\n");
		free(m);
		m = NULL;
		return NULL;
	}
	for (i=0 ; i <m->totalStations ; i++) {
		m->p[i] = (Parcours*)calloc(m->totalStations, sizeof(Parcours));
		if (m->p[i] == NULL) {
			for (j=0; j<i ; j++) {
				free(m->p[j]);
				m->p[j] = NULL;
			}
			free(m->p);
			m->p = NULL;
			free(m);
			m = NULL;
		}
	}

	/*m->l = (Ligne**)calloc(nbLignes, sizeof(Ligne*));
	if (m->l == NULL) {
		free(m->p);
		m->p = NULL;
		free(m);
		m = NULL;
		return NULL;
	}*/
	m->c = (Correspondance**)calloc(nbLignes, sizeof(Correspondance*));
	if (m->c == NULL) {
		free(m->l);
		m->l = NULL;
		free(m->p);
		m->p = NULL;
		free(m);
		m = NULL;
		return NULL;
	}
	return m;
}

/*Parcours creer_Parcours(int tempsParcours, char ligne);*/
int Parcours_Metro(Metro *m, int tempsParcours, char ligne, int origine, int destination) {
	if ((m == NULL) || (m->p == NULL)) {
		return -1;
	}
	m->p[origine][destination] = creer_Parcours(tempsParcours, ligne);
	return 0;
}

int Ligne_Metro(Metro *m, char numero, int nbStations, int position) {
	if ((m == NULL) || (m->l == NULL)) {
		return -1;
	}
	m->l[position] = creer_Ligne(numero, nbStations);
	return 0;
}

void lire_Metro(Metro **m, FILE *entree) {
	char tmp[20];
	int i, j=0, k=0, x=0, y=0, compteur=0, l;
	int totalStations;
	int nbLignes;
	int tempsParcours;
	char ligne;
	char tmp2[5];
	int interrupteur = 0;
	if ((*m) != NULL) {
		return;
	}
	fscanf(entree, "%s", tmp);
	totalStations = atoi(tmp);
	fscanf(entree, "%s", tmp);
	nbLignes = atoi(tmp);
	(*m) = creer_Metro(totalStations, nbLignes);
	while ((fscanf(entree, "%s", tmp)) != EOF) {
		switch(interrupteur) {
			case 0 :
				if((tmp[0] != '(') && (tmp[0] != 'c') && (tmp[0] != 'C')) {
					i = atoi(tmp);
					printf("-%d-  ", i);
				}
				else if (tmp[0] == '('){
					k = 1;
					i--;
					compteur = 0;
					while (tmp[k] != ')') {
						if (tmp[k] == ' ' || tmp[k] == ',') {
							k++;
							continue;
						}
						switch (compteur) {
							case 0 :
								l = 0;
								while (tmp[k] != ' ' && tmp[k] != ',' && tmp[k] != ')') {
									tmp2[l] = tmp[k];
									l++;
									k++;
								}
								tmp2[l] = '\n';
								y = atoi(tmp2);
								printf("(%d ", y);
								compteur++;
							break;
							case 1 :
								ligne = tmp[k];
								printf("%c ", ligne);
								compteur++;
								k++;
							break;
							case 2 :
								l = 0;
								while (tmp[k] != ' ' && tmp[k] != ',' && tmp[k] != ')') {
									tmp2[l] = tmp[k];
									l++;
									k++;
								}
								tmp2[l] = '\n';
								tempsParcours = atoi(tmp2);
								printf("%d)  ", tempsParcours);
							break;
						}
					}
					(*m)->p[x][y] = creer_Parcours(tempsParcours, ligne);
					if (i == 0) {
						printf("\n");
						x++;
					}
				}
				else if ((tmp[0] == 'c') || (tmp[0] == 'C')) {
					interrupteur = 1;
				}
			break;
			case 1 :
				/*
				if (tmp[1] == ':') {
					tmp2[0] = tmp[0];
					tmp2[1] = '\n';
					(*m)->c[j]->association[]
				}

				i = atoi(tmp);
				printf ("Correspondance %d\n", i);
				(*m)->c[j] = creer_Correspondance(i, nbLignes);
				j++;
				(*m)->nbCorresp++;*/
				
			break;
		}
	}
}

/*
int Correspondance_Metro(Metro *m, char numero, int nbStations, int position) {
	if ((m == NULL) || (m->l == NULL)) {
		return -1;
	}
	m->l[position] = creer_Ligne(numero, nbStations);
	return 0;
}*/
/*
void ecrire_Metro(Metro *m) {
	int i;
	for (int i = 0; i < m->nbLignes; ++i)
	{
		
	}
}
void lire_Ligne(Ligne *l, FILE *entree) {
	if (l == NULL) {
		l = creer_Ligne(char numero, int nbStations);
		if (l == NULL) {
			return;
		}
	}
	fscanf(entree, "%-")
}

*/

void liberer_Metro(Metro *m) {
	int j;
	if (m != NULL) {
		if (m->p != NULL) {
			for (j=0; j<m->totalStations ; j++) {
				free(m->p[j]);
				m->p[j] = NULL;
			}
			free(m->p);
			m->p = NULL;
		}
	/*	if (m->c != NULL) {
			for (j=0; j<m->totalStations ; j++) {
				free(m->p[j]);
				m->p[j] = NULL;
			}
			free(m->p);
			m->p = NULL;
		}*/
		if (m->l != NULL) {
			/*for (j = 0; j<m->c[0]->nbLignes ; j++) {
				liberer_Ligne(m->l[j]);
			}*/
			free(m->l);
			m->l = NULL;
		}
		if (m->c != NULL) {
			free(m->c);
			m->c = NULL;
		}
		free(m);
		m = NULL;
	}
}