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

typedef enum { UPDATE_REQUIN, UPDATE_POISSON } t_machineState;



int main() {
	init_alea();



	t_animal lion;
	init_animal(&lion, alea(0, HAUTEUR), alea(0, LARGEUR),2,7,25 );
	printf("HELLO\n");

	t_noeud* liste_poisson = creerNoeud(lion);
	
	insererEnTete(&liste_poisson, lion);
	insererEnTete(&liste_poisson, lion);
	insererEnTete(&liste_poisson, lion);
	printf("Liste apres insertion: ");
	afficher_liste(liste_poisson);
	
	int poisson = 0;
	poisson = get_nb_Animal(liste_poisson);
	printf("NB animal: %d\n", poisson);

	t_ocean ocean;
	init_ocean(ocean);
	
	t_case essai;
	essai.contenu = REQUIN;
	essai.animal = liste_poisson; //On lui passe une liste d'animal

	ocean[3][4] = essai;
	t_case case_target;
	case_target = get_case_content(ocean, 2, 2);
	printf("Contenu: %d, pointeur? %p\n", case_target.contenu, (void*)&case_target.animal);

	case_target = get_case_content(ocean, 3, 4);
	printf("Contenu: %d, pointeur? %p\n", case_target.contenu, (void*)&case_target.animal);

	//fermer_mode_graphique();

	init_graph();
	draw_ocean(ocean);


	afficher_case(2, 2, 10, 10, RED);

	delai_ecran(2500);

	printf("Before exit\n");

	int iteration = 0;
	t_machineState machineState = UPDATE_REQUIN;

	while (iteration< MAX_ITERATION);
	switch (machineState) {
	case UPDATE_REQUIN:

		break;

	case UPDATE_POISSON:

		break;

	default:
		break;
	}

	return 1;
}