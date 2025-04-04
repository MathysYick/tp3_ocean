

#include "animal.h"

//typedef struct {
//	int   posx, posy;     //sa position
//	int   age;            //son age (en jours)
//	int   energie_sante;  //le niveau d'énergie 
//	int   jrs_gest;       //nombre de jours en gestation
//} t_animal;


#ifndef liste_chainee_h
#define liste_chainee_h
typedef struct noeud {
	t_animal animal;
	struct noeud* suivant;
} t_noeud;

//Structure de la liste (Debut, fin , nb animaux, la liste)


t_noeud* creerNoeud(t_animal animal);

void insererEnTete(t_noeud** tete, t_animal animal);

t_noeud* supprimerEnTete(t_noeud* tete);

void afficher_liste(t_noeud* tete);

t_noeud* libererListe(t_noeud* tete);

int nb_Animal(t_noeud* tete);

//Déplacer le pointeur courant

//Obtenir le contenu du pointeur courant

//Retirer le contenu du pointeur courant. Noeud doit pointer au prochain. Retourne une copie de l'animal retiré
#endif