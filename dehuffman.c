#include <stdio.h>
#include <stdlib.h>
#include "arbre/arbre.h"
#include "proba/proba.h"
#include "compress/compress.h"

int main(int argc, char const *argv[])
{
    /* ------------------- DECOMPRESSION ------------------------------ */

    FILE* compresse;
    FILE* decomp;

    /* Lecture du fichier compressé */
    if (argc == 1) {
        printf("Veuillez donnez en argument un fichier à decompressé");
        exit(1);
    }
    compresse = fopen(argv[1],"r");

    if (compresse == NULL) {
        printf("Erreu à l'ouverture du fichier compressé : '%s', Veuillez verifier son existance.\n",argv[1]);
        exit(1);
    }


    /* Ecriture du fichier décompressé */
    if (argc == 3) { 
        decomp = fopen(argv[2],"w");
    } else {
        decomp = NULL;
        
    }

    decompresse(compresse,decomp);
    fclose(compresse);
    if (decomp != NULL)
        fclose(decomp);

    /* ------------------- FIN DECOMPRESSION -------------------------- */    
    return 0;
}
