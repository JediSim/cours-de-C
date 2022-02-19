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
 */

#ifndef _TP_PRNG_H
#define _TP_PRNG_H

#include <fcntl.h>
#include <getopt.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*** type pour les octets */
typedef unsigned char byte;

/*** fonction d'affichage de debogage */
void DEBUG(int v, char* format, ...);

/*** variables globales */
extern int IV_size;          // taille des vecteurs d'initialisation
extern int key_size;         // taille des clés WEP
extern int expected_weak_IV; // nombre de vecteurs faibles à considérer pour
// faire une prédiction sur un octet de la clé
extern int expected_IV;      // nombre de vecteurs à considérer pour faire une
// prédiction sur un octet de la clé
extern int nb_tests;         // nombre de tests à faire pour vérifier que la clé
// trouvée est correcte
extern char* tube;           // nom du tube contenant les données générées
extern int tube_fd;          // descripteur de fichier pour ce tube
extern int VERBOSE;          // niveau de détails d'affichages

/*** récupère des données WEP dans le tube */
int get_data(byte* IV, byte* o1, byte* o2);

/*** vérifie que la clé génère les mêmes octets que ceux que l'on
 * peut récupérer dans le tube */
int check_byte(byte* cle_WEP);

/*** teste un vecteur d'initialisation */
int weak(int n, byte* key, byte o1, byte o2, byte* prediction);

/*** craque une clé WEP complète */
int crack_WEP(byte* cle_WEP);

/*** la fonction de test */
int perform_tests(int argc, char** argv);

#endif /* _TP_PRNG_H */
