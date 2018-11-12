#include <stdio.h>
#include <stdlib.h>
#include "../arbre/arbre.h"
#include "../proba/proba.h"
#include "compress.h"

void compresse(FILE* non_compresse,FILE* compresse,codage* huffman) {
	char c;
	c = fgetc(non_compresse);
	while (c != EOF) {
		fprintf(compresse,"%s",get_code(huffman,c) );
		c=fgetc(non_compresse);
	}
}

void decompresse(FILE* compresse,FILE* non_compresse,codage* huffman) {
	
}

char* get_code(codage* huffman,char val) {
	int i = 0;
	while (huffman[i].valeur != val) ++i;
	return huffman[i].code;
}