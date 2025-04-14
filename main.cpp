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

#define MAX_ITERATION 5000
#define POISSON_DEPART 400
#define REQUIN_DEPART 100

typedef enum { UPDATE_REQUIN, UPDATE_POISSON, DELAY, UPDATE_GRAPH, NOTHING } t_machineState;



int main() {
	init_alea();

	t_animal* lion;
	lion = (t_animal*)malloc(sizeof(t_animal));

	if (lion == NULL) {
		printf("Erreur d'allocation mémoire pour animal");
		return 1;
	}

	init_animal(lion, alea(0, HAUTEUR), alea(0, LARGEUR), 2, 7, 25);
	printf("HELLO\n");

	t_noeud* liste_poisson = creerNoeud(*lion);
	insererEnTete(&liste_poisson, *lion);
	insererEnTete(&liste_poisson, *lion);
	insererEnTete(&liste_poisson, *lion);

	printf("Liste apres insertion: ");
	afficher_liste(liste_poisson);

	int poisson = get_nb_Animal(liste_poisson);
	printf("NB animal: %d\n", poisson);

	t_ocean ocean;
	init_ocean(ocean);

	t_case essai;
	essai.contenu = REQUIN;
	essai.animal = liste_poisson; //On lui passe une liste d'animal

	ocean[3][4] = essai;
	t_case case_target;
	case_target = get_case_content(ocean, 2, 2);
	printf("Contenu: %d, pointeur? %p\n", case_target.contenu, case_target.animal);

	case_target = get_case_content(ocean, 3, 4);
	printf("Contenu: %d, pointeur? %p\n", case_target.contenu, case_target.animal);

	//fermer_mode_graphique();

	init_graph();
	draw_ocean(ocean);


	//afficher_case(2, 2, 10, 10, RED);

	int empty_case = 0;
	printf("NB case vide: %d\n", count_empty_case(ocean, 9, 119));


	//t_animal* f = (t_animal*)malloc(sizeof(t_animal));
	//f->age = alea(0, MAX_AGE_POISSON);
	//f->energie_sante = ENERGIE_INIT_POISSON;
	//f->jrs_gest = 0;
	//f->posx =alea(0, HAUTEUR);
	//f->posy = alea(0, LARGEUR);
	
    t_animal* f = (t_animal*)malloc(sizeof(t_animal));
	if (f == NULL) {
		printf("Erreur d'allocation mémoire pour animal");
		return 1;
	}
    f->age = alea(0, MAX_AGE_POISSON);
    f->energie_sante = ENERGIE_INIT_POISSON;
    f->jrs_gest = 0;
    f->posx = alea(0, HAUTEUR);
    f->posy = alea(0, LARGEUR);

	t_noeud* liste_p = creerNoeud(*f);
	init_liste_poissons(&liste_p, ocean, POISSON_DEPART);
	afficher_liste(liste_p);

	draw_ocean(ocean);

	t_noeud* fish = liste_p;

	deplacer_poisson(ocean, &fish->animal);

	t_noeud* fish2 = liste_p->suivant;

	deplacer_poisson(ocean, &fish2->animal);
	draw_ocean(ocean);

	t_noeud* temp = liste_p;

	//Déplacement des poissons
	while (temp->suivant != NULL) {
		//temp = temp->suivant;
		deplacer_poisson(ocean, &temp->animal);

		temp = temp->suivant;
		if (f == NULL) { //DB
			printf("Erreur d'alloc mémoire pour poisson\n");
			break;
		}

	}
	delai_ecran(500);

	draw_ocean(ocean);

	printf("Before exit\n");

	int iteration = 0;
	int nb_pois = get_nb_Animal(liste_p);
	t_machineState machineState = UPDATE_REQUIN;

	while (iteration < MAX_ITERATION) {
		switch (machineState) {
		case UPDATE_REQUIN:

			machineState = UPDATE_POISSON;
			break;

		case UPDATE_POISSON:
			printf("Deplacer poisson\n");
			temp = liste_p;
			while (temp->suivant != NULL) {
				printf("\n\n\ndplacement\n");
				deplacer_poisson(ocean, &temp->animal);

				temp = temp->suivant;
				if (f == NULL) { //DB
					printf("Erreur d'alloc mémoire pour poisson\n");
					break;
				}
			}
			machineState = DELAY;
			break;

		case DELAY:
			delay_graph(100);
			machineState = UPDATE_GRAPH;
			break;
		case NOTHING:
			break;
		case UPDATE_GRAPH:

			iteration++;
			nb_pois = get_nb_Animal(liste_p);

			draw_ocean(ocean);
			afficher_infos(iteration, nb_pois, 2);

			machineState = UPDATE_REQUIN;
			break;
		}
	}

	return 1;
}