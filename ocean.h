#include <stdio.h>



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