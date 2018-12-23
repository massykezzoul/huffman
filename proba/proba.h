#ifndef PROBA_H
#define PROBA_H

/* Lecture des probabilité des fichiers */
/* Chaque caractère est codé en 8 bits  */

unsigned long int calcul_occurences(unsigned long int* compte,FILE* fichier);
/*
	Compte le nombre d'occurences de chaqun des carctère present dans le fichier 
	Recoit un tableau d'entier de taille 256 , et un fichier 
	renvoit le tableau avec le nombre d'occurences de chaqun des caractères, et la taille du fichier (nombre de caractère)
*/

void calcul_proba(float* proba,unsigned long int* compte,unsigned long int taille);
/*
	Calcul la probabilité d'apparition de chaque carctère present dans le fichier 
	Recoit un tableau de float de taille 256, la taille du fichier (nombre de char) et un fichier 
	renvoit le tableau avec la proba d'apparition de chaqun des caractères
*/


/* Creation du tableau des distibutions */

typedef struct distribution distribution;
struct distribution {
	unsigned char valeur;
	float proba;
};

unsigned long int nb_char(float* proba);
/*
	Return le nombre de carctère différents dans la proba
	Càd : le nombre porba != 0
*/

void init_distribution(float* proba,distribution* d,unsigned long int taille);
/* 
	Renvoi le tableau d avec tous les elements inserer 
	avec un ordre Croissant des probabilités 
*/

void affiche_d(distribution*,unsigned long int);
/*
	Affiche la distribution sous forme de tableau 
	(limité à 24 caractère différents)
*/
#endif