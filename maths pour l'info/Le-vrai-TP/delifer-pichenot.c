// Pichenot Simon, Delifer Paul
/*
 * info602, TP2 : générateurs pseudo aléatoires simples
    Delifer Paul L3-Info*/

#include "tp2.h"
#include <assert.h>

/*
 * calcule l'inverse de a modulo m
 * (renvoie 0 si a n'est pas premier avec m ou si le résultat est incorrect)
 */
int64_t invert_mod(int64_t a, int64_t m)
{
    int64_t g = 0;
    int64_t x = 0;
    int64_t y = 0;
    gcd_bezout(&g, &x, &y, a, m);
    return (g == 1) ? mod(x, m) : 0;
}

/*
 * craque un générateur congruentiel en cherchant le module, puis les nombres
 * a et c à partir de nombre générés
 *
 * Le tableau 'X' contient les 'nb' premiers nombres générés.
 * La fonction renvoie 1 si le générateur trouvé génère bien la liste donnée
 * et 0 sinon.
 */
int LCG_crack_ac(int nb, const int64_t *X, int64_t m, int64_t *a, int64_t *c)
{
    // c = X22-X3X1/X2-X1 (x2-X1 !=0);
    // a = (x2-(X22-X3X1/X2-X1))/x1 (x1 != 0);
    for (int i = 0; i < nb; i++)
    {
        if (invert_mod(X[i] - X[i + 1], m) != 0)
        {
            *a = mod(((X[i + 1]) - (X[i + 2])) / (X - (X + 1)), m);
            *c = mod(((X[i]) * (X[i + 2]) - (X[i + 1]) * (X[i + 1])) / (X[i] - (X[i + 1])), m);
            return 1;
        }
    }
    return 0;
}
// 

// Lorsque le module m du générateur congruentiel est inconnu, il faut faire un peu plus de calculs:
//     si x1, ... xn sont des nombres consécutifs donnés par le générateur, ils vérifient xk = a xk-1 + c (mod m).
//     Les différences successives yk = (xk+1 - xk) vérifient yk+1 = a yk (mod m) et donc yk+1 = a2 yk-1 (mod m).
//     On peut déduire de tout ça que yk+1 yk-1 - yk2 = 0 (mod m)
//     Autrement dit, chacun des nombres zk = yk+1 yk-1 - yk2 est un multiple de m.
//     Le nombre m est donc un diviseur commun de tous les nombres zk. Le nombre m est en fait le pgcd de tous les nombres zk avec une très forte probabilité.

int iMoinsSuivant(int64_t*X,int i ){
    return X[i]+X[i-1]; 
}
int LCG_crack_m(int nb, const int64_t *X, int64_t *m) { 
    if (nb>5){
        *m= X[1]-X[0]* X[i]
        return 1;
    }
    return 0;
     }

int LCG_crack_check(int nb, const int64_t *X, int64_t m, int64_t a, int64_t c)
{

    return -1;
}

/*
 * diagonalise une matrice booléenne de taille n x n+1
 */
int gauss(word *M, int nb_lignes) { return -1; }

/*
 * craque un générateur linéaire "fibonacci" en cherchant les "taps" qui
 * permettent de regénérer la suite.
 * Le tableau 'X' contient les 'nb' premiers bits générés par le
 * générateur.
 * La fonction renvoie 1 si les taps permettent de regénérer la suite, et 0
 * sinon.
 */
int LFSR_crack(int nb, const int *X, word *taps) { return -1; }
