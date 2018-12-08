CC=gcc
LDFLAGS=

HUFF=huffman
MAINH=huffman.c

DEHUFF=dehuffman
MAIND=dehuffman.c

SRCH = $(MAINH) arbre/arbre.c proba/proba.c compress/compress.c
SRCD = $(MAIND) arbre/arbre.c proba/proba.c compress/compress.c

HEADERS = arbre/arbre.h proba/proba.h compress/compress.h
OBJH= $(SRCH:.c=.o) 
OBJD= $(SRCD:.c=.o)

huff: $(HUFF)

$(HUFF) : $(OBJH) $(HEADERS)
	@$(CC) -o $(HUFF) $(OBJH) $(LDFLAGS) && echo "$(HUFF) created" || echo "Fail"

dehuff: $(DEHUFF)

$(DEHUFF) : $(OBJD) $(HEADERS)
	@$(CC) -o $(DEHUFF) $(OBJD) $(LDFLAGS) && echo "$(DEHUFF) created" || echo "Fail"



arbre/arbre.o : arbre/arbre.c
	@$(CC) -o arbre/arbre.o -c arbre/arbre.c $(CFLAGS)

proba/proba.o : proba/proba.c
	@$(CC) -o proba/proba.o -c proba/proba.c $(CFLAGS)

compress/compress.o : compress/compress.c
	@$(CC) -o compress/compress.o -c compress/compress.c $(CFLAGS)

huffman.o : huffman.c
	@$(CC) -o huffman.o -c huffman.c $(CFLAGS)

dehuffman.o : dehuffman.c
	@$(CC) -o dehuffman.o -c dehuffman.c $(CFLAGS)




.PHONY : clean mrproper

clean :
	rm $(OBJH) $(OBJD) -rvf

mrproper :	clean
	@rm $(HUFF) $(DEHUFF) -rvf
