/******************************************************************************/
/*  ANIMAL.H c                                                                */
/*  Module utilitaire qui permet de g�rer un type "t_animal"                  */
/*  Conception : Eric Th�                                                     */
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
	int   energie_sante;  //le niveau d'�nergie 
	int   jrs_gest;       //nombre de jours en gestation
} t_animal;
#endif

/* Re�oit un animal et ses valeurs initiales, va initialiser l'animal re�u.  */
void init_animal(t_animal* animal, int px, int py, int age, int energie, int gest) {

	animal->posx = px;
	animal->posy = py;
	animal->age = age;
	animal->energie_sante = energie;
	animal->jrs_gest = gest;
}

/* Re�oit un animal et retourne sa position via [*px, *py]. */
void get_position(const t_animal* animal, int* px, int* py) {
	*px = animal->posx;
	*py = animal->posy;
}


/* Re�oit un animal et une position et va inscrire cette position � l'animal. */
void set_position(t_animal* animal, int px, int py) {
	animal->posx = px;
	animal->posy = py;
}

/* Re�oit un animal et retourne 1 si le poisson a attient l'age de
   pubert� ET a termin� sa p�riode de gestation (donc, il va procr�er),
   retourne 0 sinon. */
int  puberte_atteinte(const t_animal* animal, int puberte, int gestation) {
	return animal->age >= puberte && animal->jrs_gest >= gestation;
}

/* Re�oit un animal et va incr�menter son age ainsi que le nombre de jours
   en gestation de +1 jour si il est assez vieux pour procr�er. */
void inc_age(t_animal* animal, int puberte) {
	if (animal->age >= puberte) {
		animal->jrs_gest++;
	}
	animal->age++;
}

/* Re�oit un animal et va r�initialiser les jours de gestation � "val".  */
void reset_gestation(t_animal* animal, int val) {
	animal->jrs_gest = val;
}

/* Re�oit un animal et va incr�menter son niveau d'�nergie de la valeur re�ue.  */
void ajout_energie(t_animal* animal, int energie) {
	animal->energie_sante += energie;
}

/* Re�oit un animal et va d�cr�menter son niveau d'�nergie de -1.  */
void dec_energie(t_animal* animal) {
	animal->energie_sante--;
}

/* Re�oit un animal et va retourner son niveau d'�nergie.  */
int  get_energie(t_animal* animal) {
	return animal->energie_sante;
}

/* Retourne 1 si l'animal re�u vient de mourir de faim (plus d'�nergie)
   OU si il a atteint son �ge maximal (age_max). On retourne 0 sinon.  */
int  est_mort(const t_animal* animal, int age_max) {
	return animal->age >= age_max || animal->energie_sante <= 0;
}
