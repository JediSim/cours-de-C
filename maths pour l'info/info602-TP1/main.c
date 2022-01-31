#include "tp1.h"

/*
 * affiche un message de debug si la constante VERBOSE est suffisament grande
 */
int VERBOSE = 0;
void DEBUG(int v, char* format, ...)
{
    va_list args;
    if (v <= VERBOSE) {
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
    }
}

/*
 * ajoute des erreurs sur un mot
 * chaque bit a une probabilité p d'étre modifié
 */
mot bruite_mot(mot m, double p)
{
    mot err = 0;
    for (int i = 0; i < 32; i++) {
        err = err << 1;
        if (rand() / (double)RAND_MAX < p) {
            err |= 1;
        }
    }
    return err ^ m;
}

/*
 * fait des tests et quelques statistiques
 */
void statistiques(int nb_tests, double proba,
    int* nb_mots_modifies,   // nombre de mots envoyés avec une erreur
    int* nb_mots_incorrects, // nombre de mots reçus avec une erreur
    int* nb_bits_modifies,   // nombre de bits envoyés avec une erreur
    int* nb_bits_incorrects  // nombre de bits reçus avec une erreur
)
{

    mot m, err, c, C;

    *nb_mots_incorrects = 0;
    *nb_mots_modifies = 0;
    *nb_bits_incorrects = 0;
    *nb_bits_modifies = 0;
    int w;

    for (int i = 0; i < nb_tests; i++) {
        // on pioche un mot aléatoire
        m = rand();
        m = m & ((1 << 12) - 1);

        // on le code
        c = code_golay(m);

        // on génère une erreur
        err = bruite_mot(c, proba);
        err &= ((1 << 24) - 1);
        int p = poids(err ^ c);
        *nb_bits_modifies += p;
        *nb_mots_modifies += (p > 0);

        // on essaie de la corriger
        C = correction_golay(err);
        C = C >> 11;

        err = C ^ m;
        w = poids(err);
        if (w != 0) {
            *nb_mots_incorrects += 1;
            *nb_bits_incorrects += w;
        }
    }
}

void print_usage(char* name)
{
    printf("Utilisation :\n");
    printf("  %s options\n", name);

    printf("actions sur un mot :\n");
    printf("    -c MOT    code le mot de 12 bits sur 23 bits\n");
    printf("    -C MOT    code le mot de 12 bits sur 24 bits\n");
    printf("    -s MOT    calcule le syndrome du mot 23 bits\n");
    printf("    -d MOT    décode (avec correction d'erreurs) le mot de 23 bits sur 12 bits\n");
    printf("    -D MOT    décode (avec correction d'erreurs) le mot de 24 bits sur 12 bits\n");
    printf("    -e MOT    décode (avec correction d'erreurs exhaustive) le mot de 23 bits sur 12 bits\n");
    printf("    -E MOT    décode (avec correction d'erreurs exhaustive) le mot de 24 bits sur 12 bits\n");

    printf("\ntests aléatoires :\n");
    printf("    -n NB     nombre de mots à tester\n");
    printf("    -p X      probabilité d'erreur (pourcentage) sur chaque bit\n");

    printf("\ndivers :\n");
    printf("    -x        utilise la base hexadécimal plutôt que la base 2\n");
    printf("    -v        augmente le niveau des affichages de débogage\n");
    printf("    -T ARG    lance la fonction de test\n");
    printf("    -h        ce message\n");
}

int main(int argc, char** argv)
{

    // initialisation pour l'aléatoire...
    time_t graine;
    time(&graine);
    srand(graine);

    int opt;
    if (argc == 1) {
        print_usage(argv[0]);
        exit(-1);
    }

    mot m = 0;
    int nb_stat_tests = 1000;
    int stat_test = 0;
    int test = 0;
    double proba = 1.0 / 10;
    int base = 2;
    mot c;
    while ((opt = getopt(argc, argv, "hTc:d:C:D:s:n:p:xve:E:")) != -1) {
        switch (opt) {
        case 'h':
            print_usage(argv[0]);
            exit(0);
            break;
        case 'x':
            base = 16;
            break;
        case 'T':
            test = 1;
            break;
        case 'c':
            if (base == 16) {
                m = strtol(optarg, NULL, 16);
            } else {
                m = strtol(optarg, NULL, 2);
            }
            c = code_golay(m);
            printf("code_golay: ");
            if (base == 16) {
                printf("%03x  =>  %06x\n", m, c);
            } else {
                print_bin(m, 12);
                printf("  =>  ");
                print_bin(c, 23);
                printf("\n");
            }
            break;
        case 'C':
            if (base == 16) {
                m = strtol(optarg, NULL, 16);
            } else {
                m = strtol(optarg, NULL, 2);
            }
            c = code_golay_etendu(m);
            printf("code_golay_etendu: ");
            if (base == 16) {
                printf("%03x  =>  %06x\n", m, c);
            } else {
                print_bin(m, 12);
                printf("  =>  ");
                print_bin(c, 24);
                printf("\n");
            }
            break;
        case 's':
            if (base == 16) {
                m = strtol(optarg, NULL, 16);
            } else {
                m = strtol(optarg, NULL, 2);
            }
            c = syndrome_golay(m);
            printf("syndrome_golay: ");
            if (base == 16) {
                printf("%06x  =>  %03x\n", m, c);
            } else {
                print_bin(m, 23);
                printf("  =>  ");
                print_bin(c, 11);
                printf("\n");
            }
            break;
        case 'd':
        case 'e':
            if (base == 16) {
                m = strtol(optarg, NULL, 16);
            } else {
                m = strtol(optarg, NULL, 2);
            }
            if (opt == 'd') {
                c = correction_golay(m);
            } else {
                c = correction_exhaustive_golay(m);
            }
            c = c >> 11;
            printf("correction_golay%s: ", opt == 'e' ? "_exhaustive" : "");
            if (base == 16) {
                printf("%06x  =>  %03x\n", m, c);
            } else {
                print_bin(m, 23);
                printf("  =>  ");
                print_bin(c, 12);
                printf("\n");
            }
            break;
        case 'D':
        case 'E':
            if (base == 16) {
                m = strtol(optarg, NULL, 16);
            } else {
                m = strtol(optarg, NULL, 2);
            }
            m = m >> 1;
            if (opt == 'D') {
                c = correction_golay(m);
            } else {
                c = correction_exhaustive_golay(m);
            }
            c = c >> 11;
            printf("correction_golay%s (étendu) : ", opt == 'e' ? "_exhaustive" : "");
            if (base == 16) {
                printf("%06x  =>  %03x\n", m, c);
            } else {
                print_bin(m, 23);
                printf("  =>  ");
                print_bin(c, 12);
                printf("\n");
            }
            break;
        case 'n':
            nb_stat_tests = atoi(optarg);
            stat_test = 1;
            break;
        case 'p':
            proba = atof(optarg) / 100;
            stat_test = 1;
            break;
        case 'v':
            VERBOSE++;
            break;
        default: /* '?' */
            printf("%s -h    pour avoir la liste des options\n", argv[0]);
            exit(-1);
        }
    }

    if (argc > optind && test == 0) {
        printf("*** Attention, certaines options de la ligne de commande sont ignorées :\n    ");
        for (int i = optind; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
        printf("*** Abandon...");
        exit(1);
    }

    if (stat_test == 1) {
        int nb_mots_modifies = 0;
        int nb_mots_incorrects = 0;
        int nb_bits_modifies = 0;
        int nb_bits_incorrects = 0;
        statistiques(
            nb_stat_tests, proba, &nb_mots_modifies, &nb_mots_incorrects, &nb_bits_modifies, &nb_bits_incorrects);
        printf("Tests sur un canal symétrique binaire avec taux d'erreur de %.2f%%.\n", proba * 100);
        printf("  %d mots ont été codés et envoyés\n", nb_stat_tests);
        printf("  %d mots ont étés modifiés\n", nb_mots_modifies);
        printf("  %d bits ont étés modifiés\n", nb_bits_modifies);
        printf("  %d mots n'ont pas étés corrigés correctement (%.4f%%)\n", nb_mots_incorrects,
            (100.0 * nb_mots_incorrects) / nb_stat_tests);
        printf("  %d bits n'ont pas étés corrigés correctement (%.4f%%)\n", nb_bits_incorrects,
            (100.0 * nb_bits_incorrects) / (12.0 * nb_stat_tests));
    }

    if (test > 0) {
        argc -= optind;
        argv += optind;
        return perform_tests(argc, argv);
    }

    return 0;
}
// vim: tw=120
