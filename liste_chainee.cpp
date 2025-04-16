

#include <stdio.h>
#include <stdlib.h>

#include "liste_chainee.h"

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
	//printf("ptr: %p\n", nouveau->suivant);
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
	int a = 0;
	while (temp != NULL) {
		a++;
		//printf("\nNoeud %d: %d -> ptr: % p", a, temp->animal.age, temp);
		printf("%d ->", temp->animal.age);

		temp = temp->suivant;

	}
	printf("\nNULL\n");
	printf("a = %d\n", a);
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

void DeplacerCourant(t_noeud* tete) {
	t_noeud* courant = tete->suivant;
}

t_animal ContenuCourant(t_noeud* tete) {
	t_noeud* courant = tete;

	return courant->animal;
}

t_animal SupprimerNoeud(t_noeud** tete, t_noeud* noeud_a_supprimer) {
	t_animal animal_courant;

	if (*tete == NULL || noeud_a_supprimer == NULL) {
		printf("Erreur: Liste vide ou nœud à supprimer est NULL\n");
		return animal_courant; // Retourne un animal non initialisé en cas d'erreur
	}

	// Si le nœud à supprimer est le nœud de tête
	if (*tete == noeud_a_supprimer) {
		*tete = noeud_a_supprimer->suivant;
		animal_courant = noeud_a_supprimer->animal;
		free(noeud_a_supprimer);
		return animal_courant;
	}


	// Trouver le nœud précédent
	t_noeud* courant = *tete;

	while (courant != NULL && courant->suivant != noeud_a_supprimer) {
		courant = courant->suivant;
		
	}

	// Si le nœud à supprimer n'est pas trouvé
	if (courant == NULL || courant->suivant == NULL) {
		printf("courant est null\n");
		
		printf("Erreur: Noeud à supprimer non trouvé dans la liste\n");
		printf("Noeud: %p\n", noeud_a_supprimer);
		return animal_courant; // Retourne un animal non initialisé en cas d'erreur
	}
	// Détacher le nœud à supprimer de la liste
	courant->suivant = noeud_a_supprimer->suivant;
	animal_courant = noeud_a_supprimer->animal;
	free(noeud_a_supprimer);

	return animal_courant;
}