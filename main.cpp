/*


*/


#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>

//#include "util.h"
//#include "util.cpp"

//#include "utilitaire_affichage.h"
//#include "utilitaire_affichage.cpp"

//#include "winBGIm.h"
//#include "winBGIm.cpp"

//#include "animal.h"
//#include "ocean.h"
#include "poisson.h"
#include "requin.h"
#include "util.h"
#include "utilitaire_affichage.h"

//#include "liste_chainee.h"
//#include "liste_chainee.cpp"


int main() {
	init_alea();

	t_animal lion;
	init_animal(&lion, alea(0, HAUTEUR), alea(0, LARGEUR),2,7,25 );
	printf("HELLO\n");

	t_noeud* liste = creerNoeud(lion);
	
	insererEnTete(&liste, lion);
	insererEnTete(&liste, lion);
	insererEnTete(&liste, lion);
	printf("Liste apres insertion: ");
	afficher_liste(liste);
	
	int poisson = 0;
	poisson = nb_Animal(liste);
	printf("NB animal: %d", poisson);

	//fermer_mode_graphique();

	delai_ecran(1000);
	//while (1);


	return 1;
}