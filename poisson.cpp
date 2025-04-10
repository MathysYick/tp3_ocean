#include "poisson.h"
#include "util.h"
#include "liste_chainee.h"


void init_liste_poissons(t_liste **tete, t_ocean ocean, int nb_poissons_voulu) {

	t_liste* temporaire = *tete;
	
	for (int i = 0; i < nb_poissons_voulu; i++) {
		//animal->posx = ...
		//animal->posy = ...
		animal->age = rand() % (MAX_AGE_POISSON + 1);
		animal->energie_sante = ENERGIE_INIT_POISSON;
		animal->jrs_gest = 0;
	}

	while (temporaire != nb_poissons_voulu) {
		//animal->posx = ...
		//animal->posy = ...
		animal->age = rand() % (MAX_AGE_POISSON + 1);
		animal->energie_sante = ENERGIE_INIT_POISSON;
		animal->jrs_gest = 0;

		temporaire++;
	}
}