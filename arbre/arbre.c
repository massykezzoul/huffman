#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"
#include "../proba/proba.h"

node* init_arbre(distribution* d,unsigned long int taille_d) {
	unsigned long int i = 0;
	node* tab;
	tab = calloc(taille_d,sizeof(node));
	for (i = 0; i < taille_d; ++i){
		tab[i].valeur = d[i].valeur;
		tab[i].proba = d[i].proba;
		tab[i].pere = -1;
		tab[i].gauche = -1;
		tab[i].droite = -1;
	}
	return tab;
}

node* make_arbre(distribution* d,unsigned long int taille_d,unsigned long int* taille_tab) {
	node* tab;
	unsigned long int taille = taille_d;
	int i,j;

	tab = init_arbre(d,taille_d);
	
	do {
		i = ppProba(tab,taille,-1);
		j = ppProba(tab,taille,i);

		/* ajout d'un element dans l'arbre */
		++taille;
		tab = realloc(tab,taille * sizeof(node));
		tab[taille-1].valeur = '\0';
		tab[taille-1].proba = tab[i].proba + tab[j].proba;
		tab[taille-1].pere = -1;
		tab[taille-1].gauche = i;
		tab[taille-1].droite = j;

		tab[i].pere = taille-1;
		tab[j].pere = taille-1;

	} while (taille < 2*taille_d - 1);

	*taille_tab = taille;

	return tab;
}

int ppProba(node* tab,unsigned long int taille,int diffrente) {
	int i,tmp;
	float ppproba;
	ppproba = 2.0;
	tmp = 0;
	i = 0;
	while ((i < taille)) {
		if ((ppproba > tab[i].proba) && (i != diffrente) && (tab[i].pere == -1)) {
			ppproba = tab[i].proba;
			tmp = i;
		}
		++i;
	}

	if (ppproba == 2.0)
		tmp = -1;

	return tmp;
}
node copier_node(node a_copier) {
	node res;
	res.valeur = a_copier.valeur;
	res.proba = a_copier.proba;
	res.pere = a_copier.pere;
	res.gauche = a_copier.gauche;
	res.droite = a_copier.droite;

	return res;
}

void concat(char* chaine,unsigned char c,int taille) {
	int i;
	chaine = realloc(chaine,(taille+2)*sizeof(char));
	/* decalacge des caractère */
	for (i = taille; i > 0; --i)
		chaine[i] = chaine[i-1];

	chaine[taille+1] = '\0';
	chaine[0] = c;
}

codage* calcul_codage(node* arbre,unsigned long int nb_char) {
	codage* code;
	int taille_code;
	unsigned long int i,precedent,courent;

	float moyenne = 0;

	courent = 0;							/* premier caractère */
	precedent = 0; 							/* indice du noeud precedent */
	code = calloc(nb_char,sizeof(codage));	/* Tableau du code de huffman associé */

	i = 0;
	/* Pour chaque caractère du fichier */
	for (i = 0; i < nb_char; ++i) { 
		taille_code = 0;
		code[i].valeur = arbre[i].valeur; 				/* initialisation de la valeur */
		code[i].code = calloc(taille_code+1,sizeof(char));	/* initialisation du code huffman */
		courent = arbre[i].pere;
		precedent = i;
		/* Parcour jusqu'a la racine */
		while (courent != -1) {
			if(arbre[courent].gauche == precedent) {
				concat(code[i].code,'0',taille_code);
			}else {
				concat(code[i].code,'1',taille_code);
			}
			precedent = courent;
			courent = arbre[courent].pere; /* vers le pere */
			++taille_code;
			moyenne++;
		}
	}

	return code;
}

void affiche_codage(codage* code,unsigned long int taille){
	int i;
	printf("--------------");
	for (i = 0; i < taille; ++i) {
		printf("------");
	}
	printf("\n");

	printf("|   valeur   |");
	for (i = 0; i < taille; ++i) {
		if ((i>=0) && (i<10))
			printf("  %c  |",code[i].valeur);
		else
			printf("  %c |",code[i].valeur);
	}
	printf("\n");

	printf("--------------");
	for (i = 0; i < taille; ++i) {
		printf("------");
	}
	printf("\n");

	printf("|   codage   |");
	for (i = 0; i < taille; ++i) {
		printf(" %s  |",code[i].code);
	}
	printf("\n");
	printf("--------------");
	for (i = 0; i < taille; ++i) {
		printf("------");
	}
	printf("\n");
}

void affiche_arbre(node* arbre,unsigned long int taille) {
	int i;
	printf("--------------");
	for (i = 0; i < taille; ++i) {
		printf("------");
	}
	printf("\n");

	printf("|   valeur   |");
	for (i = 0; i < taille; ++i) {
		if ((i>=0) && (i<10))
			printf("  %d  |",i);
		else
			printf("  %d |",i);
	}
	printf("\n");

	printf("--------------");
	for (i = 0; i < taille; ++i) {
		printf("------");
	}
	printf("\n");

	printf("|probabilité |");
	for (i = 0; i < taille; ++i) {
		printf("%0.3f|",arbre[i].proba);
	}
	printf("\n");
	printf("--------------");
	for (i = 0; i < taille; ++i) {
		printf("------");
	}
	printf("\n");
	printf("|    pere    |");
	for (i = 0; i < taille; ++i) {
		if ((arbre[i].pere>=0) && (arbre[i].pere<10))
			printf("  %d  |",arbre[i].pere);
		else
			printf("  %d |",arbre[i].pere);
	}
	printf("\n");
	printf("--------------");
	for (i = 0; i < taille; ++i) {
		printf("------");
	}
	printf("\n");
	printf("|   gauche   |");
	for (i = 0; i < taille; ++i) {
		if ((arbre[i].gauche>=0) && (arbre[i].gauche<10))
			printf("  %d  |",arbre[i].gauche);
		else
			printf("  %d |",arbre[i].gauche);
	}
	printf("\n");
	printf("--------------");
	for (i = 0; i < taille; ++i) {
		printf("------");
	}
	printf("\n");
	printf("|   droite   |");
	for (i = 0; i < taille; ++i) {
		if ((arbre[i].droite>=0) && (arbre[i].droite<10))
			printf("  %d  |",arbre[i].droite);
		else
			printf("  %d |",arbre[i].droite);
	}
	printf("\n");
	printf("--------------");
	for (i = 0; i < taille; ++i) {
		printf("------");
	}
	printf("\n");
}