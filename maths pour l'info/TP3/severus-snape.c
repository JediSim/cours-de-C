/**********************************************************************
 *** craque une clé WEP en utilisant l'attaque du Fluhrer, Mantin et
 *** Shamir.
 *** Les données sont récupérées dans un tube rempli par un
 *** générateur indépendant.
 *** TP3 d'info602 : RC4, WEP et attaque FMS
 *** Lucient Tartempion
 **********************************************************************/

#include "tp3.h"

/***
 * récupère un paquet de données dans le tube (variable globale tube_fd) :
 *   - IV est un tableau de IV_size (variable globale) octets qui contiendra
 *     le vecteur d'initialisation lu,
 *   - o1 et o2 seront les 2 premiers octets générés par RC4 à partir de la
 *     clé WEP (secrète) et le vecteur d'initialisation.
 * La fonction lit également un octet supplémentaire et vérifie qu'il est bien
 * égal à 0x00.
 * Si tout a fonctionné, la fonction renvoie IV_size ; sinon, elle renvoie un
 * nombre strictement négatif.
 */
int get_data(byte* IV, byte* o1, byte* o2)
{
    // TODO...
    return 0;
}

/***
 * récupère un paquet de données WEP générées et vérifie que la clé WEP passée
 * en argument génère bien le même premier octet avec le même vecteur
 * d'initialisation.
 * La fonction renvoie 1 lorsque c'est le cas, et 0 sinon.
 */
int check_byte(byte* cle_WEP)
{
    // TODO...
    return 0;
}

/***
 * teste un vecteur d'initialisation :
 *   - "n" est la taille de la clé déjà connue
 *   - "o1" est le premier octet généré par RC4 avec "IV"
 *   - "o2" est le premier octet généré par RC4 avec "IV"
 *   - "key" contient les morceaux de la clé que l'on a déjà calculés
 *
 * La fonction renvoie 1 si le vecteur d'initialisation était faible,
 * et dans ce cas, la prédiction correspondante est renvoyée dans le
 * dernier paramètre "prediction".
 *
 * Si le vecteur d'initialisation n'était pas faible, cette fonction
 * renvoie 0.
 */
int weak(int n, byte* key, byte o1, byte o2, byte* prediction)
{
    // TODO...
    return 0;
}

/***
 * craque une clé WEP complète
 * L'argument devra contenir la prédiction finale pour la clé complète.
 *
 * Pour chaque prédiction d'un octet de la clé, la fonction attend d'avoir
 * observé
 *   - soit expected_weak_IV (variable globale) vecteur faibles
 *   - soit expected_IV (variable globale) vecteurs
 * Lorsque c'est fait, une prédiction pour l'octet en cours est faite, et la
 * fonction passe à l'octet suivant.
 *
 * La fonction renverra le nombre d'octets de la clé qu'elle a calculé.
 */
int crack_WEP(byte* cle_WEP)
{
    // TODO...

    // ATTENTION, cle_WEP ne contient que la partie fixe de la clé alors que
    // la fonction weak prend en argument la clé complète (partie variable +
    // partie fixe). Il faut donc déclarer une nouvelle variable pour contenir
    // la clé complète.

    return 0;
}
