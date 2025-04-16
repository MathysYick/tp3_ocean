
#include <stdio.h>

#include "ocean.h"
#include "utilitaire_affichage.h"
#include "util.h"

#ifndef ocean_h
#define ocean_h  1

#define HAUTEUR 60
#define LARGEUR 120
/* Type énuméré pour les 8 directions de déplacement */
typedef enum { HAUT, HAUT_DR, DROITE, BAS_DR, BAS, BAS_G, GAUCHE, HAUT_G } t_direction;

/* Type énuméré pour le contenu d'une case */
typedef enum { VIDE, POISSON, REQUIN } t_contenu;
/* Type structure pour le contenu d'une case de la grille */
typedef struct {
	t_contenu contenu; //Soit: VIDE, POISSON ou REQUIN
	void* animal; //Pointeur générique à un animal à cette case, sinon NULL
} t_case;
/* Type-tableau de la grille de l’océan (taille : 60 X 120) */
typedef t_case t_ocean[HAUTEUR][LARGEUR];

#endif


void init_graph() {
	printf("Init graph\n");
	init_graphe(HAUTEUR, LARGEUR);  //TODO je ne comprends pas les paramètres
	init_zone_environnement(HAUTEUR, LARGEUR);
	afficher_case(0, 0, 1, 1, WHITE);
	afficher_case(1, 1, 10, 10, WHITE);
	afficher_case(2, 2, 5, 50, YELLOW);
	afficher_case(3, 3, 15, 10, WHITE);
	afficher_case(4, 4, 100, 100, WHITE);
	afficher_case(50, 45, 100, 100, WHITE);


	afficher_infos(50, 70, 2);


}

void init_ocean(t_ocean ocean) {
	for (int i = 0; i < HAUTEUR; i++) {
		for (int j = 0; j < LARGEUR;j++) {
			ocean[i][j].contenu = VIDE;
			ocean[i][j].animal = NULL;

		}
	}
	printf("Ocean init\n");
}

t_case get_case_content(t_ocean ocean, int posx, int posy) {
	//printf("get case x: %d, y: %d\n", posx, posy);
	return ocean[posx][posy];
}

void set_case(t_ocean ocean, void* animal, t_contenu contenu, int posx, int posy) {
	ocean[posx][posy].contenu = contenu;
	ocean[posx][posy].animal = animal;
}

void errase_case(t_ocean ocean, int posx, int posy) {
	//printf("errase");

	ocean[posx][posy].contenu = VIDE;
	ocean[posx][posy].animal = NULL;
}

int count_empty_case(t_ocean ocean, int posx, int posy) {
	/*ocean[posx-1][posy-1].contenu = VIDE;  //DB
	ocean[posx-1][posy].contenu = REQUIN;
	ocean[posx-1][posy+1].contenu = POISSON;

	ocean[posx][posy-1].contenu = REQUIN;
	ocean[posx][posy].contenu = VIDE;
	ocean[posx][posy+1].contenu = VIDE;

	ocean[posx+1][posy-1].contenu = VIDE;
	ocean[posx+1][posy].contenu = POISSON;
	ocean[posx+1][posy+1].contenu = REQUIN;*/
	t_case cell;
	int empty_count = 0;
	int offset = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			offset = 0;
			if (posx + i < 0 || posx + i >= HAUTEUR) {
				//printf("Out of bound in x\n");
				break;
			}
			if (posy + j < 0) {
				//printf("Out of bound in -y\n");
				offset += 119;
			}else if ( posy + j >= LARGEUR) {
				//printf("Out of bound in +y\n");
				offset -= 119;
			}
			
			cell = get_case_content(ocean, posx + i, posy + j+ offset);
			//printf("x: %d, y: %d, contenu: %d\n", posx + i, posy + j+ offset, cell.contenu);  //DB
			if (cell.contenu == VIDE) {
				//printf("empty cell: x: %d y: %d\n", posx + i, posy + j+ offset);
				empty_count++;
			}
			else {
				//printf("Cell occupé x: %d y: %d\n", posx + i, posy + j+ offset);
			}
		}
		
	}

	cell = get_case_content(ocean, posx, posy); //Cette condition ne devrais pas être utilisé puisque qu'on ne devrait pas compter autour d'une case vide,
	if (cell.contenu == VIDE) {                 //mais juste au cas où.
		empty_count--;
	}
	return empty_count;
}


void draw_ocean(t_ocean ocean) {
	//printf("draw ocean\n");
	for (int i = 0; i < HAUTEUR; i++) {
		for (int j = 0; j < LARGEUR;j++) {
			//printf("x: %d y: %d , %d\n",i,j, ocean[i][j].contenu);
			if (ocean[i][j].contenu == REQUIN) {
				//printf("requin");
				afficher_case(i, j, HAUTEUR, LARGEUR, BLUE);
			}
			else if (ocean[i][j].contenu == VIDE) {
				//printf("VIDE");
				afficher_case(i, j, HAUTEUR, LARGEUR, BLACK);
				//afficher_case(i, j, 1, 1, RED);
			}
			else if (ocean[i][j].contenu == POISSON) {
				//printf("POISSON");
				afficher_case(i, j, HAUTEUR, LARGEUR, GREEN);
				//afficher_case(i, j, 1, 1, RED);
			}
			else if (ocean[i][j].contenu == DEBUG) {
				printf("DEBUG\n");
				afficher_case(i, j, HAUTEUR, LARGEUR, RED);
				//afficher_case(i, j, 1, 1, RED);
			}
			if (ocean[i][j].contenu != VIDE) { //DB
				//delai_ecran(1);
			}
			

		}
	}
}