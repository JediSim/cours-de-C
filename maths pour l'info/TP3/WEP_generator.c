/**********************************************************************
 *** générateur de données "WEP"                                      *
 *** TP3 d'info602 : RC4, WEP et attaque FMS                         *
 *** Pierre Hyvernat                                                  *
 ***
 *** VOUS NE DEVEZ PAS MODIFIER CE FICHIER !
 ***
 **********************************************************************/

#include <assert.h>
#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

/***
 *** type pour les octets
 ***/
typedef unsigned char byte;

/**********************************************************************
 * Le code pour RC4 :                                                 *
 *   - initialisation (RC4_KSA(key, key_size))                      *
 *   - obtention d'un nouvel octet (RC4_PRGA())                       *
 * et une fonction pour générer une clé secrète aléatoire.            *
 **********************************************************************/

/*** état interne du générateur */
typedef struct RC4_state {
    /* la permutation */
    byte P[256];

    /* les compteurs i et j */
    byte i;
    byte j;
} RC4_state;

/*** variable (globale et statique) contenant l'état courant du générateur */
static RC4_state current_state;

/*** fonction auxiliaire : échange deux octets */
void swap(byte* a, byte* b)
{
    byte o;
    o = *a;
    *a = *b;
    *b = o;
}

/************************************************************************
 * RC4, le "key scheduling algorithm" : initialisation de l'état global *
 ************************************************************************/
void RC4_KSA(byte* key, int key_size)
{
    int i, j;

    /* on remet les compteurs à 0 */
    current_state.i = 0;
    current_state.j = 0;

    /* la permutation P est initialement l'identité */
    for (i = 0; i < 256; i++)
        current_state.P[i] = i;

    /* le mélange pour obtenir la permutation... */
    j = 0;
    for (i = 0; i < 256; i++) {
        j = (j + current_state.P[i] + key[i % key_size]) % 256;
        swap(&current_state.P[i], &current_state.P[j]);
    }
}

/**********************************************************************
 * RC4, générer un nouvel octet à partir de l'état courant.           *
 **********************************************************************/
byte RC4_PRGA(void)
{
    byte k;

    current_state.i += 1;
    current_state.j += current_state.P[current_state.i];
    swap(
        &current_state.P[current_state.i], &current_state.P[current_state.j]);

    k = (current_state.P[current_state.i] + current_state.P[current_state.j]);
    return current_state.P[k];
}

/**********************************************************************
 * génération d'une clé aléatoire                                     *
 **********************************************************************/
byte* random_key(int key_size)
{
    byte* key = malloc(key_size);
    for (int i = 0; i < key_size; i++) {
        key[i] = rand() % 256;
    }
    return key;
}

/**********************************************************************
 * quelques tests pour RC4                                            *
 **********************************************************************/

/* "chiffre" une suite d'octets en initialisant RC4 à partir d'une clé :
 *   - "l" est la taille de la clé,
 *   - "key" est la clé secrète
 *   - "n" est la taille du message clair
 *   - "texte" est le message clair
 */
byte* test_chiffre(int l, byte* key, int n, byte* texte)
{
    int i;

    byte* cle_RC4 = malloc(sizeof(byte) * l);
    for (i = 0; i < l; i++)
        cle_RC4[i] = key[i];

    byte* resultat = malloc(n * sizeof(byte));

    RC4_KSA(cle_RC4, l);
    for (i = 0; i < n; i++)
        resultat[i] = texte[i] ^ RC4_PRGA();

    return resultat;
}

/* "chiffre" est une chaine de caractères en initialisant RC4 à partir d'une
 * clé, elle même donnée comme chaine de caractères :
 *   - "key" est la clé secrète
 *   - "texte" est le message clair
 */
byte* chiffre_chaine(char* key, char* texte)
{
    return (
        test_chiffre(strlen(key), (byte*)key, strlen(texte), (byte*)texte));
}

/* idem, mais vérifie si le résultat est bien celui attendu
 * renvoie 1  si le test est OK, et "-n" si le test a échoué sur l'octet "n"
 */
int test_chaine(char* key, char* texte, byte* resultat)
{
    byte* rc4 = chiffre_chaine(key, texte);
    int OK = 1;
    for (int i = 0; i < (int)strlen(texte); i++) {
        if (rc4[i] != resultat[i]) {
            OK = -i;
            break;
        }
    }
    free(rc4);
    return OK;
}

void test_RC4(void)
{
    printf("\n");
    printf("################\n");
    printf("# TESTS RC4... #\n");
    printf("################\n\n");

    {
        char* key = "Key";
        char* texte = "Plaintext";
        byte R[] = { 0xbb, 0xf3, 0x16, 0xe8, 0xd9, 0x40, 0xaf, 0x0a, 0xd3 };
        int OK;
        printf("Test 1 : key = \"%s\" et texte = \"%s\" :\n", key, texte);
        OK = test_chaine(key, texte, R);
        if (OK == 1) {
            printf("  OK.\n");
        } else {
            printf("  OOPS : erreur à l'octet %d.\n", -OK);
        }
    }
    {
        char* key = "Wiki";
        char* texte = "pedia";
        byte R[] = { 0x10, 0x21, 0xbf, 0x04, 0x20 };
        int OK;
        printf("Test 2 : key = \"%s\" et texte = \"%s\" :\n", key, texte);
        OK = test_chaine(key, texte, R);
        if (OK == 1) {
            printf("  OK.\n");
        } else {
            printf("  OOPS : erreur à l'octet %d.\n", -OK);
        }
    }
    {
        char* key = "Secret";
        char* texte = "Attack at dawn";
        byte R[] = { 0x45, 0xA0, 0x1F, 0x64, 0x5F, 0xC3, 0x5B, 0x38, 0x35,
            0x52, 0x54, 0x4B, 0x9B, 0xF5 };
        int OK;
        printf("Test 3 : key = \"%s\" et texte = \"%s\" :\n", key, texte);
        OK = test_chaine(key, texte, R);
        if (OK == 1) {
            printf("  OK.\n");
        } else {
            printf("  OOPS : erreur à l'octet %d.\n", -OK);
        }
    }
}

/*** variables globales */
int key_size = 13;
int IV_size = 3;
byte* key = NULL;
byte* RC4_key = NULL;
char* output_filename = NULL;
int fifo_wep = 0;

/* affiche l'aide */
void display_help(char* exe)
{
    printf("Usage : %s [options]\n", exe);
    printf("\n");
    printf(
        "  --key_size=N, -lN\n"
        "      taille en octets de la clé WEP aléatoire (défaut : 13)\n"
        "  --IV_size=N, -iN\n"
        "      taille en octets des vecteurs d'initialisation (défaut : 3)\n"
        "  --key=\"KEY\", -K\"KEY\"\n"
        "      utilise la clé donnée en argument sous la forme\n"
        "      \".. .. .. ..\" (en hexadécimal)\n"
        "  --easy, -e\n"
        "      utilise les vecteurs d'initialisation (n+3, 255, ...)\n"
        "      (implique une taille d'IV de 3)\n"
        "  --tube=FILENAME, -tFILENAME\n"
        "      spécifie le nom du tube à utiliser (défaut: data_WEP)\n"
        "  --file=FILENAME, -fFILENAME\n"
        "      spécifie le nom du fichier à utiliser (défaut: data_WEP)\n"
        "  --nb_packets=N, -nN\n"
        "      spécifie le nombre de paquets à générer (défaut: 10000000)\n"
        "  --increment, -I\n"
        "      les vecteurs d'initialisations sont simplement incrémentés\n"
        "  --show_key, -s\n"
        "      affiche la clé utilisée\n"
        "  --help, -h\n"
        "      affiche ce message\n");
}

/*** génère une key à partir d'une chaine de caractères représentant une clé
 * en hexadécimal... */
int string_to_key(char* s, int key_size)
{
    unsigned o;
    int i, j;
    for (i = 0; i < key_size && 3 * i < (int)strlen(s); i++) {
        sscanf(&s[3 * i], "%02x ", &o);
        key[i] = (byte)o;
    }
    for (j = i; j < key_size; j++)
        key[j] = 0;
    return i;
}

/*** affiche la clé sur stdout (signal SIGUSR1) */
void show_key(int nothing)
{
    (void)nothing; // pour éviter le warning "unused variable nothing"
    printf("clé utilisée: ");
    for (int i = 0; i < key_size; i++)
        printf("%02x ", key[i]);
    printf("\n");
}

/*** supprime le tube (signal SIGINT) */
void clean(int nothing)
{
    (void)nothing; // pour éviter le warning "unused variable nothing"
    printf("Bye...\n");
    close(fifo_wep);
    unlink(output_filename);
    exit(0);
}

int main(int argc, char* argv[])
{
    signal(SIGUSR1, show_key);
    signal(SIGINT, clean);

    /* initialisation du générateur aléatoire */
    struct timeval temps;
    gettimeofday(&temps, NULL);
    srand(temps.tv_usec);

    int easy = 0;
    int increment = 0;
    int show = 0;
    int use_fifo = 1;
    int nb_packets = 10000000;

    static const struct option long_options[]
        = { { "key_size", required_argument, NULL, 'l' },
              { "IV_size", required_argument, NULL, 'i' },
              { "key", required_argument, NULL, 'K' },
              { "easy", no_argument, NULL, 'e' },
              { "tube", required_argument, NULL, 't' },
              { "file", required_argument, NULL, 'f' },
              { "nb_packets", required_argument, NULL, 'n' },
              { "increment", no_argument, NULL, 'I' },
              { "help", no_argument, NULL, 'h' },
              { "show_key", no_argument, NULL, 's' }, { NULL, 0, NULL, 0 } };

    int opt;
    while ((opt = getopt_long(argc, argv, "hl:i:K:Iset:f:n:", long_options, NULL))
        != -1) {
        switch (opt) {
        case 'h':
            display_help(argv[0]);
            return (0);
            break;
        case 'l':
            key_size = atoi(optarg);
            break;
        case 'i':
            IV_size = atoi(optarg);
            break;
        case 'I':
            increment = 1;
            break;
        case 'e':
            easy = 1;
            break;
        case 's':
            show = 1;
            break;
        case 'K':
            key = malloc(key_size);
            int c = string_to_key(optarg, key_size);
            if (c < key_size)
                printf("*** Attention : la clé fournie est trop courte, elle "
                       "a été complétée par des \"00\".\n");
            if (c > key_size)
                printf("*** Attention : la clé fournie est trop longue, elle "
                       "a été tronquée.\n");
            break;
        case 't':
            output_filename = strdup(optarg);
            use_fifo = 1;
            break;
        case 'f':
            output_filename = strdup(optarg);
            use_fifo = 0;
            break;
        case 'n':
            nb_packets = atoi(optarg);
            use_fifo = 0;
            break;
        default: /* '?' */
            printf("option non reconnue...\n\n");
            display_help(argv[0]);
            return (-1);
        }
    }

    if (argc > optind) {
        printf("*** Attention, certaines options de la ligne de commande "
               "sont ignorées :\n        ");
        for (int i = optind; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
        printf("*** Abandon...");
        exit(1);
    }

    if (output_filename == NULL) {
        output_filename = strdup("data_WEP");
    }

    if (easy != 0) {
        if (IV_size != 3) {
            printf("*** L'option '--easy' n'est compatible qu'avec une "
                   "taille d'IV de 3\n");
            printf("*** Abandon...");
            exit(1);
        }
        printf(
            "On teste uniquement les vecteurs de la forme [n+3,255,...]\n");
    }

    /* on supprime le fichier (ou tube) précédent */
    unlink(output_filename);

    if (use_fifo == 1) {
        if (0 == mknod(output_filename, S_IRUSR | S_IWUSR | S_IFIFO, 0)) {
            /* Attention, il faut ouvrir le tube en lecture/écriture pour conserver
         * au moins une connection "lecture" à tout moment. */
            fifo_wep = open(output_filename, O_RDWR);
            if (-1 == fifo_wep) {
                printf("Erreur lors de l'ouverture du tube %s.\n", output_filename);
                printf("On abandonne tout.\n");
                exit(-1);
            }
        } else {
            printf("Erreur lors de la création du tube %s.\n", output_filename);
            printf("On essaie avec un fichier...\n");
            printf("Vous pouvez modifier le nombre de paquets générés avec l'option --nb_packets\n");
            use_fifo = 0;
        }
    }
    if (use_fifo == 0) {
        if (-1 == (fifo_wep = open(output_filename, O_WRONLY | O_CREAT, 0644))) {
            printf("Erreur lors de la création du fichier %s.\n", output_filename);
            printf("On abandonne tout.\n");
            exit(-1);
        }
    };

    if (key == NULL) {
        /* on tire une clé */
        key = random_key(key_size);
    }
    if (show || use_fifo == 0)
        show_key(0);

    /* on initialise la clé RC4 : les premiers octets seront donnés par les
     * IV, les derniers octets sont donnés par la clé WEP... */
    RC4_key = malloc((IV_size + key_size) * sizeof(byte));
    for (int i = 0; i < IV_size; i++)
        RC4_key[i] = 0;
    for (int i = IV_size; i < IV_size + key_size; i++)
        RC4_key[i] = key[i - IV_size];

    /* on génère des vecteurs d'initialisation et des premiers octets avec RC4
     */
    int nb_IV = 0;
    byte output[IV_size + 3]; // "IV_size+3" pour avoir de la place de mettre
                              // les 2 octets générés par RC4 et 0000

    if (use_fifo == 1) {
        printf("Pour afficher la clé, vous pouvez utiliser la commande\n"
               "   $ kill -s SIGUSR1 %d\n",
            getpid());
    }

    for (int j = 0; use_fifo || j < nb_packets; j++) {
        if (increment == 0) {
            for (int i = 0; i < IV_size; i++)
                RC4_key[i] = rand() % 256;
            if (easy != 0)
                RC4_key[1] = 255;
        } else {
            for (int i = IV_size - 1; i >= 0; i--) {
                RC4_key[i] = (RC4_key[i] + 1) % 256;
                if (RC4_key[i] != 0)
                    break;
            }
        }
        nb_IV++;

        /* on initialise RC4 avec le vecteur d'initialisation courant,
         * puis on demande le premier octet */
        RC4_KSA(RC4_key, IV_size + key_size);

        for (int i = 0; i < IV_size; i++) {
            output[i] = RC4_key[i];
        }
        output[IV_size] = RC4_PRGA();
        output[IV_size + 1] = RC4_PRGA();
        output[IV_size + 2] = 0;

        /* printf("  %i: [%02x, %02x, %02x] -> %02x\n", nb_IV, IV[0], IV[1],
         * IV[2], IV[3]); */
        if (IV_size + 3 != write(fifo_wep, output, IV_size + 3)) {
            printf("Problème lors de l'écriture dans le tube...\n");
            printf("On abandonne tout.\n");
            exit(-1);
        }
    }
    return 0;
}
