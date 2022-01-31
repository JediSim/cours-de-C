/*
 * info602, TP1 : code de Golay
 */

#include "tp1.h"

void help()
{
    printf("available tests:\n");
    printf("  binaire <N>       affiche le nombre N en hexa et binaire\n");
}

/*
 * fonction de test, exécutée par l'argument '-T' de la ligne de commande
 */
int perform_tests(int argc, char** argv)
{
    if (argc == 0) {
        printf("no test given\n");
        printf("abort...\n");
        exit(1);
    }

    if (0 == strcmp(argv[0], "binaire")) {
        if (argc != 2) {
            printf("'binaire' expects 1 argument\n");
            printf("abort...\n");
            exit(1);
        }
        int32_t n = strtol(argv[1], NULL, 10);
        printf("en binaire, le mot 0x%08" PRIx32 " s'écrit 0b", n);
        print_bin(n, 32);
        printf("\n");
    } else {
        printf("unknown test: %s\n", argv[0]);
        help();
        exit(1);
    }
    return 0;
}
