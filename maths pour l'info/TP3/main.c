/**********************************************************************
 *** craque une clé WEP en utilisant l'attaque du Fluhrer, Mantin et
 *** Shamir.
 *** Les données sont récupérées dans un tube rempli par un
 *** générateur indépendant.
 *** TP3 d'info602 : RC4, WEP et attaque FMS
 *** Pierre Hyvernat
 ***
 *** VOUS NE DEVEZ PAS MODIFIER CE FICHIER !
 ***
 **********************************************************************/

#include "tp3.h"

/*** control the verbosity of debug messages */
int VERBOSE = 0; // niveau d'affichage
void DEBUG(int v, char* format, ...)
{
    va_list args;
    if (v <= VERBOSE) {
        va_start(args, format);
        // vfprintf(stderr, format, args);
        // using stderr is prone to unexpected behaviour as students mix DEBUG
        // and normal printf calls, which are buffered differently and can
        // thus result in out of order messages
        vfprintf(stdout, format, args);
        va_end(args);
    }
}

/*** variables globales */

int IV_size = 3;            // taille des vecteurs d'initialisation
int key_size = 13;          // taille des clés WEP
int expected_weak_IV = 200; // nombre de vecteurs faibles à considérer pour
// faire une prédiction sur un octet de la clé
int expected_IV = 6000000; // nombre de vecteurs à considérer pour faire une
// prédiction sur un octet de la clé
int nb_tests = 10; // nombre de tests à faire pour vérifier que la clé trouvée
// est correcte

char* tube = NULL; // nom du tube contenant les données générées
int tube_fd = -1;  // descripteur de fichier pour ce tube

void display_help(char* exe)
{
    printf("Usage : %s [options]\n", exe);
    printf(
        "\n"
        "  --key_size=N, -lN\n"
        "      taille en octets de la clé WEP aléatoire (défaut : 13)\n"
        "  --IV_size=N, -iN\n"
        "      taille en octets des vecteurs d'initialisation (défaut : 3)\n"
        "  --tube=FILENAME, -tFILENAME\n"
        "      spécifie le nom du tube à utiliser (défaut: data_WEP)\n"
        "  --expected_weak_IV=N, -nN\n"
        "      spécifie le nombre de vecteurs faibles à regarder pour "
        "prédire un octet de la clé\n"
        "  --expected_IV=N, -NN\n"
        "      spécifie le nombre de vecteurs à regarder pour prédire un "
        "octet de la clé\n"
        "  --nb_tests=N\n"
        "      spécifie le nombre de tests à faire sur des nouveaux paquets "
        "après avoir trouvé une clé\n"
        "lorsque les premières prédictions ne fonctionnent pas\n"
        "  --verbose, -v\n"
        "      augmente le niveau de détails de débogage\n"
        "  --test, -T\n"
        "      lance uniquement la fonction de test avec les arguments de la "
        "ligne de commandes\n"
        "  --help, -h\n"
        "      affiche ce message\n");
}

int main(int argc, char* argv[])
{
    /* gestion des option de la ligne de commandes */
    static const struct option long_options[]
        = { { "key_size", required_argument, NULL, 'l' },
              { "IV_size", required_argument, NULL, 'i' },
              { "expected_IV", required_argument, NULL, 'N' },
              { "expected_weak_IV", required_argument, NULL, 'n' },
              { "nb_tests", required_argument, NULL, 'C' },
              { "tube", required_argument, NULL, 't' },
              { "test", no_argument, NULL, 'T' },
              { "help", no_argument, NULL, 'h' },
              { "verbose", no_argument, NULL, 'v' }, { NULL, 0, NULL, 0 } };

    int opt;
    char test = 0;

    while ((opt = getopt_long(argc, argv, "hl:i:n:N:Tv", long_options, NULL))
        != -1) {
        switch (opt) {
        case 'h':
            display_help(argv[0]);
            return (0);
            break;
        case 'C':
            nb_tests = atoi(optarg);
            break;
        case 'l':
            key_size = atoi(optarg);
            break;
        case 'i':
            IV_size = atoi(optarg);
            break;
        case 'n':
            expected_weak_IV = atoi(optarg);
            break;
        case 'N':
            expected_IV = atoi(optarg);
            break;
        case 't':
            tube = strdup(optarg);
            break;
        case 'T':
            test = 1;
            break;
        case 'v':
            VERBOSE++;
            break;
        default: /* '?' */
            printf("option non reconnue...\n\n");
            display_help(argv[0]);
            return (-1);
        }
    }

    if (test > 0) {
        argc -= optind;
        argv += optind;

    } else if (argc > optind) {
        printf("*** Attention, certaines options de la ligne de commande "
               "sont ignorées :\n        ");
        for (int i = optind; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
        printf("*** Abandon...");
        exit(1);
    }

    if (tube == NULL) {
        tube = strdup("data_WEP");
    }

    tube_fd = open(tube, O_RDONLY);
    if (tube_fd < 0) {
        printf("***\n"
               "*** Attention, le tube '%s' n'existe pas...\n"
               "***\n",
            tube);
    }

    byte cle_WEP[key_size];

    if (test != 0) {
        return perform_tests(argc, argv);
    } else {
        crack_WEP(cle_WEP);
        printf("\nclé trouvée: ");
        for (int i = 0; i < key_size; i++)
            printf("%02x ", cle_WEP[i]);
        printf("\n");

        int ok = 0;
        for (int k = 0; k < nb_tests; k++) {
            ok += check_byte(cle_WEP);
        }

        if (nb_tests > 0 && ok == nb_tests) {
            printf("%d tests réussis\n", nb_tests);
            return 0;
        } else if (nb_tests > 0 && ok < nb_tests) {
            printf("%d tests échoués sur %d\n", nb_tests - ok, nb_tests);
            return nb_tests - ok;
        } else {
            // DEBUG(0, "aucun test effectué\n");
            return 0;
        }
    }
}
