
#include <stdio.h>

#include "ocean.h"
//#include "animal.h"
#include "utilitaire_affichage.h"
#include "util.h"


void init_graph() {
init_graphe(3, 3);
init_zone_environnement(100, 100);
afficher_case(2, 2, 5, 50, WHITE);
afficher_infos(50, 70, 2);
}

void init_ocean() {
	//t_case t_ocean[HAUTEUR][LARGEUR] = { 0 };
	//remplir_liste_poisson()
}

void vider_ocean() {

}

//t_animal* get_case_content(int* posx, int* posy) {
//
//}
//
//void set_case(t_animal* animal, int* posx, int* posy) {
//
//}
//
//void errase_case(int* posx, int* posy) {
//
//}
//
//void count_empty_case(int* posx, int* posy) {
//
//}
