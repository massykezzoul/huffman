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
	rewind(fichier);
	return taille;
}

void calcul_proba(float* proba,unsigned long int* compte,unsigned long int taille){
	int i;
	for (i = 0; i < 256; ++i) {
		if (compte[i] != 0) {
			proba[i] = (float) compte[i] / taille;
		}
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
	int i,j=0;
	for (j = 0; j < taille; ++j) {
		d[j].proba = 2.0;
	}

	j  = 0;
	for (i = 0; i < 256; ++i) {
		if (proba[i] != 0) {
			d[j].valeur = (char)i;
			d[j].proba = proba[i];
			j++;
		}
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