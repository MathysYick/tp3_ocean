
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
	init_graphe(1000, 1000);  //TODO je ne comprends pas les paramètres
	init_zone_environnement(HAUTEUR, LARGEUR);
	//afficher_case(2, 2, 5, 50, WHITE);
	afficher_infos(50, 70, 2);


}

void init_ocean(t_ocean ocean) {
	for (int i = 0; i < HAUTEUR; i++) {
		for (int j = 0; j < LARGEUR;j++) {
			if (i % 2 == 0) {
				ocean[i][j].contenu = VIDE;
			}
			else {
				ocean[i][j].contenu = REQUIN;
			}
			
			ocean[i][j].animal = NULL;

		}
	}
	printf("Ocean init\n");
}

t_case get_case_content(t_ocean ocean, int posx, int posy) {
	return ocean[posx][posy];
}

void set_case(t_ocean ocean, void* animal, t_contenu contenu, int posx, int posy) {
	ocean[posx][posy].contenu = contenu;
	ocean[posx][posy].animal = animal;
}

void errase_case(t_ocean ocean, int posx, int posy) {
	ocean[posx][posy].contenu = VIDE;
	ocean[posx][posy].animal = NULL;
}

//void count_empty_case(int* posx, int* posy) {
//	for (int i = 0; i < NB_COUPS; i++) {
//		
//	}
//}


void draw_ocean(t_ocean ocean) {
	for (int i = 0; i < HAUTEUR; i++) {
		for (int j = 0; j < LARGEUR;j++) {
			//printf("x: %d y: %d , %d\n",i,j, ocean[i][j].contenu);
			if (ocean[i][j].contenu == REQUIN) {
				//printf("requin");
				afficher_case(i, j, 1, 1, BLUE);
			}
			else if (ocean[i][j].contenu == VIDE) {
				//printf("VIDE");
				afficher_case(i, j, 10, 100, RED);

			}

		}
	}
}