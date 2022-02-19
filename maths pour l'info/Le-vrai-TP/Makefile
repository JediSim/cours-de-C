##
## CONSIGNES :
##    - votre fichier principal devra s'appeler "prenom-nom.c" ou
##      "nom1-nom2.c" si vous êtes en binômes
##    - il faut modifier la variable "NOM" ci dessous pour qu'elle corresponde
##      au nom du fichier (sans le ".c")
##    - pour compiler, il suffit de faire
##      $ make
##      dans le répertoire qui contient les fichiers
##


################
## à modifier ##
################
NOM ?= delifer-pichenot


# FLAGS = -Wall -std=c99 -Wextra -pedantic -Werror
FLAGS = -Wall -std=c99 -Wextra -pedantic -Werror -Wno-unused-parameter -Wno-unused-function



#----------------------------------------------------------------------
#----- NE RIEN MODIFIER SOUS CETTE LIGNE ------------------------------
#----------------------------------------------------------------------

NAME = $(NOM:.c=)
EXE = prng

FILES_C = utils.c lcg.c lfsr.c main.c $(NAME).c tests-$(NAME).c
FILES_O = $(FILES_C:.c=.o)

CC = gcc $(FLAGS)
# CC = clang $(FLAGS)

all: $(EXE)

$(EXE): $(FILES_O)
	$(CC) $(FILES_O) -o $(EXE)

%.o: %.c tp2.h
	$(CC) -c -o $@ $<

albus-dumbledore.o: albus-dumbledore.c tp2.h
	@echo
	@echo "CHANGEZ LE NOM DU FICHIER $< ET"
	@echo "MODIFIEZ LA VARIABLE 'NOM' DANS LE FICHIER Makefile"
	@echo
	$(CC) -c -o $@ $<

clean:
	rm -f *.o a.out

veryclean: clean
	rm -rf $(EXE)

.PHONY: clean veryclean all
