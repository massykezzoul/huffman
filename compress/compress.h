#ifndef COMPRESS_H
#define COMPRESS_H

#include "../arbre/arbre.h"

void compresse(FILE* non_compresse,FILE* compresse,codage* huffman);
/*
	lit le fichier compressé est ecrit le code de chaque caractère dans le fichier compressé
 */

void decompresse(FILE* compresse,FILE* non_compresse,codage* huffman);
/*
	Décompresse le fichier compresser
	la code de huffman associé doit etre donné en paramètre
 */

char* get_code(codage* huffman,char val);
/*
	renvoie le code huffman associé au caractère val
 */

#endif