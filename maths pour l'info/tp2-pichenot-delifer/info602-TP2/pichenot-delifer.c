/*
 * info602, TP2 : générateurs pseudo aléatoires simples
 */

#include "tp2.h"
#include <assert.h>

/*
 * calcule l'inverse de a modulo m
 * (renvoie 0 si a n'est pas premier avec m ou si le résultat est incorrect)
 */
int64_t invert_mod(int64_t a, int64_t m) 
{ 
    int x,y,g;
    gcd_bezout(g,x,y,a,m);
    if (g) return x;
    return 0; 
}

/*
 * craque un générateur congruentiel en cherchant le module, puis les nombres
 * a et c à partir de nombre générés
 *
 * Le tableau 'X' contient les 'nb' premiers nombres générés.
 * La fonction renvoie 1 si le générateur trouvé génère bien la liste donnée
 * et 0 sinon.
 */
int LCG_crack_ac(int nb, const int64_t* X, int64_t m, int64_t* a, int64_t* c)
{
    return -1;
}

int LCG_crack_m(int nb, const int64_t* X, int64_t* m) { return -1; }

int LCG_crack_check(int nb, const int64_t* X, int64_t m, int64_t a, int64_t c)
{
    return -1;
}

/*
 * diagonalise une matrice booléenne de taille n x n+1
 */
int gauss(word* M, int nb_lignes) { return -1; }

/*
 * craque un générateur linéaire "fibonacci" en cherchant les "taps" qui
 * permettent de regénérer la suite.
 * Le tableau 'X' contient les 'nb' premiers bits générés par le
 * générateur.
 * La fonction renvoie 1 si les taps permettent de regénérer la suite, et 0
 * sinon.
 */
int LFSR_crack(int nb, const int* X, word* taps) { return -1; }
