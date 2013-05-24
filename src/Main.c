#include <getopt.h>
#include <time.h>
#include "Main.h"


int main (int argc, char **argv) {
	FILE *f;
	Metro *m = NULL;
	Metro *tmp = NULL;
	Parcours **p = NULL;
	Parcours **resultat;
	int station = -1;
	int option, res;
    const char* const short_options = "tD:C:ec";
    const struct option long_options[] = {
        { "terminus", 		   		0,  NULL,  't' },
        { "plusCourtS", 		    1,  NULL,  'D' },
        { "plusCourtA", 		    1,  NULL,  'C' },
        { "eulerien", 		    	0,  NULL,  'e' },
        { "composante", 		    0,  NULL,  'c' },
        { "help", 		    		0,  NULL,  'h' },
        { NULL,         			0,  NULL,   0  }
    };
    srand(time(NULL));
    ouvrirFichier(&f, "Metro", "r");
    lire_Metro(&m, f);
    fermerFichier(f);
    do {
		option = getopt_long (argc, argv, short_options, long_options, NULL);
		switch (option) {
		    case 't':
		    	tmp = creer_Metro(m->nbStations, m->nbLignes);
		    	if (tmp != NULL) {
		    		if (-1 != (res = copier_ParcoursNonOriente(m->p, tmp->p, tmp->nbStations))) {
			    		ouvrirFichier(&f, "Terminus", "w");
			    		liberer_Tab_Correspondance(tmp->c, m->nbStations);
		    			liberer_Chaine(tmp->lignes);
			    		tmp->c = m->c;
			    		tmp->lignes = m->lignes;
			    		lire_Lignes(&tmp);
						ajusterTerminus(tmp);
					   	ecrire_Lignes(tmp, f);
					    fermerFichier(f);
			    	}
		    	}
		    	tmp->c = NULL;
			    tmp->lignes = NULL;
		    	liberer_Metro(tmp);
		    break;
		    case 'D':
		    	if (1 == sscanf(optarg, "%d", &station)) {
		    		if (station < 0 || station >= m->nbStations) {
			    		fprintf(stderr, "La station selectionnée est invalide\n");
			    	}
		    		else {
		    			ouvrirFichier(&f, "PlusCourtSansTempsChangement", "w");
				    	p = creer_Tab_Parcours(m->nbStations);
						PlusCourtesDistances(m, p, f, station, S_TEMPS);
						ecrire_PlusCourtsChemins(p, f, station, m->nbStations, m->nbAdj[station]);
						liberer_Tab_Parcours(p, m->nbStations);
						fermerFichier(f);
		    		}
		    	}
		    	else {
		    		fprintf(stderr, "L'argument entré n'est pas un entier\n");
		    	}
		    break;
		    case 'C': 
		    	if (1 == sscanf(optarg, "%d", &station)) {
		    		if (station < 0 || station >= m->nbStations) {
			    		fprintf(stderr, "La station selectionnée est invalide\n");
			    	}
		    		else {
		    			ouvrirFichier(&f, "PlusCourtAvecTempsChangement", "w");
				    	p = creer_Tab_Parcours(m->nbStations);
						PlusCourtesDistances(m, p, f, station, A_TEMPS);
						ecrire_PlusCourtsChemins(p, f, station, m->nbStations, m->nbAdj[station]);
						liberer_Tab_Parcours(p, m->nbStations);
						fermerFichier(f);
		    		}
		    	}
		    	else {
		    		fprintf(stderr, "L'argument entré n'est pas un entier\n");
		    	}
		    break;
		    case 'e': 
		    	ouvrirFichier(&f, "Eulerien", "w");
		    	estEulerien(m, f);
		    	fermerFichier(f);
		    break;
		    case 'c': 
				resultat = composanteFConnexe(m);
				ouvrirFichier(&f, "Composante", "w");
				ecrire_Tab_Parcours(resultat, m->nbStations, f);
				fermerFichier(f);
				liberer_Tab_Parcours(resultat, m->nbStations);
		    break;
		    case 'h':
		     	fprintf(stdout, "\n-t ou -terminus : Affiche les lignes du metro dans le fichier \"Terminus\".\n\n");
		     	fprintf(stdout, "-D ou -plusCourtA n : Affiche les plus courts chemins depuis n (un entier) \n\tvers tous les autres sommets dans le fichier \"PlusCourtSansTempsChangement\".\n\n");
		     	fprintf(stdout, "-C ou -plusCourtS n : Affiche les plus courts chemins depuis n (un entier) \n\tvers tous les autres sommets dans le fichier \"PlusCourtAvecTempsChangement\".\n\n");
		     	fprintf(stdout, "-e ou -eulerien : Affiche dans le fichier \"Eulerien\" si le metro est graphe eulérien.\n\n");
		    	fprintf(stdout, "-c ou -composante : Affiche dans le fichier \"Composantes\", les composantes fortements connexes du metro.\n\n");
		    	fprintf(stdout, "--h ou -help : Aide sur les options.\n\n");
		    break; 
		}
	} while (option != -1);
	liberer_Metro(m);
	exit(EXIT_SUCCESS);
}