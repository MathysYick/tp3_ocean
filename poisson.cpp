#include "poisson.h"
#include "util.h"
#include "liste_chainee.h"

#include <stdio.h>
#include <stdlib.h>


//BUG: Un noeud de trop est crée au début. Une adresse invalide est sorti de l'affichage de la liste
void init_liste_poissons(t_noeud** tete, t_ocean ocean, int nb_poissons_voulu) {
	printf("Init liste poisson\n");
	int f_cree = 0;
	t_case cell = {  };
	int x, y;

	while (f_cree < nb_poissons_voulu) {

		x = alea(0, HAUTEUR);
		y = alea(0, LARGEUR);
		cell = get_case_content(ocean, x, y);

		while (cell.contenu != VIDE) {
			printf("La case n'est pas vide\n");
			x = alea(0, HAUTEUR);
			y = alea(0, LARGEUR);
			cell = get_case_content(ocean, x, y);
		}

		t_animal* f = (t_animal*)malloc(sizeof(t_animal));
		if (f == NULL) {
			printf("Erreur d'alloc mémoire init liste poisson");
			return;
		}
		f->age = alea(0, MAX_AGE_POISSON);
		f->energie_sante = ENERGIE_INIT_POISSON;
		f->jrs_gest = 0;
		f->posx = x;
		f->posy = y;
		insererEnTete(tete, *f);

		//printf("x: %d, y: %d\n", x, y); //DB
		set_case(ocean, f, POISSON, x, y);
		f_cree++;
	}
	printf("cree: %d\n", f_cree);
}


int deplacer_poisson(t_ocean ocean, t_animal* f) {

	int empty_around = count_empty_case(ocean, f->posx, f->posy);
	if (empty_around == 0) {
		return 0;
	}



	return 1;
}