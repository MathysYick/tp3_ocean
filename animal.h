/******************************************************************************/
/*  ANIMAL.H                                                                  */
/*  Module utilitaire qui permet de g�rer un type "t_animal"                  */
/*  Conception : Mathys Yick                                                  */
/******************************************************************************/


/*

TEst 3 10 avril
*/


#if !defined (LIB_ANIMAL)
#define LIB_ANIMAL 1

/* Type-structure pour un animal */
typedef struct {
	int   posx, posy;     //sa position
	int   age;            //son age (en jours)
	int   energie_sante;  //le niveau d'�nergie 
	int   jrs_gest;       //nombre de jours en gestation
} t_animal;

/* Re�oit un animal et ses valeurs initiales, va initialiser l'animal re�u.  */
void init_animal(t_animal* animal, int px, int py, int age, int energie, int gest);

/* Re�oit un animal et retourne sa position via [*px, *py]. */
void get_position(const t_animal* animal, int* px, int* py);

/* Re�oit un animal et une position et va inscrire cette position � l'animal. */
void set_position(t_animal* animal, int px, int py);

/* Re�oit un animal et retourne 1 si le poisson a attient l'age de
   pubert� ET a termin� sa p�riode de gestation (donc, il va procr�er),
   retourne 0 sinon. */
int  puberte_atteinte(const t_animal* animal, int puberte, int gestation);

/* Re�oit un animal et va incr�menter son age ainsi que le nombre de jours
   en gestation de +1 jour si il est assez vieux pour procr�er. */
void inc_age(t_animal* animal, int puberte);

/* Re�oit un animal et va r�initialiser les jours de gestation � "val".  */
void reset_gestation(t_animal* animal, int val);

/* Re�oit un animal et va incr�menter son niveau d'�nergie de la valeur re�ue.  */
void ajout_energie(t_animal* animal, int energie);

/* Re�oit un animal et va d�cr�menter son niveau d'�nergie de -1.  */
void dec_energie(t_animal* animal);

/* Re�oit un animal et va retourner son niveau d'�nergie.  */
int  get_energie(t_animal* animal);

/* Retourne 1 si l'animal re�u vient de mourir de faim (plus d'�nergie)
   OU si il a atteint son �ge maximal (age_max). On retourne 0 sinon.  */
int  est_mort(const t_animal* animal, int age_max);

#endif