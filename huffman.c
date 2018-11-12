#include <stdio.h>
#include <stdlib.h>
#include "arbre/arbre.h"
#include "proba/proba.h"
#include "compress/compress.h"


int main(int argc, char const *argv[])
{
	/* ----------------------------------------------------------------------------------------------------*/
	/* Etape de compression du fichier */

	/* Declaration des variables */
	FILE* fichier;
	FILE* compress;
	unsigned long int taille_d,taille_arbre,i;
	unsigned long int compte[256];
	float proba[256];


	distribution* d;
	
	node* arbre;

	codage* tab_code;
	/* initialisation des variables */

	fichier = fopen(argv[1],"r");

	taille_d = 0;
	taille_arbre = 0;
	for (i = 0; i < 256; ++i)
		compte[i] = 0;
	for (i = 0; i < 256; ++i)
		proba[i] = 0.0;	

	/* Lecture des occurences et des probabilité à partir du fichier */

	if (fichier == NULL) {
		printf("Erreur lors de la lecture du fichier '%s', merci de verifier son existance\n",argv[1]);
		exit(1);
	} else {
		/* Calcule des occurences */
		taille_d = calcul_occurences(compte,fichier);
		/* Calcule des probabilités */
		calcul_proba(proba,compte,taille_d,fichier);

		fclose(fichier);
	}

	/* Nombre de char different */
	taille_d = nb_char(proba);

	/* declaration du tableau de la destribution */ 		
	d = calloc(taille_d,sizeof(distribution));

	/* insertion des probabilités (trié en Ascendant) ps:pourquoi trié? je ne sais pas*/
	init_distribution(proba,d,taille_d);

	/* Affiche la distribution 	*/ 
	/* affiche_d(d,taille_d); 	*/


	/* ----------------------------------------------------------------------------------------------------*/
	/* Etape de creation de l'arbre de huffman */

	/* Construction de l'arbre */
	arbre = make_arbre(d,taille_d,&taille_arbre);

	/*affiche_arbre(arbre,taille_arbre);		*/
	
	/* Determiner le codage de chaque char sous forme d'un tableau	*/
	tab_code = calcul_codage(arbre,taille_d);

	/* Affichage de la table de huffman associé */
	/*affiche_codage(tab_code,taille_d);		*/

	/* ----------------------------------------------------------------------------------------------------*/
	/* Etape de creation du fichier compressé */


	if (argv[2] == NULL)
		compress = fopen("compressed.huf","w");
	else 
		compress = fopen(argv[2],"w");

	fichier = fopen(argv[1],"r");

	if ((compress == NULL) || (fichier == NULL)) {
		printf("Erreur à la creation du fichier, ou la réouverture du fichier .\n");
		exit(1);
	} else {
		/* ecriture du fichier compressé */
		compresse(fichier,compress,tab_code);
		fclose(fichier);
		fclose(compress);
	}



	return 0;
}