

#include <stdio.h>
#include <stdlib.h>

#include "liste_chainee.h"

//sdfsdf
//gogoogogoogo

// bonsoir tabarnak

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

#endif

t_noeud* creerNoeud(t_animal animal) {
	t_noeud* nouveau = (t_noeud*)malloc(sizeof(t_noeud));
	if (nouveau == NULL) {
		printf("Erreur d'allocation memoire");
		return NULL;
	}

	nouveau->animal = animal;
	nouveau->suivant = NULL;
	return nouveau;
}


void insererEnTete(t_noeud** tete, t_animal animal) {
	t_noeud* nouveau = creerNoeud(animal);
	if (nouveau == NULL) return;

	nouveau->suivant = *tete;
	*tete = nouveau;
}

t_noeud* supprimerEnTete(t_noeud* tete) {
	if (tete == NULL) return NULL;

	t_noeud* temp = tete;
	tete = tete->suivant;
	free(temp);

	return tete;
}

void afficher_liste(t_noeud* tete) {
	t_noeud* temp = tete;

	while (temp != NULL) {
		printf("%d -> ", temp->animal.age);
		temp = temp->suivant;
	}
	printf("NULL\n");
}


t_noeud* libererListe(t_noeud* tete) {
	t_noeud* temp;
	while (tete != NULL) {
		temp = tete;
		tete = tete->suivant;
		free(temp);
	}
	return NULL;
}

int get_nb_Animal(t_noeud* tete) {
	t_noeud* temp;
	int nbAnimal = 0;
	while (tete != NULL) {
		temp = tete;
		tete = tete->suivant;
		nbAnimal++; 
	}
	return nbAnimal;
}

//void DeplacerCourant(t_noeud *tete) {
//	t_noeud *courant = (*tete)->suivant;
//}
//
//t_animal ContenuCourant(t_noeud *tete) {
//	t_noeud *courant = tete;
//
//	return courant->animal;
//}
//
//t_animal SupprimerCourant(t_noeud **tete) {
//	t_noeud *courant = *tete;
//	t_animal animal_courant;
//
//	if ((*tete)->suivant == NULL) {
//		valeur_courant = courant->animal; 
//		free(courant);
//		*tete = NULL;
//
//		return animal_courant;
//	}
//	else {
//		*tete = (*tete)->suivant;
//		valeur_courant = courant->animal;
//		free(courant);
//
//		return animal_courant;
//	}
//}



void Bonjour() {
	printf("hello");
}
