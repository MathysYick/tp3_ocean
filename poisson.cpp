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
		printf("age: %d\n", f->age);

		//printf("x: %d, y: %d\n", x, y); //DB
		set_case(ocean, f, POISSON, x, y);
		f_cree++;
	}
	printf("cree: %d\n", f_cree);
	afficher_liste(*tete);
}


int deplacer_poisson(t_ocean ocean, t_animal* f) {
	if (f == NULL) { //DB
		printf("Erreur d'alloc mémoire pour poissssson\n");
		return 0;
	}
	printf("age du poisson qu,on deplace: %d, a la case x: %d y: %d\n", f->age, f->posx, f->posy);

	int emt = count_empty_case(ocean, f->posx, f->posy);
	printf("number of empty around: %d\n", emt);
	if (emt == 0) {
		return 0;
	}

	t_case cell = get_case_content(ocean, f->posx, f->posy);
	printf("Contenu: %d\n", cell.contenu);
	int mouv_x = 0;
	int mouv_y = 0;

	int posx = 0;
	int posy = 0;

	int it = 0;
	while (cell.contenu != VIDE) {
		/*if (it == 15) {
			printf("tourne en rond");
			exit(20);
		}*/
		//printf("it: %d",it);
		it++;
		int int_dir = alea(0, 7);

		posx = f->posx;
		posy = f->posy;

		mouv_x = 0;
		mouv_y = 0;

		/*printf("AVANT\n");
		printf("case x: %d y: %d\n", f->posx, f->posy);
		printf("mouvement %d\n", int_dir);*/

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


		if (posx > HAUTEUR || posy > LARGEUR) {
			//printf("x ou y trop gros \nx: %d y: %d", posx, posy);
		}
		cell = get_case_content(ocean, posx, posy);
	}
	printf("case x: %d y: %d\n", f->posx, f->posy);

	errase_case(ocean, f->posx, f->posy);
	set_case(ocean, f, POISSON, posx, posy);

	f->posx = posx;
	f->posy = posy;

	printf("case x: %d y: %d\n", f->posx, f->posy);

	return 1;
}

int add_baby_fish(t_ocean ocean, t_animal* f, t_noeud** liste_p) {
	int emt = count_empty_case(ocean, f->posx, f->posy);
	//printf("number of empty around: %d\n", emt);
	if (emt == 0) {
		return 0;
	}

	reset_gestation(f, 0);

	if (alea(1, 3) == 1 || get_nb_Animal(*liste_p) >= MAX_POISSON) { // A ENLEVER
		printf("Fausse couche ou max poisson atteint\n");
		printf("nb poissons: %d\n", get_nb_Animal(*liste_p));
	}
	else {
		printf("Accouchement succes\n");
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
			cell = get_case_content(ocean, posx, posy);
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

		//printf("age du poisson parent: %d,       a la case x: %d y: %d\n", f->age, f->posx, f->posy);

		//printf("age du poisson qu,on ajoute: %d, a la case x: %d y: %d\n", bb->age, bb->posx, bb->posy);
		//printf("nb poissons: %d\n", get_nb_Animal(*liste_p));
		//afficher_liste(*liste_p);

		//Ajouter nouveau noeud poisson
	}

	return 1;
}

