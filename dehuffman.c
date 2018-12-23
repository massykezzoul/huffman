#include <stdio.h>
#include <stdlib.h>
#include "arbre/arbre.h"
#include "proba/proba.h"
#include "compress/compress.h"

#define VERBOSE__ 0

int main(int argc, char const *argv[])
{
    /* ------------------- DECOMPRESSION ------------------------------ */

    FILE* compresse;
    FILE* decomp;

    /* Lecture du fichier compressé */
    if (argc == 1) {
        printf("Veuillez donnez en argument un fichier à decompresser");
        exit(1);
    }
    compresse = fopen(argv[1],"rb");

    if (compresse == NULL) {
        printf("Erreur à l'ouverture du fichier compressé : '%s', Veuillez verifier son existance.\n",argv[1]);
        exit(1);
    }


    /* Ecriture du fichier décompressé */
    if (argc == 3) { 
        decomp = fopen(argv[2],"wb");
    } else {
        decomp = NULL;
        
    }

    decompresse(compresse,decomp,VERBOSE__);
    fclose(compresse);
    if (decomp != NULL)
        fclose(decomp);

    printf("Fichier '%s' déompresser avec Succée.\n",argv[1]);
    /* ------------------- FIN DECOMPRESSION -------------------------- */    
    return 0;
}
