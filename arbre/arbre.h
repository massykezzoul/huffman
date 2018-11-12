#ifndef ARBRE_H
#define ARBRE_H

#include "../proba/proba.h"

typedef struct node node;
struct node{
	char valeur;
	int pere; /*la position du père dans le tableau*/
	int gauche; /*le fils gauche*/
	int droite; /*le fils droite */
	float proba; /* la probabilité d'apparition du caractère */
};

typedef struct codage codage;
struct codage {
	char valeur;
	char* code;
};


node* init_arbre(distribution* d,unsigned long int taille_d);
/*
	initialise le tableau d'arbre;
	Données : le tableau des distributions et sa taille
	Resultat : retourne le tableau de node(creer toute les feuilles)
 */

node* make_arbre(distribution* d,unsigned long int taille,unsigned long int* taille_tab);
/*
	Construction de l'arbre
	Données : le tableau des distributions et sa taille;
	Resultat : 	initialise l'arbre avec la fonction init_arbre() puis 
				construis l'arbre complétement et retourne sa taille
 */

int ppProba(node* tab,unsigned long int taille_tab,int diffrente);
/*
	renvoie l'indice de la plus petite proba dans le tableau de node
		tel que cet indice est diffrent du paramètre 'differente'
		et que l'element n'a pas de pere (Càd : n'a pas déja éte fusionné)
*/

node copier_node(node a_copier);
/*
	return un node qui est égal à celui donnée en paramètre
 */

void concat(char* chaine,char c,int taille) ;
/*
	ajoute le char c au debut de la chaine "chaine"
	Rq : chaine doit etre alloué dynamiquement
 */

codage* calcul_codage(node* arbre,unsigned long int taille);
/*
	Renvoie le code associé à chaque caractère en tableau de codage
*/

void affiche_codage(codage* code,unsigned long int taille);

void affiche_arbre(node*,unsigned long int taille_tab);

#endif