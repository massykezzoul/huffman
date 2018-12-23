#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arbre/arbre.h"
#include "proba/proba.h"
#include "compress/compress.h"

#define VERBOSE__ 0

void affiche_info(FILE* source, FILE* dest) {
	/*
		affiche les info suivants :			
			taille originelle de la source, 
			taille compressée et gain en pourcentage,
	*/

	long int taille_source = 0;
	long int taille_dest = 0;

	/* Taille originelle de la source */
	fseek(source,0,SEEK_END);
	
	/* Taille compressée et gain en pourcentage */
	fseek(dest,0,SEEK_END);

	taille_source = ftell(source);
	taille_dest = ftell(dest);

	printf("Information de compression : \n");
	printf("\tTaille Originelle de la source : %ld Octet\n",taille_source);
	printf("\tTaille compressée : %ld Octet\n",taille_dest);	
	printf("\tGain en pourcentage : %0.2f%%\n",(1 - ((float)taille_dest / taille_source)) * 100);

}


int main(int argc, char const *argv[])
{
	/* ----------------------------------------------------------------------------------------------------*/
	/* Etape de compression du fichier */

	/* Declaration des variables */
	FILE* fichier;
	FILE* compress;
	unsigned long int taille_f,taille_d,taille_arbre,i;
	unsigned long int compte[256];
	float proba[256];

	distribution* d;
	
	node* arbre;

	codage* tab_code;
	codage* tab_code2;
	/* initialisation des variables */
	if (argc > 2) {
		fichier = fopen(argv[1],"rb");
		compress = fopen(argv[2],"wb");
	} else {
		printf("Peu d'arguments.\n");
		exit(1);
	}

	/* -------------- COMPRESSION ------------------------------------------------------------------------ */

		taille_d = 0;
		taille_arbre = 0;
		for (i = 0; i < 256; ++i)
			compte[i] = 0;
		for (i = 0; i < 256; ++i)
			proba[i] = 0.0;	

		/* Lecture des occurences et des probabilité à partir du fichier */

		if (fichier == NULL || compress == NULL) {
			printf("Erreur lors de la lecture du fichier '%s', merci de verifier son existance\n",(fichier==NULL)?argv[1]:argv[2]);
			exit(1);
		} else {
			/* Calcule des occurences */
			taille_f = calcul_occurences(compte,fichier);
			/* Calcule des probabilités */
			calcul_proba(proba,compte,taille_f);

		}

		/* Nombre de char different */
		taille_d = nb_char(proba);

		/* Ecriture de l'entête du fichier */
		ecrire_entete(compress,compte,taille_d);

		/* declaration du tableau de la destribution */ 		
		d = calloc(taille_d,sizeof(distribution));

		/* insertion des probabilités */
		init_distribution(proba,d,taille_d);

		/* Affiche la distribution 	*/ 
		if (VERBOSE__) affiche_d(d,taille_d);
		
		/* ----------------------------------------------------------------------------------------------------*/
		/* Etape de creation de l'arbre de huffman */
		
		/* Construction de l'arbre */
		arbre = make_arbre(d,taille_d,&taille_arbre);
		if (VERBOSE__) affiche_arbre(arbre,taille_arbre);
		
		/* Determiner le codage de chaque char sous forme d'un tableau	*/
		tab_code = calcul_codage(arbre,taille_d);
		
		/* Affichage de la table de huffman associé */
		if (VERBOSE__) affiche_codage(tab_code,taille_d);
		
		/* ----------------------------------------------------------------------------------------------------*/
		/* Etape de creation du fichier compressé */		

		compresse(fichier,compress,tab_code,taille_d);

		printf("Fichier '%s' Créer avec Succée.\n",argv[2]);

		affiche_info(fichier,compress);
		
		fclose(fichier);
		fclose(compress);
		

	/* -------------- FIN COMPRESSION ------------------------------------------------------------------------ */



	return 0;
}