#include "tp1.h"

#define BIT(i, m) ((m)&1)

/*
 * renvoie le bit numéro 'i' d'un mot 'm'
 * question 1
 */
int bit(int i, mot m)
{
    // On décalle le mot du nombre de bit passé en parametre.
    // On applique le "& 1" sur le mot décallé pour ne récupérer que le dernier bit.
    return (m >> i)&1;
}

/*
 * affiche les n bit de poids faible d'un mot
 * question 1
 */
void print_bin(mot m, int n)
{
    // On parcours le mot à l'envers et on récupère les bits un à un.
    for(int i = n; i >= 0; i--)
    {
        printf("%d",bit(i,m));
    }
}

/*
 * compte le nombre de 1 dans un mot
 * question 2
 */
int poids(mot m)
{
    // ...
    return 0;
}

/**********************************************************************
 * Code de Golay avec parité
 * matrice generatrice: I | G avec G
   10101110001
   11111001001
   11010010101
   11000111011
   11001101100
   01100110110
   00110011011
   10110111100
   01011011110
   00101101111
   10111000110
   01011100011
 *********************************************************************/

/* question 3 */
mot golay_A[12] = { 0x571, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/*
 * code une suite de 12 bits (bits de poids faible d'un mot) en ajoutant la
 * redondance donnée par la matrice A
 * Le résultat (23 bits) est stocké dans les 23 bits de poid faible du mot
 * renvoyé.
 * question 3
 */
mot code_golay(mot entree)
{
    // ...
    return 0;
}

/*
 * décode un mot du code de Golay en supprimant les bits de redondance
 * question 4
 */
mot decode_golay(mot m)
{
    // ...
    return 0;
}

/*
 * code de Golay étendu: 23 bit du code de Golay, avec un bit de parité
 * question 5
 */
mot code_golay_etendu(mot entree)
{
    // ...
    return 0;
}

/* matrice de partité */
/* question 6 */
mot golay_H[23]
    = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/*
 * syndrome d'un mot du code de Golay (sans bit de parité)
 * question 6
 */
mot syndrome_golay(mot m)
{
    // ...
    return 0;
}

/*
 * renvoie le décalage circulaire (à droite) de p bits sur un mot de n bits
 * question 7
 */
mot decalage_circulaire(mot m, int n, int p)
{
    // ...
    return m;
}

/*
 * correction d'erreur pour le code de Golay en utilisant la méthode "error
 * trapping" + cyclicité
 * question 8
 * question 9
 * question 10
 */
mot correction_golay(mot m)
{
    // ...
    return -1;
}

/*
 * correction d'erreur pour le code de Golay en utilisant la recherche exhaustive
 * question 11
 */
mot correction_exhaustive_golay(mot m)
{
    // ...
    return -1;
}
