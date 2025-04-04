

#include <stdio.h>
#include <stdlib.h>

//#include "animal.h"
#include "liste_chainee.h"


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

int nb_Animal(t_noeud* tete) {
	t_noeud* temp;
	int nbAnimal = 0;
	while (tete != NULL) {
		temp = tete;
		tete = tete->suivant;
		nbAnimal++;
	}
	return nbAnimal;
}

//Déplacer le pointeur courant

//Obtenir le contenu du pointeur courant

//Retirer le contenu du pointeur courant. Noeud doit pointer au prochain. Retourne une copie de l'animal retiré
