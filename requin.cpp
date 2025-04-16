#include "requin.h"
#include "util.h"
#include "liste_chainee.h"

#include <stdio.h>
#include <stdlib.h>


//BUG: Un noeud de trop est crée au début. Une adresse invalide est sorti de l'affichage de la liste
void init_liste_requin(t_noeud** tete, t_ocean ocean, int nb_req_voulu) {
	//printf("Init liste requin\n");
	int r_cree = 0;
	t_case cell = {  };
	int x, y;

	while (r_cree < nb_req_voulu) {

		x = alea(0, HAUTEUR);
		y = alea(0, LARGEUR);
		cell = get_case_content(ocean, x, y);

		while (cell.contenu != VIDE) {
			//printf("La case n'est pas vide\n");
			x = alea(0, HAUTEUR);
			y = alea(0, LARGEUR);
			cell = get_case_content(ocean, x, y);
		}

		t_animal* r = (t_animal*)malloc(sizeof(t_animal));
		if (r == NULL) {
			printf("Erreur d'alloc mémoire init liste poisson");
			return;
		}
		r->age = alea(0, MAX_AGE_REQUIN);
		r->energie_sante = alea(1, (ENERGIE_DIGESTION * 2));

		if (r->age >= NB_JRS_PUB_REQUIN) {
			r->jrs_gest = alea(1, NB_JRS_GEST_REQUIN);
		}
		else {
			r->jrs_gest = 0;
		}
		r->posx = x;
		r->posy = y;
		insererEnTete(tete, *r);
		//printf("age: %d\n", r->age);

		//printf("x: %d, y: %d\n", x, y); //DB
		set_case(ocean, r, REQUIN, x, y);
		r_cree++;
	}
	//printf("requin cree: %d\n", r_cree);
	afficher_liste(*tete);
}

int deplacer_requin(t_ocean ocean, t_animal* r) {
	if (r == NULL) { //DB
		printf("Erreur d'alloc mémoire pour poissssson\n");
		return 0;
	}
	//printf("age du poisson qu,on deplace: %d, a la case x: %d y: %d\n", r->age, r->posx, r->posy);

	int emt = count_empty_case(ocean, r->posx, r->posy);
	//printf("number of empty around: %d\n", emt);
	if (emt == 0) {
		return 0;
	}

	t_case cell = get_case_content(ocean, r->posx, r->posy);
	//printf("Contenu: %d\n", cell.contenu);
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

		posx = r->posx;
		posy = r->posy;

		mouv_x = 0;
		mouv_y = 0;

		/*printf("AVANT\n");
		printf("case x: %d y: %d\n", r->posx, r->posy);
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
	//printf("case x: %d y: %d\n", r->posx, r->posy);

	errase_case(ocean, r->posx, r->posy);
	set_case(ocean, r, REQUIN, posx, posy);

	r->posx = posx;
	r->posy = posy;

	//printf("case x: %d y: %d\n", r->posx, r->posy);

	return 1;
}

int add_baby_req(t_ocean ocean, t_animal* r, t_noeud** liste_r) {
	int emt = count_empty_case(ocean, r->posx, r->posy);
	//printf("number of empty around: %d\n", emt);
	if (emt == 0) {
		return 0;
	}

	reset_gestation(r, 0);

		//printf("Accouchement succes\n");
		dec_energie(r);

		t_case cell = get_case_content(ocean, r->posx, r->posy);
		int mouv_x = 0;
		int mouv_y = 0;

		int posx = 0;
		int posy = 0;

		while (cell.contenu != VIDE) {
			int int_dir = alea(0, 7);

			posx = r->posx;
			posy = r->posy;

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
			printf("Erreur d'alloc mémoire pour bébé requin\n");
			return 0;
		}

		init_animal(bb, posx, posy, 0, ENERGIE_DIGESTION, 0);
		insererEnTete(liste_r, *bb);
		set_case(ocean, bb, REQUIN, posx, posy);

		free(bb);

	return 1;
}


void kill_req(t_ocean ocean, t_noeud* noeud_r, t_noeud** liste_r) {
	if (noeud_r == NULL || liste_r == NULL || *liste_r == NULL) {
		printf("Invalid node or list\n");
		exit(100);
	}
	errase_case(ocean, noeud_r->animal.posx, noeud_r->animal.posy);

	t_animal dead = SupprimerNoeud(liste_r, noeud_r);
}

void eat_shark(t_ocean ocean, t_animal* r, t_noeud** liste_p) {
	if (liste_p == NULL || *liste_p == NULL) {
		printf("Erreur: liste de poissons non initialisée\n");
		return;
	}

	int offset = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			offset = 0;
			if (r->posx + i < 0 || r->posx + i >= HAUTEUR) {
				break;
			}
			if (r->posy + j < 0) {
				offset += 119;
			}
			else if (r->posy + j >= LARGEUR) {
				offset -= 119;
			}
			t_case cell = get_case_content(ocean, r->posx + i, r->posy + j + offset);
			if (cell.contenu == POISSON) {
				int is_dead = 0;
				t_noeud* temp = *liste_p;
				while (temp != NULL) {
					if (cell.animal == &(temp->animal)) {
						//printf("poisson a tuer trouver!\n");
						is_dead = 1;
						break;
					}
					temp = temp->suivant;
				}

				if (is_dead == 0) {
					//printf("Erreur: poisson non trouver\n");
					temp = NULL;
					free(temp);
					return;
				}
				ajout_energie(r, ENERGIE_DIGESTION);
				errase_case(ocean, r->posx + i, r->posy + j + offset);
				t_animal dead = SupprimerNoeud(liste_p, (t_noeud*)cell.animal);
				temp = NULL;
				free(temp);
			}
		}
	}
}

