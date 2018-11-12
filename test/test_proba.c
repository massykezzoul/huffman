#include <stdio.h>
#include <stdlib.h>
#include "proba.h"

int main(int argc, char const *argv[])
{
	FILE* fichier = NULL;
	fichier = fopen(argv[1], "r");
	unsigned long int compte[256] = {0};
	float proba[256] = {0};
	unsigned long int taille = 0;

	if (fichier == NULL)
		printf("Erreur de lecture du fichier %s\n",argv[1]);
	else {
		//Calcule des occurences + de la taille
		taille = calcul_occurences(compte,fichier);
	 	//Calcule des probabilité 
		calcul_proba(proba,compte,taille,fichier);

		//Affichage des resultats
		printf("La taille du fichier : %ld\n",taille );
		for (int i = 0; i < 256; ++i) {
			if (compte[i] != 0) {
				printf("' %c ' = %ld occurences => %0.3f % \n",(char)i,compte[i],proba[i]);
		 	}
		}
		printf("\n");

		fclose(fichier);
	}
	return 0;
}