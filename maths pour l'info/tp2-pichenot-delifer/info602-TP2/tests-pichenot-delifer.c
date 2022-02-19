/*
 * info602, TP2 : générateurs pseudo aléatoires simples
 */

#include "tp2.h"

void help()
{
    printf("available tests:\n");
    printf("  invert <A> <M>       inverse modulo M\n");
    printf("  gauss                gauss elimination on stdin\n");
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

    if (0 == strcmp(argv[0], "invert")) {
        if (argc != 3) {
            printf("'invert' expects 2 arguments\n");
            printf("abort...\n");
            exit(1);
        }
        int64_t a = strtol(argv[1], NULL, 10);
        int64_t m = strtol(argv[2], NULL, 10);
        int64_t x = invert_mod(a, m);
        printf("inverse of %" PRId64 " modulo %" PRId64 " is %" PRId64 "\n",
            a, m, x);
        printf("vérification : %" PRId64 " * %" PRId64 " = %" PRId64
               " (mod %" PRId64 ")\n",
            a, x, (a * x) % m, m);
    } else if (0 == strcmp(argv[0], "gauss")) {
        if (argc != 1) {
            printf("'gauss' doesn't expect any argument\n");
            printf("abort...\n");
            exit(1);
        }
        int nb_lines;
        word* M = read_matrix(&nb_lines);
        printf("pivot de Gauss sur la matrice\n");
        print_M(M, nb_lines);
        printf("\n");
        int r = gauss(M, nb_lines);
        if (r == -1) {
            printf("pas de solution (ou une infinité...) !\n");
        } else if (r == 1) {
            printf("résultat:\n");
            print_M(M, nb_lines);
            printf("\n");
        } else {
            printf("valeur de retour inconnue\n");
        }
    } else {
        printf("unknown test: %s\n", argv[0]);
        help();
        exit(1);
    }
    return 0;
}
