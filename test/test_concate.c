#include <stdio.h>
#include <stdlib.h>

void concat(char* chaine,char c,int taille) {	
	int i;
	chaine = realloc(chaine,(taille+1)*sizeof(char));
	/* decalacge des caractère */
	for (i = taille; i > 0; --i)
		chaine[i] = chaine[i-1];

	chaine[0] = c;
}

int main(int argc, char const *argv[]) {
	char* chaine = calloc(0,sizeof(char));
	char c = '5';
	concat(chaine,c,0);
	printf("%s\n",chaine);
	concat(chaine,c,1);
	printf("%s\n",chaine);
	return 0;
}