/*
 * info602,
 * entêtes pour le tp2
 */

#ifndef _TP_PRNG_H
#define _TP_PRNG_H

#include <assert.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIT(i, m) ((int)(((m) >> (i)) & 1))

// fonction de debug
extern int VERBOSE;
void DEBUG(int v, char* format, ...);

typedef uint64_t word;

/**********************************
 * quelques fonctions utilitaires
 **********************************/

// affiche un entier int64_t en binaire
void print_bin(word m, int t);

// affiche un tableau d'entiers comme une matrice de bits
void print_M(word* M, int t);

// calcule le pgcd et les nombres de Bezout pour a et b
void gcd_bezout(int64_t* g, int64_t* x, int64_t* y, int64_t a, int64_t b);

// calcul le pgcd de a et b
int64_t gcd(int64_t a, int64_t b);

// modulo mathématique (toujours positif)
int64_t mod(int64_t x, int64_t m);

/*********************************
 * Linear congruential generator
 *********************************/

// initialize the current LCG
void LCG_init(int64_t a, int64_t c, int64_t m);

// give the initial seed for the current LCG
void LCG_seed(int64_t seed);

// generate the next number
int64_t LCG_random();

// display the current LCG
void LCG_show();

/**********************************
 * Linear Feedback Shift Register
 **********************************/

// initialize the current LFSR
void LFSR_init(word taps);

// give the initial seed for the current LFSR
void LFSR_seed(word seed);

// generate the next bit
int LFSR_random_bit();

// display the current LFSR
void LFSR_show();

/**********************************
 * À FAIRE
 **********************************/

/*
 * calcule l'inverse de a modulo m
 * (renvoie 0 si a n'est pas premier avec m)
 */
int64_t invert_mod(int64_t a, int64_t m);

/*
 * craque un générateur congruentiel en cherchant le module, puis les nombres
 * a et c à partir de nombre générés
 *
 * Le tableau 'random' contient les 'nb' premiers nombres générés.
 * La fonction renvoie 1 si le générateur trouvé génère bien la liste donnée
 * et 0 sinon.
 */
int LCG_crack_ac(int nb, const int64_t* random, int64_t m, int64_t* a, int64_t* c);
int LCG_crack_m(int nb, const int64_t* random, int64_t* m);
int LCG_crack_check(int nb, const int64_t* random, int64_t a, int64_t c, int64_t m);

/*
 * diagonalise une matrice booléenne de taille n x n+1
 */
int gauss(word* M, int nb_lignes);

/*
 * craque un générateur linéaire "fibonacci" en cherchant les "taps" qui
 * permettent de regénérer la suite.
 * Le tableau 'random' contient les 'nb' premiers bits générés par le
 * générateur.
 * La fonction renvoie 1 si les taps permettent de regénérer la suite, et 0
 * sinon.
 */
int LFSR_crack(int nb, const int* random, word* taps);

/*
 * fonction de test, exécutée par l'argument '-T' de la ligne de commande
 */
int perform_tests(int argc, char** argv);

word* read_matrix(int* nb_lignes);

#endif /* _TP_PRNG_H */
