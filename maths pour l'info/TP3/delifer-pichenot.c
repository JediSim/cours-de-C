/**********************************************************************
 *** craque une clé WEP en utilisant l'attaque du Fluhrer, Mantin et
 *** Shamir.
 *** Les données sont récupérées dans un tube rempli par un
 *** générateur indépendant.
 *** TP3 d'info602 : RC4, WEP et attaque FMS
 *** Delifer Paul & Pichenot Simon
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
int get_data(byte *IV, byte *o1, byte *o2)
{
    // il faut lire les octets qui décrivent le vecteur d'initialisation.
    read(tube_fd, IV, IV_size);
    // ensuite on lit les 2 octets générés avec RC4:
    read(tube_fd, o1, 1);
    read(tube_fd, o2, 1);
    byte EOCODE;
    // il faut ensuite lire l'octet qui suit et vérifier si il vaut 0.
    read(tube_fd, &EOCODE, 1);
    if (EOCODE == 0x00)
        return IV_size;
    return -1;
}

/***
 * récupère un paquet de données WEP générées et vérifie que la clé WEP passée
 * en argument génère bien le même premier octet avec le même vecteur
 * d'initialisation.
 * La fonction renvoie 1 lorsque c'est le cas, et 0 sinon.
 */
int check_byte(byte *cle_WEP)
{
    // TODO...
    return 0;
}

byte indexOf(byte o, byte *P, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (o == P[i])
            return i;
    }
    return -1;
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
int weak(int n, byte *key, byte o1, byte o2, byte *prediction)
{
    byte P[256];

    // init de P[]
    for (int i = 0; i < 256; i++)
        P[i] = i;

    byte j = 0;
    byte tempo;
    // n premiers pas du KSA
    for (int i = 0; i < n; i++)
    {
        j = (j + P[i] + key[i]) % 256;

        // On swap
        tempo = P[i];
        P[i] = P[j];
        P[j] = tempo;
    }

    // On test si le vecteur init est faible
    if ((P[1] < n) && (P[1] + P[P[1]] == n))
    {
        // On calcul la prediction
        *prediction = indexOf(o1, P, 256);

        if (*prediction == (byte)-1)
            return -1;

        *prediction -= j + P[n];

        return 1;
    }
    return 0;
}

void initTabOfOccurence(int tab[])
{
    for (int i = 0; i < 256; i++) tab[i] = 0;
}

byte occurence_index(int tab[])
{
    int max = tab[0];
    byte res = 0;
    for (int i = 0; i < 256; i++)
    {
        if(max < tab[i]){
            res = i;
            max = tab[i];
        } 
    }
    return res;
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
int crack_WEP(byte *cle_WEP)
{
    int tabOfOccurence[256];
    byte prediction, o1, o2;

    byte cle_complete[IV_size + key_size];
    int n = IV_size;

    for (int i = 0; i < key_size; i++)
    {
        initTabOfOccurence(tabOfOccurence);//faut coder ça ???
        //c'est ptetre un peu long 
        // c'est bizarre
        // relance il y avait une erreur
        //encore raté :(
            //cest sur que ça marche chez sinux? yes
            // refait un make
            // lance le generateur et le crack dans le meme terminal
        
        for (int counter = 0, counter_weak = 0; counter < expected_IV && counter_weak < expected_weak_IV; counter++)
        {
            get_data(cle_complete, &o1, &o2);
            if(weak(i, cle_complete, o1, 0, &prediction)) {

                tabOfOccurence[prediction]+=1;
                counter_weak++;
            }
        }
        cle_WEP[i] = occurence_index(tabOfOccurence);
        cle_complete[n] = cle_WEP[i];
        n++;
    }
    return 0;
}
