#ifndef COMPRESS_H
#define COMPRESS_H

#include "../arbre/arbre.h"

void compresse(FILE* non_compresse,FILE* compresse,codage* huffman,int taille_huf);
/*	
	1 - Ecrit l'entête
	2 - lit le fichier non_compressé et ecrit le code associé de chaque caractère dans le fichier compressé
 */

void decompresse(FILE* compresse,FILE* non_compresse,int verbose);
/*
	1 - Lit l'entête du fichier
	2 - Décompresse le fichier compresser
	si (verbose != 0) alors la fonction affiche les information de décompression en détail (La distribution, l'arbre de huffman, le codage de chaque caractère)
 */

char* get_code(codage* huffman,unsigned char val,int taille);
/*
	renvoie le code huffman associé au caractère val
 */

unsigned char stringToBinary(unsigned char * str,int begin ,int len);

char* binaryToString(unsigned char code,int len);



void ecrire_entete(FILE* compresse,unsigned long int occurences[],int nb_char);
/* 
	Ecrit l'entête du fichier,
	l'entier int étant le nombre de charactère différent (taille du tableau : codage)
*/

int lire_entete(FILE*,float*);
/*
	Lit l'entête du fichier et renvoie le code huffman associé
*/


void FromDecimalToBin(int chiffreDecimal,unsigned char* binaire,int nb);
/*
	Convertion Decimal to binaire 
	le binaire est stocké binaire en chaine de caractère de nb bits.
*/
int FromBinToDecimal(unsigned char* binaire,int nb );
/*
	Convertion Binaire TO Decimal
	Retourne l'entier conrespondant au binaire codé en nb bits
*/


#endif