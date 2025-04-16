
#include "animal.h"
#include "ocean.h"
#include "liste_chainee.h"

#ifndef poisson_h
#define poisson_h 1 


#define MAX_POISSON 1000 //nombre maximal de poissons avant la surpopulation
#define MAX_AGE_POISSON 150 //âge maximal du poisson
#define NB_JRS_PUB_POISSON 30 //nombre de jours avant la puberté
#define NB_JRS_GEST_POISSON 15 //nombre de jours de gestation
#define ENERGIE_INIT_POISSON 3 //valeur initiale d'énergie

void init_liste_poissons(t_noeud** tete, t_ocean ocean, int nb_poissons_voulu);

int deplacer_poisson(t_ocean ocean, t_animal* f);

int add_baby_fish(t_ocean ocean, t_animal* f ,t_noeud** liste_p);

void kill_fish(t_ocean ocean, t_noeud* noeud_f, t_noeud** liste_p);

#endif