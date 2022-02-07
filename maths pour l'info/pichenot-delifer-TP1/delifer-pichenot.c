#include "tp1.h"

#define BIT(i, m) ((m)&1)
//#define WORDSIZE 32;

/*
 * renvoie le bit numéro 'i' d'un mot 'm'
 * question 1
 */
int WORDSIZE = 32;
int bit(int i, mot m)
{
    //  On renvoie le bit numéro i en décallant de i le mot m
    return (m >> i) & 1;
}

/*
 * affiche les n bit de poids faible d'un mot
 * question 1
 */
void print_bin(mot m, int n)
{
    int i = n - 1;
    while (i >= 0)
    {
        // On parcourt le mot et on affiche chacun des bits un à un
        printf("%d", (bit(i, m)));
        i--;
    }
}

/*
 * compte le nombre de 1 dans un mot
 * question 2
 */
int poids(mot m)
{
    int resultat = 0;
    for (int i = 0; i < WORDSIZE; i++)
    {
        // Si le premier bit de m est 1
        if (m & 1)
            resultat += 1;
        // On decalle de 1 le mot m
        m >>= 1;
    }
    return resultat;
}

/**********************************************************************
* Code de Golay avec parité
* matrice generatrice: I | G avec G
10101110001
11111001001
11010010101
11000111011.
11001101100.
01100110110.
00110011011.
10110111100.
01011011110.
00101101111.
10111000110.
01011100011
*********************************************************************/

/* question 3 */
mot golay_A[12] = {0x571, 0x7c9, 0x695, 0x63b, 0x66c, 0x336, 0x19b, 0x5bc, 0x2de, 0x16f, 0x5c6, 0x2e3};

/*
 * code une suite de 12 bits (bits de poids faible d'un mot) en ajoutant la
 * redondance donnée par la matrice A
 * Le résultat (23 bits) est stocké dans les 23 bits de poid faible du mot
 * renvoyé.
 * question 3
 */
mot code_golay(mot entree)
{
    mot res = 0;
    for (int i = 0; i < 12; i++)
    {
        // Si le bit est a 1 on fait le xor avec la ligne correspondant
        if (bit(i, entree) == 1)
        {
            // Si le bit i du mot est 1 alors on fait le xor de la ligne avec les lignes precedentes.
            res ^= golay_A[11 - i];
        }
    }
    // On concatene le mot en entree et les bits de redondance.
    return (entree << 11) ^ res;
}

/*
 * décode un mot du code de Golay en supprimant les bits de redondance
 * question 4
 */
mot decode_golay(mot m)
{
    // On decalle de 11 pour sauter les bits de redondances
    return (m >> 11);
}

/*
 * code de Golay étendu: 23 bit du code de Golay, avec un bit de parité
 * question 5
 */
mot code_golay_etendu(mot entree)
{
    entree = code_golay(entree);
    // On concatene un bit de parite au code de Golay.
    return (entree << 1) ^ (poids(entree) & 1);
}

/* matrice de partité */
/* question 6 */
mot golay_H[23] = {0x571,
                   0x7c9,
                   0x695,
                   0x63b,
                   0x66c,
                   0x336,
                   0x19b,
                   0x5bc,
                   0x2de,
                   0x16f,
                   0x5c6,
                   0x2e3,
                   // --------------------
                   0x400,
                   0x200,
                   0x100,
                   0X80,
                   0x40,
                   0x20,
                   0x10,
                   0x8,
                   0x4,
                   0x2,
                   0x1};

/*
 * syndrome d'un mot du code de Golay (sans bit de parité)
 * question 6
 */
mot syndrome_golay(mot m)
{
    // calculer le syndrome de m revient a calculer la multiplication de m par la matrice golay_H

    mot syndrome = 0;
    for (int i = 0; i < 23; i++)
    {
        if (bit(i, m) == 1)
        {
            syndrome ^= golay_H[22 - i]; // multiplier reviens a faire un xor avec la ligne i si le bit i de m est 1.
        }
    }
    return syndrome;
}

/*
 * renvoie le décalage circulaire (à droite) de p bits sur un mot de n bits
 * question 7
 */
mot decalage_circulaire(mot m, int n, int p)
{
    int bitTmp;
    for (int i = 0; i < p; i++)
    {
        bitTmp = bit(0, m);
        m = (m >> 1) ^ (bitTmp << (n - 1)); //on décale le mot m de 1 vers la droite et on lui rajoute l'ancien 1er bit.
    }
    return m;
}

/*
 * correction d'erreur pour le code de Golay en utilisant la méthode "error
 * trapping" + cyclicité
 * question 8
 * question 9 :
 * trois erreurs : 00011010011111110000110 => 11011010011110110000110
 * deux erreurs : 00011010011111110000110 => 10011010011101110000110
 * Dans ce cas on cherche les mots avec des erreurs suffisament espacées pour que le syndrome ne les detecte pas.
 * 
 * question 10
 */
mot correction_golay(mot m)
{
    mot tmp = 1;
    mot motTmp = m;
    mot syndrome;
    int passe = 0;
    for (int j = 0; j < 23; j++)
    {
        for (int i = 0; i < 23; i++)
        {
            syndrome = syndrome_golay(motTmp);
            if (poids(syndrome) <= (3 - passe)) // si poids<=3 ne donne pas de mot correct alors la variable passe vaut 1.
            {
                motTmp ^= syndrome;
                return decalage_circulaire(motTmp, 23, 23 - i);
            }
            else
            {
                motTmp = decalage_circulaire(motTmp, 23, 1);
            }
        }
        passe = 1; //si on a deja fait tous les décalages possible et que l'erreur n'a pas étée corrigée
        motTmp = m ^ (tmp << j); // On part du principe que le premier bit est faux et on réessaie. Si ce n'était pas le premier on passe au suivant etc...
    }

    return -1; //si le mot n'a pas de correction.
}

/*
 * correction d'erreur pour le code de Golay en utilisant la recherche exhaustive
 * question 11
 */
mot correction_exhaustive_golay(mot m)
{
    mot min = code_golay(0);
    mot tmp;
    int distMin = poids(min ^ m);
    int poidsTmp;
    for (int i = 0; i < (1 << 12); i++)
    {
        tmp = code_golay(i); // On construit le mot i du code de Golay.
        poidsTmp = poids(tmp ^ m);
        if (distMin > poidsTmp) // C'est une fonction de minimum sur la distance de Hamming
        {
            distMin = poidsTmp;
            min = tmp;
        }
    }
    // On renvoie le mot avec la plus petite distance de Hamming
    return min;
}

// Apres comparaison avec la commande time la correction exhaustive est plus lente que la correction "intelligente" de Golay
// car elle parcourt tou les mots mêmes si elle a deja le resultat.

// Question 12 :
