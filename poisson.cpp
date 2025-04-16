#include "poisson.h"
#include "util.h"
#include "liste_chainee.h"

#include <stdio.h>
#include <stdlib.h>



void init_liste_poissons(t_noeud** tete, t_ocean ocean, int nb_poissons_voulu) {
	//printf("Init liste poisson\n");
	int f_cree = 0;
	t_case cell = {  };
	int x, y;

	while (f_cree < nb_poissons_voulu) {

		x = alea(0, HAUTEUR);
		y = alea(0, LARGEUR);
		cell = get_case_content(ocean, x, y);

		while (cell.contenu != VIDE) {
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
		//printf("age: %d\n", f->age);

		set_case(ocean, f, POISSON, x, y);
		f_cree++;
	}
	//printf("poisson cree: %d\n", f_cree);
	//afficher_liste(*tete);
}


int deplacer_poisson(t_ocean ocean, t_animal* f) {
	if (f == NULL) { //DB
		printf("Erreur d'alloc mémoire pour poissssson\n");
		return 0;
	}

	int emt = count_empty_case(ocean, f->posx, f->posy);
	if (emt == 0) {
		return 0;
	}

	t_case cell = get_case_content(ocean, f->posx, f->posy);
	int mouv_x = 0;
	int mouv_y = 0;

	int posx = 0;
	int posy = 0;

	int it = 0;
	while (cell.contenu != VIDE) {
		
		int int_dir = alea(0, 7);

		posx = f->posx;
		posy = f->posy;

		mouv_x = 0;
		mouv_y = 0;

		switch (int_dir) {
		case HAUT:
			mouv_y++;
			break;

		case HAUT_DR:
			mouv_x++;
			mouv_y--;
			break;

		case DROITE:
			mouv_x++;
			break;

		case BAS_DR:
			mouv_x++;
			mouv_y++;
			break;

		case BAS_G:
			mouv_x--;
			mouv_y++;
			break;

		case BAS:
			mouv_y++;
			break;

		case GAUCHE:
			mouv_x--;
			break;

		case HAUT_G:
			mouv_x--;
			mouv_y--;
			break;
		}

		if (posy + mouv_y >= LARGEUR) {
			posy = 0;
		}
		else if (posy + mouv_y < 0) {
			posy = LARGEUR - 1;
		}
		else {
			posy += mouv_y;
		}

		if (posx + mouv_x < HAUTEUR && posx + mouv_x > 0) {
			posx += mouv_x;
		}

		if (it == 15) {
			return 0;
		}
		it++;
		cell = get_case_content(ocean, posx, posy);

	}

	errase_case(ocean, f->posx, f->posy);
	set_case(ocean, f, POISSON, posx, posy);

	f->posx = posx;
	f->posy = posy;

	return 1;
}

int add_baby_fish(t_ocean ocean, t_animal* f, t_noeud** liste_p) {
	int emt = count_empty_case(ocean, f->posx, f->posy);
	if (emt == 0) {
		return 0;
	}

	int it = 0;
	reset_gestation(f, 0);

	if (alea(1, 3) == 1 || get_nb_Animal(*liste_p) >= MAX_POISSON) {
		//Do nothing
	}
	else {
		dec_energie(f);

		t_case cell = get_case_content(ocean, f->posx, f->posy);
		int mouv_x = 0;
		int mouv_y = 0;

		int posx = 0;
		int posy = 0;

		while (cell.contenu != VIDE) {
			int int_dir = alea(0, 7);

			posx = f->posx;
			posy = f->posy;

			mouv_x = 0;
			mouv_y = 0;

			switch (int_dir) {
			case HAUT:
				mouv_y++;
				break;

			case HAUT_DR:
				mouv_x++;
				mouv_y--;
				break;

			case DROITE:
				mouv_x++;
				break;

			case BAS_DR:
				mouv_x++;
				mouv_y++;
				break;

			case BAS_G:
				mouv_x--;
				mouv_y++;
				break;

			case BAS:
				mouv_y++;
				break;

			case GAUCHE:
				mouv_x--;
				break;

			case HAUT_G:
				mouv_x--;
				mouv_y--;
				break;
			}

			if (posy + mouv_y >= LARGEUR) {
				posy = 0;
			}
			else if (posy + mouv_y < 0) {
				posy = LARGEUR - 1;
			}
			else {
				posy += mouv_y;
			}

			if (posx + mouv_x < HAUTEUR && posx + mouv_x > 0) {
				posx += mouv_x;
			}

			if (it == 15) {
				return 0;
			}
			cell = get_case_content(ocean, posx, posy);

			it++;
		}

		t_animal* bb;
		bb = (t_animal*)malloc(sizeof(t_animal));
		if (bb == NULL) {
			printf("Erreur d'alloc mémoire pour bébé poisson\n");
			return 0;
		}

		init_animal(bb, posx, posy, 0, ENERGIE_INIT_POISSON, 0);
		insererEnTete(liste_p, *bb);
		set_case(ocean, bb, POISSON, posx, posy);
		free(bb);
	}

	return 1;
}

void kill_fish(t_ocean ocean, t_noeud* noeud_f, t_noeud** liste_p) {
	if (noeud_f == NULL || liste_p == NULL || *liste_p == NULL) {
		printf("Invalid node or list\n");
		exit(100);
	}
	errase_case(ocean, noeud_f->animal.posx, noeud_f->animal.posy);

	t_animal dead = SupprimerNoeud(liste_p, noeud_f);
}