
#include "animal.h"
#include "ocean.h"
#include "liste_chainee.h"

#ifndef requin_h
#define requin_h 1


#define MAX_AGE_REQUIN 1500 //âge maximal du requin
#define NB_JRS_PUB_REQUIN 90 //nombre de jours avant la puberté
#define NB_JRS_GEST_REQUIN 30 //nombre de jours de gestation
#define ENERGIE_DIGESTION 10 //valeur ajoutée à l'indice d’énergie après un repas

void init_liste_requin(t_noeud** tete, t_ocean ocean, int nb_req_voulu);

int deplacer_requin(t_ocean ocean, t_animal* r);

int add_baby_req(t_ocean ocean, t_animal* r, t_noeud** liste_r);

void kill_req(t_ocean ocean, t_noeud* noeud_r, t_noeud** liste_r);

void eat_shark(t_ocean ocean, t_animal* r, t_noeud** liste_p);

#endif
