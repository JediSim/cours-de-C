/*
 * info602,
 * entêtes pour le tp1
 */

#ifndef _TP1_H
#define _TP1_H
/* bibliothèques qui peuvent servir... */
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <getopt.h> /* gestion des arguments optionels de la ligne de commandes */
#include <inttypes.h>
#include <stdint.h> /* types d'entier avec garantie sur le nombre de bits */
#include <time.h> /* pour initialiser la graine pour générer des nombres aléatoires */

/*
 * variable globale, niveau de d'affichage
 */
extern int VERBOSE;
void DEBUG(int v, char* format, ...);

/*
 * le type des mots
 */
typedef uint32_t mot;

/*
 * renvoie le bit numéro 'i' d'un mot 'm'
 */
int bit(int i, mot m);

/*
 * affiche les 'n' bits de poids faible d'un mot
 */
void print_bin(mot m, int n);

/*
 * renvoie le nombre de '1' dans un mot
 */
int poids(mot m);

/*
 * la matrice génératrice
 */
extern mot golay_A[12];

/*
 * code une suite de 12 bits (bits de poids faible d'un mot) en ajoutant la
 * redondance donnée par la matrice A
 * Le résultat (23 bits ou 24 bits pour la version étendue) est stocké dans
 * les 23 bits de poid faible du mot renvoyé.
 */
mot code_golay(mot entree);

/*
 * décode un mot du code de golay un supprimant les bits de redondance
 */
mot decode_golay(mot m);

/*
 * même chose, mais avec un bit de parité en plus
 */
mot code_golay_etendu(mot entree);

/*
 * la matrice de parité
 */
extern mot golay_H[23];

/*
 * syndrome d'un mot du code de Golay (sans bit de parité)
 */
mot syndrome_golay(mot m);

/*
 * renvoie le décalage circulaire (à droite) de p bits sur un mot de n bits
 */
unsigned decalage_circulaire(mot m, int n, int p);

/*
 * correction d'erreur pour le code de Golay en utilisant la méthode "error
 * trapping" + cyclicité
 */
mot correction_golay(mot m);

/*
 * correction d'erreur pour le code de Golay en utilisant la recherche
 * exhaustive
 */
mot correction_exhaustive_golay(mot m);

/*
 * statistiques de correction sur un canal binaire symétrique
 */
void statistiques(int nb_tests, double proba,
    int* nb_mots_modifies,   // nombre de mots envoyés avec une erreur
    int* nb_mots_incorrects, // nombre de mots reçus avec une erreur
    int* nb_bits_modifies,   // nombre de bits envoyés avec une erreur
    int* nb_bits_incorrects  // nombre de bits reçus avec une erreur
);

/*
 * fonction de test exécutée avec l'argument "-T" depuis la ligne de commande
 */
int perform_tests(int argc, char** argv);

/***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/*
 * ajoute des erreurs sur un mot
 * chaque bit à une probabilité p d'être modifié
 */
mot bruite_mot(mot m, double p);

#endif /* _TP1_H */
