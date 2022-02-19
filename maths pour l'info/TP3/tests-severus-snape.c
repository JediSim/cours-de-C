#include "tp3.h"

void help()
{
    printf("available tests:\n");
    printf("  get_data <N>\n");
    printf("  weak  <KEY> <O1> (ex: weak 0x78 0x89 0xec 0x01 0x02 0x03 0x04 "
           "0x21)\n");
}
/***
 * fonction de tests, appelée par la ligne de commandes avec l'option -T
 */
int perform_tests(int argc, char** argv)
{
    if (argc == 0) {
        printf("no test to run...\n");
        help();
        return 1;
    }

    // test "get_data"
    if (0 == strcmp(argv[0], "get_data")) {

        int n;
        if (argc < 2) {
            n = 10;
        } else {
            n = atoi(argv[1]);
        }

        printf("\n\nfonction get_data\n"
               "-----------------\n"
               "affichage des %d premiers paquets :\n\n",
            n);
        byte IV[IV_size];
        byte o1, o2;
        for (int i = 0; i < n; i++) {
            if (get_data(IV, &o1, &o2) == IV_size) {
                printf("paquet %2d : ", i + 1);
                for (int k = 0; k < IV_size; k++)
                    printf("%02x ", IV[k]);
                printf(" =>  %02x %02x\n", o1, o2);
            } else {
                printf("***\n"
                       "*** Problème lors de la lecture d'un paquet...\n"
                       "*** Abandon\n"
                       "***\n");
                exit(1);
            }
        }
    }

    // test "weak"
    else if (0 == strcmp(argv[0], "weak")) {

        if (argc <= 2) {
            printf("***\n");
            printf("*** problème, pas assez d'arguments...\n");
            printf("*** Abandon\n");
            exit(1);
        }

        int n = argc - 2;
        byte* K = malloc(sizeof(byte) * n);
        for (int i = 0; i < n; i++) {
            K[i] = strtol(argv[i + 1], NULL, 16);
        }
        byte o1;
        o1 = strtol(argv[argc - 1], NULL, 16);

        printf("\n\nfonction weak\n"
               "-------------\n");
        printf("n = %d\n", n);
        printf("K = ");
        for (int i = 0; i < n; i++) {
            printf("%02X ", K[i]);
        }
        printf("\no = %02X\n", o1);

        byte prediction;

        if (weak(n, K, o1, 0, &prediction)) {
            printf("L'IV est faible.\n");
            printf("La prédiction correspondante est %02X.\n", prediction);
        } else {
            printf("L'IV n'est pas faible.\n");
        }
    }

    else {
        printf("unknown test %s...\n", argv[0]);
        help();
    }
    return 0;
}
