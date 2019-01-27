# Algorithme de HUFFMAN

## Presentation

Ceci est l'implementation de l'algorithme de compression de données de huffman dans le langage C.<br>
Réalisé dans le cadre d'un TP en Novembre 2018, par Kezzoul Massili.

## Compilation

Pour compiler :

- Le compresseur et Le decompresseur : `make all`
- Le compresseur : `make huff`
- Le decompresseur: `make dehuff`

## Utilisation

- Pour Compressé un fichier :    `./huffman source dest`
- Pour décompressé le fichier :
  - `./dehuffman source` : affiche le fichier décomprésse dans la sortie standart
  - `./dehuffman source dest` : decomrésse le fichier source dans le fichier  dest
