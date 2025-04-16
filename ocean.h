#include <stdio.h>



#ifndef ocean_h
#define ocean_h  1

#define HAUTEUR 60
#define LARGEUR 120

#define POISSON_INIT 400
#define REQUIN_INIT 100

#define NB_COUPS 8

/* Type énuméré pour les 8 directions de déplacement */
typedef enum { HAUT, HAUT_DR, DROITE, BAS_DR, BAS, BAS_G, GAUCHE, HAUT_G } t_direction;
/* Type énuméré pour le contenu d'une case */
typedef enum { VIDE, POISSON, REQUIN , DEBUG} t_contenu;
/* Type structure pour le contenu d'une case de la grille */
typedef struct {
	t_contenu contenu; //Soit: VIDE, POISSON ou REQUIN
	void* animal; //Pointeur générique à un animal à cette case, sinon NULL
} t_case;
/* Type-tableau de la grille de l’océan (taille : 60 X 120) */
typedef t_case t_ocean[HAUTEUR][LARGEUR];


void init_graph();

void init_ocean(t_ocean ocean);

t_case get_case_content(t_ocean ocean, int posx, int posy);

void set_case(t_ocean ocean, void* animal, t_contenu contenu, int posx, int posy);

void errase_case(t_ocean ocean, int posx, int posy);

int count_empty_case(t_ocean ocean, int posx, int posy);

void draw_ocean(t_ocean ocean);
#endif