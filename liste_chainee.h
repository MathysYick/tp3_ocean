

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

//-----------------------------------------------------------// Nécessaire ??
typedef t_noeud* ptr_noeud;

typedef struct liste {
	ptr_noeud debut;
	ptr_noeud fin;
	//(void*)liste; // La liste? huh
	int nb_animaux;

}t_liste;
//Structure de la liste (Debut, fin , nb animaux, la liste)
//----------------------------------------------------------//


t_noeud* creerNoeud(t_animal animal);

void insererEnTete(t_noeud** tete, t_animal animal);

t_noeud* supprimerEnTete(t_noeud* tete);

void afficher_liste(t_noeud* tete);

t_noeud* libererListe(t_noeud* tete);

int get_nb_Animal(t_noeud* tete);

void DeplacerCourant(t_noeud* tete);

t_animal ContenuCourant(t_noeud* tete);

//t_animal SupprimerCourant(t_noeud** tete);

t_animal SupprimerNoeud(t_noeud** tete, t_noeud* noeud_a_supprimer);
//Déplacer le pointeur courant

//Obtenir le contenu du pointeur courant

//Retirer le contenu du pointeur courant. Noeud doit pointer au prochain. Retourne une copie de l'animal retiré
#endif