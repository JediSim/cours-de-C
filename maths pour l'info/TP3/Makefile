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


# NOTE: gnu99 instead of c99 to allow using strdup
# FLAGS = -Wall -std=gnu99 -Wextra -pedantic -Werror -O3
FLAGS = -Wall -std=gnu99 -Wextra -pedantic -Werror -O3 -Wno-unused-parameter -Wno-unused-function



#----------------------------------------------------------------------
#----- NE RIEN MODIFIER SOUS CETTE LIGNE ------------------------------
#----------------------------------------------------------------------

NAME = $(NOM:.c=)
EXE = crack

FILES_C = $(NAME).c tests-$(NAME).c main.c
FILES_O = $(FILES_C:.c=.o)

CC = gcc $(FLAGS)
# CC = clang $(FLAGS)

all: WEP_generator $(EXE)

WEP_generator: WEP_generator.c
	$(CC) $< -o $@

$(EXE): $(FILES_O)
	$(CC) $(FILES_O) -o $(EXE)

%.o: %.c tp3.h
	$(CC) -c -o $@ $<


severus-snape.o: severus-snape.c tp3.h
	@echo
	@echo "CHANGEZ LE NOM DU FICHIER $< ET"
	@echo "MODIFIEZ LA VARIABLE 'NOM' DANS LE FICHIER Makefile"
	@echo
	$(CC) -c -o $@ $<

clean:
	rm -f data_WEP *.o a.out
	killall WEP_generator || true

veryclean: clean
	rm -f WEP_generator $(EXE)

.PHONY: clean veryclean all
