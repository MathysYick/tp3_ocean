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

typedef enum { UPDATE_REQUIN, UPDATE_POISSON, DELAY, UPDATE_GRAPH, UPDATE_FILE, NOTHING } t_machineState;

int main() {
	init_alea();

	//t_animal* lion;
	//lion = (t_animal*)malloc(sizeof(t_animal));

	//if (lion == NULL) {
	//	printf("Erreur d'allocation mémoire pour animal");
	//	return 1;
	//}

	//init_animal(lion, alea(0, HAUTEUR), alea(0, LARGEUR), 2, 7, 25);
	//printf("HELLO\n");

	//t_noeud* liste_poisson = creerNoeud(*lion);
	//insererEnTete(&liste_poisson, *lion);
	//insererEnTete(&liste_poisson, *lion);
	//insererEnTete(&liste_poisson, *lion);

	//printf("Liste apres insertion: ");
	//afficher_liste(liste_poisson);

	//int poisson = get_nb_Animal(liste_poisson);
	//printf("NB animal: %d\n", poisson);

	//t_animal* bb_test;
	//bb_test = (t_animal*)malloc(sizeof(t_animal));
	//if (bb_test == NULL) {
	//	printf("Erreur d'alloc mémoire pour bébé poisson\n");
	//	return 0;
	//}

	t_ocean ocean;
	init_ocean(ocean);

	/*t_noeud* tempBB = liste_poisson;

	add_baby_fish(ocean, &tempBB->animal, &liste_poisson);

	printf("Liste apres AJOUT bb: ");
	afficher_liste(liste_poisson);

	poisson = get_nb_Animal(liste_poisson);
	printf("NB animal: %d\n", poisson);*/

	//delay_graph(5000);  //DB

	//t_case essai;
	//essai.contenu = REQUIN;
	//essai.animal = liste_poisson; //On lui passe une liste d'animal

	//ocean[3][4] = essai;
	//t_case case_target;
	//case_target = get_case_content(ocean, 2, 2);
	//printf("Contenu: %d, pointeur? %p\n", case_target.contenu, case_target.animal);

	//case_target = get_case_content(ocean, 3, 4);
	//printf("Contenu: %d, pointeur? %p\n", case_target.contenu, case_target.animal);

	//fermer_mode_graphique();

	init_graph();
	draw_ocean(ocean);

	//afficher_case(2, 2, 10, 10, RED);

	//int empty_case = 0;
	//printf("NB case vide: %d\n", count_empty_case(ocean, 9, 119));

	//free(lion);
	//free(bb_test);


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
	/*afficher_liste(liste_p);

	draw_ocean(ocean);

	t_noeud* fish = liste_p;

	deplacer_poisson(ocean, &fish->animal);

	t_noeud* fish2 = liste_p->suivant;

	deplacer_poisson(ocean, &fish2->animal);
	draw_ocean(ocean);*/



	//LISTE REQUIN
	t_animal* r = (t_animal*)malloc(sizeof(t_animal));
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

	t_noeud* liste_r = creerNoeud(*r);
	init_liste_requin(&liste_r, ocean, REQUIN_DEPART);

	/*printf("LISTE REQUINSSSSSSSS");
	afficher_liste(liste_r);*/

	draw_ocean(ocean);


	t_noeud* temp = liste_p;
	t_noeud* temp_r = liste_r;
	//Déplacement des poissons
	//while (temp->suivant != NULL) {
	//	//temp = temp->suivant;
	//	deplacer_poisson(ocean, &temp->animal);

	//	temp = temp->suivant;
	//	if (f == NULL) { //DB
	//		printf("Erreur d'alloc mémoire pour poisson\n");
	//		break;
	//	}

	//}
	delai_ecran(100);

	draw_ocean(ocean);

	printf("Before exit\n");

	int iteration = 0;
	int nb_pois = get_nb_Animal(liste_p);
	int nb_req = get_nb_Animal(liste_r);

	t_machineState machineState = UPDATE_REQUIN;
	//t_machineState machineState = NOTHING;  //DB

	int fishie = 0;
	int deadd = 0;

	int accouchement = 0;

	FILE* file;
	file = fopen("simulation_data.txt", "w");

	if (file == NULL) {
		printf("Erreur lors de l'ouverture en écriture");
	}

	while (iteration < MAX_ITERATION) {
		switch (machineState) {

		case NOTHING:
			break;
		case UPDATE_REQUIN:

			//printf("SHARK EAT GOOD");
			temp_r = liste_r;
			while (temp_r->suivant != NULL) {
				
				eat_shark(ocean, &temp_r->animal, &liste_p);
				
				temp_r = temp_r->suivant;
			}

			//printf("\nAjout BB SHARK -- DEPLACEMENT SHARK\n");
			temp_r = liste_r;
			fishie = 0;
			while (temp_r->suivant != NULL) {
				accouchement = 0;
				if (puberte_atteinte(&temp_r->animal, NB_JRS_PUB_REQUIN, NB_JRS_GEST_REQUIN)) {
					//printf("\najout bb\n");
					if (add_baby_req(ocean, &temp_r->animal, &liste_r) == 1) {
						//printf("nb req: %d\n", get_nb_Animal(liste_r));
						fishie++;
						accouchement = 1;
					}
					//printf("nb req: %d\n", get_nb_Animal(liste_r));

				}
				if (!accouchement) {
					//printf("Deplacer requin\n");
					deplacer_requin(ocean, &temp_r->animal);
				}
				temp_r = temp_r->suivant;
			}
			//printf("Fishie: %d\n", fishie);
			//afficher_liste(liste_r);


			//printf("KILL REQUIES\n");
			deadd = 0;
			temp_r = liste_r;
			//printf("ptr: %p", temp);
			while (temp_r->suivant != NULL) {
				t_noeud* next_r = temp_r->suivant; // Sauvegardez le prochain nœud avant de supprimer
				if (est_mort(&temp_r->animal, MAX_AGE_REQUIN) == 1) {
					//printf("KILL!\n");
					deadd++;
					kill_fish(ocean, temp_r, &liste_r);
				}
				//printf("ptr: %p\n", temp);
				//temp = temp->suivant;	
				temp_r = next_r;
				//printf("ptr: %p\n", temp);
				next_r = NULL;
				free(next_r);
			}
			/*if (deadd != 0) {
				printf("DEAD SHARK : %d\n", deadd);
			}*/

			//printf("DEAD SHARK : %d\n", deadd);

			

			//printf("INC AGE REQ\n");
			temp_r = liste_r;
			while (temp_r->suivant != NULL) {
				inc_age(&temp_r->animal, NB_JRS_PUB_REQUIN);

				temp_r = temp_r->suivant;

			}

			//printf("DEC ENERGIE\n");
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
						//printf("nb poissons: %d\n", get_nb_Animal(liste_p));
						fishie++;
						accouchement = 1;
					}
					//printf("nb poissns: %d\n", get_nb_Animal(liste_p));

				}

				if (!accouchement) {
					//printf("Deplacer poisson\n");
					deplacer_poisson(ocean, &temp->animal);
				}
				temp = temp->suivant;
			}
			//printf("Fishie: %d\n", fishie);
			//afficher_liste(liste_p);

			//printf("KILL FISHIES\n");
			temp = liste_p;
			while (temp->suivant != NULL) {
				t_noeud* next = temp->suivant; // Sauvegardez le prochain nœud avant de supprimer
				if (est_mort(&temp->animal, MAX_AGE_POISSON) == 1) {
					//printf("KILL!\n");
					kill_fish(ocean, temp, &liste_p);
				}
				//printf("ptr: %p\n", temp);
				//temp = temp->suivant;	
				temp = next;
				//printf("ptr: %p\n", temp);
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
			//delay_graph(100);
			machineState = UPDATE_GRAPH;
			break;

		case UPDATE_GRAPH:

			iteration++;
			nb_pois = get_nb_Animal(liste_p);
			nb_req = get_nb_Animal(liste_r);

			draw_ocean(ocean);
			afficher_infos(iteration, nb_pois, nb_req);

			machineState = UPDATE_FILE;
			break;
		case UPDATE_FILE:
			fprintf(file, "%d,%d,%d\n", iteration, nb_pois, nb_req);
			machineState = UPDATE_REQUIN;

			break;
		}
		
	}


	free(f);
	free(r);
	libererListe(liste_p);
	libererListe(liste_r);
	fclose(file);

	return 1;
}