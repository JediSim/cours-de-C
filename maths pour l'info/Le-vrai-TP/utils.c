/*
 * info602,
 * fonctions diverses pour le TP2
 */
#include "tp2.h"

// control the verbosity of debug messages
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
 * modulo mathématique sur les entiers 64 bits
 */
int64_t mod(int64_t x, int64_t m) { return ((x % m) + m) % m; }

/*
 * affiche un entier t bits en binaire
 */
void print_bin(word m, int t)
{
    for (int i = 0; i < t; i++) {
        printf("%s%d", i == 0 ? "" : " ", BIT(t - 1 - i, m));
    }
}

/*
 * affiche un tableau d'entier comme une matrice de bits
 */
void print_M(word* M, int nb_lignes)
{
    for (int i = 0; i < nb_lignes; i++) {
        print_bin(M[i], nb_lignes + 1);
        printf("\n");
    }
    printf("\n");
}

/*
 * calcule le pgcd et les nombres de Bezout pour a et b
 * (les autres arguments sont utilisés pour renvoyer le résultat)
 */
void gcd_bezout(int64_t* g, int64_t* x, int64_t* y, int64_t a, int64_t b)
{
    int64_t xx = 0;
    int64_t old_x = 1;
    int64_t yy = 1;
    int64_t old_y = 0;
    int64_t rr = b;
    int64_t old_r = a;
    int64_t q, tmp;
    while (rr != 0) {
        q = old_r / rr;
        tmp = rr;
        rr = old_r - q * tmp;
        old_r = tmp;
        tmp = xx;
        xx = old_x - q * tmp;
        old_x = tmp;
        tmp = yy;
        yy = old_y - q * tmp;
        old_y = tmp;
    }
    if (old_r < 0) {
        *g = -old_r;
    } else {
        *g = old_r;
    }
    *x = old_x;
    *y = old_y;
    if (-*g == a * *x + b * *y) {
        *x = -*x;
        *y = -*y;
    }
    assert(*g > 0);
    assert(a * *x + b * *y == *g);
}

/*
 * calcul le pgcd de a et b
 */
int64_t gcd(int64_t a, int64_t b)
{
    int64_t g, x, y;
    gcd_bezout(&g, &x, &y, a, b);
    return g;
}

/*
 * lit une matrice booléenne depuis stdin et renvoie un pointeur. Le nombre
 * d'équations est renvoyée par l'argument nb_lignes.
 * la matrice est entrée sous la forme
 *      01011
 *      11011
 *      00101
 *      11101
 * ATTENTION, cette fonction alloue une zone mémoire.
 */
word* read_matrix(int* nb_lines)
{
    char s[256];
    word* M = NULL;
    int n = 0;
    int i = 0;
    *nb_lines = 0;
    while (fgets(s, 256, stdin)) {
        n = strlen(s);
        if (n == 0)
            break;
        if (s[n - 1] == '\n') {
            s[n - 1] = '\0';
            n--;
        }
        if (n == 0)
            continue;
        if (*nb_lines > 0 && i >= *nb_lines) {
            printf("*** OOPS, too many lines in matrix\n");
            printf("*** aborting\n");
            exit(1);
        }
        if (M == NULL) {
            M = malloc(sizeof(word) * n - 1);
            *nb_lines = n - 1;
        }
        M[i++] = strtoll(s, NULL, 2);
    }
    return M;
}
