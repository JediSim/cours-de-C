#include <stdio.h>
#include <stdlib.h>
#include "train.h"

/* pgm principal pour le client et le serveur */
int main(int argc, char *argv[])
{
    printf("gestion train\n");
    if (argc == 2)
    {
		printf("%s %s %s", "Lancement PGM client de lancement des trains sur le serveur ", argv[1],"\n");
        departTrain(argv[1]);
    }
    else
    {
		printf("%s", "Lancement PGM serveur d'ordonanceur des trains\n");
        ordonanceurTrain();
    }

    return 0;
}
