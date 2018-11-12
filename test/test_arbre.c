#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

int main(int argc, char const *argv[])
{	
	//creation de l'arbre
	node* arbre = calloc(1,sizeof(node));

	ajout(arbre,NULL,NULL,'e',1.0);

	return 0;
}