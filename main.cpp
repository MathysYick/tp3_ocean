/*
Test 10 avril
*/

/*
*/

#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>


#include "poisson.h"
#include "requin.h"
#include "util.h"
#include "utilitaire_affichage.h"
//#include "utilitaire_affichage.cpp"

#define MAX_ITERATION 5000
#define POISSON_DEPART 400
#define REQUIN_DEPART 100

typedef enum { BEGIN, INIT_GRAPHE, INIT_LISTE, UPDATE_REQUIN, UPDATE_POISSON, DELAY, UPDATE_GRAPH, UPDATE_FILE, NOTHING, END } t_machineState;

int main() {
	init_alea();
	init_graph();



	t_ocean ocean;
	init_ocean(ocean);


	int iteration = 0;
	int nb_pois = 0;
	int nb_req = 0;

	t_machineState machineState = BEGIN;

	int fishie = 0;
	int deadd = 0;

	int accouchement = 0;

	FILE* file;
	file = fopen("simulation_data.txt", "w");

	if (file == NULL) {
		printf("Erreur lors de l'ouverture en écriture");
	}


	int affichage = 0;
	int touche = 0;

	t_noeud* temp = NULL;
	t_noeud* temp_r = NULL;

	t_animal* r = NULL;
	t_animal* f = NULL;

	t_noeud* liste_p = NULL;
	t_noeud* liste_r = NULL;

	printf("Voulez-vous avec affichage (O)ui/(N)on ?\n");
	touche = obtenir_touche();

	fflush(stdout);

	while (1) {
		switch (machineState) {

		case NOTHING:
			break;

		case BEGIN:
			if (touche == 'O') {
				affichage = 1;
				machineState = INIT_GRAPHE;

			}
			else {
				affichage = 0;
				machineState = INIT_LISTE;
				fermer_mode_graphique();
			}
			break;

		case INIT_GRAPHE:
			//init_graph();
			draw_ocean(ocean);

			machineState = INIT_LISTE;
			break;

		case INIT_LISTE:
			f = (t_animal*)malloc(sizeof(t_animal));
			if (f == NULL) {
				printf("Erreur d'allocation mémoire pour animal");
				return 1;
			}
			f->age = alea(0, MAX_AGE_POISSON);
			f->energie_sante = ENERGIE_INIT_POISSON;
			f->jrs_gest = 0;
			f->posx = alea(0, HAUTEUR);
			f->posy = alea(0, LARGEUR);

			liste_p = creerNoeud(*f);
			init_liste_poissons(&liste_p, ocean, POISSON_DEPART);

			//LISTE REQUIN
			r = (t_animal*)malloc(sizeof(t_animal));
			if (r == NULL) {
				printf("Erreur d'allocation mémoire pour animal");
				return 1;
			}
			r->age = alea(0, MAX_AGE_POISSON);
			r->energie_sante = alea(1, (ENERGIE_DIGESTION * 2));
			if (r->age >= NB_JRS_PUB_REQUIN) {
				r->jrs_gest = alea(1, NB_JRS_GEST_REQUIN);
			}
			else {
				r->jrs_gest = 0;
			}	r->posx = alea(0, HAUTEUR);
			r->posy = alea(0, LARGEUR);

			liste_r = creerNoeud(*r);
			init_liste_requin(&liste_r, ocean, REQUIN_DEPART);

			temp = liste_p;
			temp_r = liste_r;

			machineState = UPDATE_REQUIN;
			break;
		case UPDATE_REQUIN:
			temp_r = liste_r;
			while (temp_r->suivant != NULL) {
				eat_shark(ocean, &temp_r->animal, &liste_p);
				temp_r = temp_r->suivant;
			}

			temp_r = liste_r;
			fishie = 0;
			while (temp_r->suivant != NULL) {
				accouchement = 0;
				if (puberte_atteinte(&temp_r->animal, NB_JRS_PUB_REQUIN, NB_JRS_GEST_REQUIN)) {
					if (add_baby_req(ocean, &temp_r->animal, &liste_r) == 1) {
						fishie++;
						accouchement = 1;
					}
				}
				if (!accouchement) {
					deplacer_requin(ocean, &temp_r->animal);
				}
				temp_r = temp_r->suivant;
			}
			deadd = 0;
			temp_r = liste_r;
			while (temp_r->suivant != NULL) {
				t_noeud* next_r = temp_r->suivant; // Sauvegardez le prochain nœud avant de supprimer
				if (est_mort(&temp_r->animal, MAX_AGE_REQUIN) == 1) {
					deadd++;
					kill_fish(ocean, temp_r, &liste_r);
				}
				temp_r = next_r;
				next_r = NULL;
				free(next_r);
			}
			temp_r = liste_r;
			while (temp_r->suivant != NULL) {
				inc_age(&temp_r->animal, NB_JRS_PUB_REQUIN);

				temp_r = temp_r->suivant;

			}
			temp_r = liste_r;
			while (temp_r->suivant != NULL) {
				dec_energie(&temp_r->animal);

				temp_r = temp_r->suivant;

			}
			machineState = UPDATE_POISSON;
			break;

		case UPDATE_POISSON:
			//printf("Ajout BB fish -- Deplacement fish\n");
			temp = liste_p;
			fishie = 0;
			while (temp->suivant != NULL) {
				accouchement = 0;
				if (puberte_atteinte(&temp->animal, NB_JRS_PUB_POISSON, NB_JRS_GEST_POISSON)) {
					//printf("\najout bb\n");
					if (add_baby_fish(ocean, &temp->animal, &liste_p) == 1) {
						fishie++;
						accouchement = 1;
					}
				}

				if (!accouchement) {
					deplacer_poisson(ocean, &temp->animal);
				}
				temp = temp->suivant;
			}
			//printf("KILL FISHIES\n");
			temp = liste_p;
			while (temp->suivant != NULL) {
				t_noeud* next = temp->suivant; // Sauvegardez le prochain nœud avant de supprimer
				if (est_mort(&temp->animal, MAX_AGE_POISSON) == 1) {
					kill_fish(ocean, temp, &liste_p);
				}
				temp = next;
				next = NULL;
				free(next);
			}

			//printf("INC poissons\n");
			temp = liste_p;
			while (temp->suivant != NULL) {
				inc_age(&temp->animal, NB_JRS_PUB_POISSON);
				temp = temp->suivant;
			}
			machineState = DELAY;
			break;

		case DELAY:
			iteration++;
			nb_pois = get_nb_Animal(liste_p);
			nb_req = get_nb_Animal(liste_r);

			//delay_graph(100);
			if (affichage) {
				machineState = UPDATE_GRAPH;
			}
			else {
				machineState = UPDATE_FILE;
			}
			break;

		case UPDATE_GRAPH:

			

			draw_ocean(ocean);
			afficher_infos(iteration, nb_pois, nb_req);

			machineState = UPDATE_FILE;
			break;
		case UPDATE_FILE:
			fprintf(file, "%d,%d,%d\n", iteration, nb_pois, nb_req);
			machineState = UPDATE_REQUIN;


			if (iteration > 10) {
				if (iteration >= MAX_ITERATION|| nb_pois == 0|| nb_req == 0) {
					machineState = END;
				}
			}
			break;

		case END:
			printf("Les résultats ont ete enregistre dans le fichier simulation_data.txt\n\n");

			if (iteration >= MAX_ITERATION ) {
				printf("La simulation c'est termine normallement\n");
			}
			else if (nb_pois == 0) {
				printf("Extinction des poissons\n");

			}
			else if (nb_req == 0) {
				printf("Extinction des requins\n");

			}

			free(f);
			free(r);
			/*free(temp);
			free(temp_r);*/
			libererListe(liste_p);
			libererListe(liste_r);
			fclose(file);

			return 1;
			break;
		}

	}
	return 1;
}