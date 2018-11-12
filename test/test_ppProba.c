#include <stdio.h>

typedef struct node node;
struct node{
	char valeur;
	int pere; /*la position du père dans le tableau*/
	int gauche; /*le fils gauche*/
	int droite; /*le fils droite */
	float proba; /* la probabilité d'apparition du caractère */
};


int ppProba(node* tab,int taille,int diffrente) {
	int i,tmp = 0;
	float ppproba=2.0;
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

int main(int argc, char const *argv[])
{
	node tab[3];
	tab[0].valeur = 'c';
	tab[0].proba = 0.012;
	tab[0].pere = 1;
	tab[0].gauche = -1;
	tab[0].droite = -1;
	tab[1].valeur = 'c';
	tab[1].proba = 0.1;
	tab[1].pere = -1;
	tab[1].gauche = -1;
	tab[1].droite = -1;
	tab[2].valeur = 'c';
	tab[2].proba = 0.1;
	tab[2].pere = -1;
	tab[2].gauche = -1;
	tab[2].droite = -1;

	printf("%d\n",ppProba(tab,3,-1));
	return 0;
}