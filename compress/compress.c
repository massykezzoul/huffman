#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../arbre/arbre.h"
#include "../proba/proba.h"
#include "compress.h"

#include <unistd.h> /* sleep function */

void compresse(FILE* non_compresse,FILE* compresse,codage* huffman,int taille_huf) {
	unsigned char c;		/* pour lire un caractère du fichier non compressé */
	int i,j;
	unsigned char *code; /* Pour stocké le code huffman associé avant de le mettre dans le buffer */
	unsigned char buffer[9] = "22222222\0";

	int ziyada; /* Le nombre de bits non significatif ajouté */
	/* Ecriture des données compressé  */
	c = fgetc(non_compresse);

	while (!feof(non_compresse)) {

		i=0;
       	while(buffer[i]!='2') i++;

       	code=get_code(huffman,c,taille_huf);


       	j=0;
		/* Copié le code dans le buffer jusqu'à ce que le buffer soit plein ou le code copié complétement */
       	while( (i<8) && ( j < strlen(code) ) ){
			buffer[i] = code[j];
			i++;
			j++;
        }

        while ( (i == 8) || (j < strlen(code)))  {
			/* Le buffer est plein */
			if (i == 8) {
				fprintf(compresse,"%c",stringToBinary(buffer,0,8));
				/* Vider le buffer */
				strcpy(buffer,"22222222\0");
				i = 0;
			}

			/* Le code n'a pas été copié completment */
			if(j<strlen(code)) {
				/* copié le code restant dans le nouveau buffer */
				while(i<8 && j< strlen(code)){
					buffer[i]=code[j];
					i++;
					j++;
				}
			}
        }
        c = fgetc(non_compresse);
	}
	/* Ajout des bits non significatif */
	i=0;
    while(buffer[i]!='2') i++;

	if (i != 0) {
		/* Nombre de bits ajouté à la fin */
		ziyada = 8 - i;
   		while (i < 8) {
       		buffer[i] = '0';
       		i++;
     	}
  		fprintf(compresse,"%c",stringToBinary(buffer,0,8));
    } else ziyada = 0;

	/* Ecriture de *ziyada* dans le l'entête après le premier octet */
	fseek(compresse,1,SEEK_SET);
	/* Convertion en chaine de 0 et de 1 de 8 bits */
	FromDecimalToBin(ziyada,code,8);
	fprintf(compresse,"%c",stringToBinary(code,0,8));

}

void decompresse(FILE* compresse,FILE* non_compresse,int verbose) {
	float proba[256] = {0.0};
	unsigned long int taille_d = 0,taille_arbre = 0;
	distribution* d;
	node* arbre;
	codage* code;

	int z;

	unsigned char *buffer = malloc(9*sizeof(unsigned char));

	/* nombre de bits non significatif */
	int ziyada;
	ziyada = lire_entete(compresse,proba);

	taille_d = nb_char(proba);

	d = calloc(taille_d,sizeof(distribution) );
	
	init_distribution(proba,d,taille_d);

	if (verbose) affiche_d(d,taille_d);

	arbre = make_arbre(d,taille_d,&taille_arbre);

	if (verbose) affiche_arbre(arbre,taille_arbre);

	code = calcul_codage(arbre,taille_arbre);
	
	if (verbose) affiche_codage(code,taille_d);

	if (non_compresse == NULL) {
		printf("Le fichier décompréssé : \n");
	}

	/* Ecriture du fichier */
	unsigned char c;
	c = fgetc(compresse);

	/* Initialisation de l'indice a la racine */
	int i=taille_arbre-1;
	int t = 0;

	int nb = 8;
	/* Lecture du fichier complet */
	while (feof(compresse) == 0) {

		/* Mettre l'octet lu dans le buffer en binaire */		
		buffer = binaryToString(c,8);

		c = fgetc(compresse);

		/* dernier Buffer */
		if (feof(compresse) != 0)
			nb = 8 - ziyada;
		else 
			nb = 8;

		/* Parcours du buffer en decedant dans l'arbre */
		for (t=0; t < nb;t++) {
			/* Decendre vers le fils */
			if (buffer[t] == '0') {
				i = arbre[i].gauche;
			} else {
				i = arbre[i].droite;
			}

			/* si est une feuille */
			if (arbre[i].gauche == -1 && arbre[i].droite ==-1) {
				if (non_compresse == NULL) 
					printf("%c",arbre[i].valeur);
				else 
					fprintf(non_compresse,"%c",arbre[i].valeur);
				/* Retour vers la racine */
				i = taille_arbre - 1;
			}
		}
	}
	printf("\n");
}

unsigned char stringToBinary(unsigned char * str,int begin ,int len)
{
    unsigned char code = 0;
    int i;

    for(i = begin; i < begin+len ; i++)
        code |= str[i] - '0' << (begin+len-1 - i);

    return code;
}

char* binaryToString(unsigned char code,int len) {
	int i;
    char *str = malloc(len+1*sizeof(char));
	for (i = 0; i < len; ++i) {
  		str[i] = ((code >> (len-1 - i)) & 1) + '0';
	}
    str[i] = '\0';
    return str;
}

void ecrire_entete(FILE* compresse,unsigned long int occurences[],int nb_char) {
	unsigned char* binaire=malloc(0);
	int i = 0;

	/* buffers */
	unsigned char buf1,buf2,buf3,buf4;

	if (compresse == NULL ) {
		printf("Erreur d'ouverture du fichier compressé.\n");
		exit(1);
	}
	/* nb_char est le nombre de caractère différent du fichier */
	/* Ecriture du nombre de caractère différents au debut du fichier */
	fprintf(compresse,"%c",(unsigned char)nb_char);
	/* initaliser le nombre de de bit non sgnificatif en fin de fichier */
	fprintf(compresse,"%c",0);

	/* Ecriture de chaque caractère suivit de son nombre d'occurences */
	for(i = 0;i<256;++i) {
		if (occurences[i] != 0) {
			/* Ecriture du caractère codé en 8 bits dans le fichier compressé*/
			fprintf(compresse,"%c",(unsigned char)i);
			FromDecimalToBin((unsigned char)i,binaire,8);
			
			/* Ecriture du nombre d'occurences du caractère codé en 32 bits  */
			binaire = realloc(binaire,33*sizeof(unsigned char));
			FromDecimalToBin(occurences[i],binaire,32);
			buf1 = stringToBinary(binaire,0,8);
    	    buf2 = stringToBinary(binaire,8,8);
	        buf3 = stringToBinary(binaire,16,8);
        	buf4 = stringToBinary(binaire,24,8);

			fprintf(compresse,"%c%c%c%c",buf1,buf2,buf3,buf4);
		}
	}
}

int lire_entete(FILE* fichier,float* proba) {
	/* Nombre de caractère différent */
	int n;
	/* Nombre total de caractère */
	int nbc=0;

	int i = 0;
	int l = 0;
	int j = 0;
	int k = 0;

	int ziyada = 0;

	unsigned char* binaire = malloc(9*sizeof(unsigned char));
	unsigned char* binaire2 = malloc(9*sizeof(unsigned char));
	unsigned char c;

	/* Lecture des 8 premier bits */
	c = fgetc(fichier);
	binaire = binaryToString(c,8);
	n = FromBinToDecimal(binaire,8);

	/* Lecture du deuxième octet */
	c = fgetc(fichier);
	binaire = binaryToString(c,8);
	ziyada = FromBinToDecimal(binaire,8);

	for (k = 0;k<n;k++) {
		/* Lecture de la deuxième partie */
		c = fgetc(fichier);
		binaire = binaryToString(c,8);
		i = FromBinToDecimal(binaire,8);


		/* Lecture du nombre d'occurence de cet élement là */
		binaire2 = malloc(9*sizeof(unsigned char));
		for (j = 0; j<4 ;j++) {
			c = fgetc(fichier);
			binaire= binaryToString(c,8);
			binaire2 = strcat(binaire2,binaire);

		}
		proba[i] = FromBinToDecimal(binaire2,32);
		nbc+=proba[i];
	}

	for (k=0;k<256;k++) {
		if (proba[k] != 0.0) {
			proba[k] = proba[k] / nbc;
		}
		
	}

	return ziyada;
}

char* get_code(codage* huffman,unsigned char val,int taille) {
	int i = 0;
	while ((i<taille) && (huffman[i].valeur!=val)) i++;
	return huffman[i].code;
}


void FromDecimalToBin(int chiffreDecimal,unsigned char* binaire,int nb_bits) {
	int leBinaire = 2;
	unsigned char* tmp = malloc((nb_bits+1) * sizeof(unsigned char));
    int i = 0;
	int j=0;

    while (leBinaire <= chiffreDecimal)
        leBinaire *= 2;
    leBinaire /= 2;
    while (leBinaire != 0)
    {
        if (leBinaire <= chiffreDecimal)
        {
            tmp[i] = '1';
            chiffreDecimal -= leBinaire;
        }
        else {
            tmp[i] = '0';
        }
        ++i;
        leBinaire /= 2;
    }
    while (i < nb_bits) {
		binaire[j] = '0';
		++j;
		++i;
	}
	i = 0;
	while (j<nb_bits) {
		binaire[j] = tmp[i];
		++j;
		++i;
	}
	binaire[nb_bits] = '\0';
}

int FromBinToDecimal(unsigned char* binaire,int nb_bits) {
	int decimal = 0;
	int i = nb_bits - 1;
	int k = 1;
	while(i >= 0) {
		if (binaire[i] == '1')
			decimal += k;
		k *= 2;
		--i;
	}
	return decimal;
}
