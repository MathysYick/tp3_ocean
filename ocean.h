#include <stdio.h>



#ifndef ocean_h
#define ocean_h  1

#define HAUTEUR 60
#define LARGEUR 120
/* Type �num�r� pour les 8 directions de d�placement */
typedef enum { HAUT, HAUT_DR, DROITE, BAS_DR, BAS, BAS_G, GAUCHE, HAUT_G } t_direction;
/* Type �num�r� pour le contenu d'une case */
typedef enum { VIDE, POISSON, REQUIN } t_contenu;
/* Type structure pour le contenu d'une case de la grille */
typedef struct {
	t_contenu contenu; //Soit: VIDE, POISSON ou REQUIN
	void* animal; //Pointeur g�n�rique � un animal � cette case, sinon NULL
} t_case;
/* Type-tableau de la grille de l�oc�an (taille : 60 X 120) */
typedef t_case t_ocean[HAUTEUR][LARGEUR];




#endif