CC=gcc
CFLAGS=-Wall -pedantic -ansi 
LDFLAGS=
EXEC=huffman
ARGV=compresse.txt
SRC = huffman.c arbre/arbre.c proba/proba.c compress/compress.c
HEADERS = arbre/arbre.h proba/proba.h compress/compress.h
OBJ= $(SRC:.c=.o)

all: $(EXEC)

$(EXEC) : $(OBJ) $(HEADERS)
	@$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS) && echo "$(EXEC) created" || echo "Fail"

%.o: %.c 
	@$(CC) -o $@ -c $< $(CFLAGS) 

exe : 
	@./$(EXEC) $(ARGV) && echo "\nProgramme executé sans Erreur" || echo "\nErreur lors de l'execution du programme"

.PHONY : clean mrproper

clean :
	@rm $(OBJ) -rvf

mrproper :	clean
	@rm $(EXEC) -rvf

tar : 
	@tar -czvf code_source.tar.gz makefile $(SRC) $(HEADERS) && echo "'code_source.tar.gz' created" || echo "FAIL"
zip : 
	@zip -r code_source.zip makefile $(SRC) $(HEADERS) && echo "'code_source.zip' created" || echo "FAIL"

subl :
	@subl $(SRC) $(HEADERS)

evince:
	@evince ../../TD\ \&\ TP.pdf &

