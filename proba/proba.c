#include <stdio.h>
#include <stdlib.h>
#include "proba.h"

/* Calcul des probas */

unsigned long int calcul_occurences(unsigned long int* compte, FILE* fichier) {
	char c = fgetc(fichier);
	unsigned long int taille = 0;
	while (c != EOF) {
		compte[(int)c]++;
		c=fgetc(fichier);
		taille++;
	}
	return taille;
}

void calcul_proba(float* proba,unsigned long int* compte,unsigned long int taille,FILE* fichier){
	int i;
	for (i = 0; i < 256; ++i) {
		proba[i] = (float) compte[i] / taille;
	}
}


/* distibutions */

unsigned long int nb_char(float* proba){
	unsigned long int t;
	int i;
	t = 0;
	for (i = 0; i < 256; ++i) {
		if (proba[i] != 0.0)
			t++;
	}
	return t;
}


void init_distribution(float* proba,distribution* d,unsigned long int taille) {
	/* Mettre toute les proba à 2.0 */
	int i;
	for (i = 0; i < taille; ++i) {
		d[i].proba = 2.0;
	}

	/* Insertions des valeurs une à une en gardant le trie */
	for (i = 0; i < 256; ++i) {
		if (proba[i] != 0) {
			inserer_trie((char)i,proba[i],d,taille);
		}
	}
}

void inserer_trie(char c,float p,distribution* d,unsigned long int taille) { /* à refaire en dichotomique */
	int i;
	distribution tmp,tmp2;
	i = 0;
	/* Recherche de sa place */
	while ((i < taille) && (d[i].proba < p)) 
		i++;

	tmp.proba = d[i].proba;
	tmp.valeur = d[i].valeur;

	d[i].proba = p;
	d[i].valeur = c;

	i++;

	/* Decalage des valeurs qui viennent aprés */
	while (tmp.proba != 2.0) {
		/* sauvgarde de l'ancienne valeur */
		tmp2.proba = d[i].proba;
		tmp2.valeur = d[i].valeur;

		/* Mise à jour du tableau */
		d[i].proba = tmp.proba;
		d[i].valeur = tmp.valeur;	

		/* passe à la suivante */
		tmp.proba = tmp2.proba;
		tmp.valeur = tmp2.valeur;
		i++;
	}
}

void affiche_d(distribution* d,unsigned long int taille){
	int i;
	printf("--------------");
	for (i = 0; i < taille; ++i) {
		printf("------");
	}
	printf("\n");

	printf("|   valeur   |");
	for (i = 0; i < taille; ++i) {
		if (d[i].valeur == '\n')
			printf(" \\n  |");
		else if (d[i].valeur == ' ')
			printf(" ESC |");			
		else
			printf("  %c  |",d[i].valeur);
	}
	printf("\n");

	printf("--------------");
	for (i = 0; i < taille; ++i) {
		printf("------");
	}
	printf("\n");

	printf("|probabilité |");
	for (i = 0; i < taille; ++i) {
		printf("%0.3f|",d[i].proba);
	}
	printf("\n");
	printf("--------------");
	for (i = 0; i < taille; ++i) {
		printf("------");
	}
	printf("\n");
}