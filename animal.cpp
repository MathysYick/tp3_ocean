/******************************************************************************/
/*  ANIMAL.H c                                                                */
/*  Module utilitaire qui permet de gérer un type "t_animal"                  */
/*  Conception : Eric Thé                                                     */
/******************************************************************************/


/*
Test 2 10 avril
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "animal.h"

#if !defined (LIB_ANIMAL)
#define LIB_ANIMAL 1

/* Type-structure pour un animal */
typedef struct {
	int   posx, posy;     //sa position
	int   age;            //son age (en jours)
	int   energie_sante;  //le niveau d'énergie 
	int   jrs_gest;       //nombre de jours en gestation
} t_animal;
#endif

/* Reçoit un animal et ses valeurs initiales, va initialiser l'animal reçu.  */
void init_animal(t_animal* animal, int px, int py, int age, int energie, int gest) {

	animal->posx = px;
	animal->posy = py;
	animal->age = age;
	animal->energie_sante = energie;
	animal->jrs_gest = gest;
}

/* Reçoit un animal et retourne sa position via [*px, *py]. */
void get_position(const t_animal* animal, int* px, int* py) {
	*px = animal->posx;
	*py = animal->posy;
}


/* Reçoit un animal et une position et va inscrire cette position à l'animal. */
void set_position(t_animal* animal, int px, int py) {
	animal->posx = px;
	animal->posy = py;
}

/* Reçoit un animal et retourne 1 si le poisson a attient l'age de
   puberté ET a terminé sa période de gestation (donc, il va procréer),
   retourne 0 sinon. */
int  puberte_atteinte(const t_animal* animal, int puberte, int gestation) {
	return animal->age >= puberte && animal->jrs_gest >= gestation;
}

/* Reçoit un animal et va incrémenter son age ainsi que le nombre de jours
   en gestation de +1 jour si il est assez vieux pour procréer. */
void inc_age(t_animal* animal, int puberte) {
	if (animal->age >= puberte) {
		animal->jrs_gest++;
	}
	animal->age++;
}

/* Reçoit un animal et va réinitialiser les jours de gestation à "val".  */
void reset_gestation(t_animal* animal, int val) {
	animal->jrs_gest = val;
}

/* Reçoit un animal et va incrémenter son niveau d'énergie de la valeur reçue.  */
void ajout_energie(t_animal* animal, int energie) {
	animal->energie_sante += energie;
}

/* Reçoit un animal et va décrémenter son niveau d'énergie de -1.  */
void dec_energie(t_animal* animal) {
	animal->energie_sante--;
}

/* Reçoit un animal et va retourner son niveau d'énergie.  */
int  get_energie(t_animal* animal) {
	return animal->energie_sante;
}

/* Retourne 1 si l'animal reçu vient de mourir de faim (plus d'énergie)
   OU si il a atteint son âge maximal (age_max). On retourne 0 sinon.  */
int  est_mort(const t_animal* animal, int age_max) {
	return animal->age >= age_max || animal->energie_sante <= 0;
}
