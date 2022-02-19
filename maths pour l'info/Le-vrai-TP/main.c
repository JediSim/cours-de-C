#include "tp2.h"

void print_usage(char* cmd)
{
    printf("  Usage:\n");
    printf("  \n");
    printf("  As a generator:\n");
    printf("    %s -g LCG A C M          generate random numbers using an LCG\n", cmd);
    printf("    %s -g LFSR T1 ... Tn     generate random numbers using an LFSR\n", cmd);

    printf("  In all cases, the option -s seed allows to choose the seed, in decimal (default: 1)\n");
    printf("  and the option -n NB allows to choose how many numbers will be generated (default: 10)\n");
    printf("  \n");

    printf("  To crack a generator:\n");
    printf("    %s -c LCG X1 X2 ...      attempt to recover the LCG from the sequence of integers X1,X2,...\n", cmd);
    printf("    %s -m M -c LCG X1 X2 ... attempt to recover the LCG from the sequence of integers X1,X2,... with "
           "modulus M\n",
        cmd);
    printf("    %s -c LFSR BB...         attempt to recover the LFSR from the sequence of bits BB,...\n", cmd);
    printf("  \n");
    printf("  Internal tests:\n");
    printf("    %s -T ARG                execute the 'test' function\n", cmd);
    printf("  \n");
}

#define NONE 0
#define LCG 1
#define LFSR 2
#define GALOIS 3
#define GENERATE 3
#define CRACK 4
#define TESTS 5

int VERBOSE = 0;
int main(int argc, char** argv)
{

    int opt;

    if (argc == 1) {
        print_usage(argv[0]);
        exit(-1);
    }

    int nb_randoms = 10;
    int type_prng = NONE;
    int seed = 1;
    int action = GENERATE;
    int64_t modulus = 0;
    while ((opt = getopt(argc, argv, "hn:g:s:c:m:vT")) != -1) {
        switch (opt) {
        case 'h':
            print_usage(argv[0]);
            exit(0);
        case 'T':
            type_prng = TESTS;
            break;
        case 's':
            seed = strtoul(optarg, NULL, 10);
            break;
        case 'g':
            if (0 == strcmp("LFSR", optarg)) {
                type_prng = LFSR;
                break;
            }
            if (0 == strcmp("LCG", optarg)) {
                type_prng = LCG;
                break;
            }
            /* if (0 == strcmp("galois", optarg)) { */
            /*     type_prng = GALOIS; */
            /*     break; */
            /* } */
            /* printf("allowed types for prng: LFSR, galois and LCG\n"); */
            printf("allowed types for prng: LFSR and LCG\n");
            exit(0);
            break;
        case 'c':
            if (0 == strcmp("LFSR", optarg)) {
                type_prng = LFSR;
                action = CRACK;
                break;
            }
            if (0 == strcmp("LCG", optarg)) {
                type_prng = LCG;
                action = CRACK;
                break;
            }
            printf("allowed types for prng: LFSR and LCG\n");
            exit(0);
            break;
        case 'm':
            modulus = strtoul(optarg, NULL, 10);
            break;
        case 'n':
            nb_randoms = atoi(optarg);
            break;
        case 'v':
            VERBOSE++;
            break;
        default: /* '?' */
            printf("%s -h   to get a help message\n", argv[0]);
            exit(-1);
        }
    }

    if (type_prng == TESTS) {
        argc -= optind;
        argv += optind;
        return perform_tests(argc, argv);
    } else if (type_prng == LCG && action == GENERATE) {
        if (argc - optind != 3) {
            print_usage(argv[0]);
            exit(-1);
        }
        int64_t a, c, m;
        a = strtoul(argv[optind], NULL, 10);
        c = strtoul(argv[optind + 1], NULL, 10);
        m = strtoul(argv[optind + 2], NULL, 10);
        LCG_init(a, c, m);
        LCG_seed(seed);
        LCG_show();
        for (int i = 0; i < nb_randoms; i++) {
            printf("%" PRId64, LCG_random());
        }
        printf("\n");
        return 0;
    } else if (type_prng == LFSR && action == GENERATE) {
        word taps = 0;
        for (int i = optind; i < argc; i++) {
            taps |= 1 << (atoi(argv[i]) - 1);
        }
        LFSR_init(taps);
        if (seed == 0) {
            printf("The seed of a linear feedback shift register generator "
                   "cannot be 0!\n");
            exit(1);
        }
        LFSR_seed(seed);
        LFSR_show();
        for (int i = 0; i < nb_randoms; i++) {
            printf("%d", LFSR_random_bit());
        }
        printf("\n");
    } else if (type_prng == LCG && action == CRACK) {
        int64_t* table = malloc((argc - optind) * sizeof(int64_t));
        for (int i = optind; i < argc; i++) {
            table[i - optind] = strtoul(argv[i], NULL, 10);
        }
        int64_t a, c;
        a = 0;
        c = 0;
        int r;
        if (modulus == 0) {
            r = LCG_crack_m(argc - optind, table, &modulus);
            if (r == 0) {
                printf("crack m unsuccessful.\n");
                return 0;
            }
            if (r != 1) {
                printf("LA FONCTION LCG_crack_m DOIT RENVOYER 1 ou 0 (valeur reçue : %d).\n", r);
                return 1;
            }
        }
        r = LCG_crack_ac(argc - optind, table, modulus, &a, &c);
        if (r == 0) {
            printf("crack a,c unsuccessful..\n");
            return 1;
        }
        if (r != 1) {
            printf("LA FONCTION LCG_crack_ac DOIT RENVOYER 1 ou 0 (valeur reçue : %d).\n", r);
            return 1;
        }
        r = LCG_crack_check(argc - optind, table, modulus, a, c);
        if (r == 0) {
            printf("crack check unsuccessful..\n");
            return 1;
        }
        if (r != 1) {
            printf("LA FONCTION LCG_crack_check DOIT RENVOYER 1 ou 0 (valeur reçue : %d).\n", r);
            return 1;
        }

        printf("crack successful:\n");
        LCG_init(a, c, modulus);
        LCG_show();
        return 0;
    } else if (type_prng == LFSR && action == CRACK) {
        char* X = argv[optind];
        int* table = malloc(sizeof(int) * strlen(X));
        word taps = 0;
        for (unsigned i = 0; i < strlen(X); i++) {
            if (X[i] == '0') {
                table[i] = 0;
            } else if (X[i] == '1') {
                table[i] = 1;
            } else {
                printf("The sequence contains more than just bits...\n");
                exit(-1);
            }
        }
        int r = LFSR_crack(strlen(X), table, &taps);
        if (1 == r) {
            printf("crack successful:\n");
            LFSR_init(taps);
            LFSR_show();
            return 0;
        } else if (-1 == r) {
            printf("crack unsuccessful..\n");
            return 1;
        } else {
            printf("LA FONCTION LCG_crack DOIT RENVOYER 1 ou -1 (valeur reçue : %d).\n", r);
            return 1;
        }
    }

    return 0;
}
// vim: textwidth=120
