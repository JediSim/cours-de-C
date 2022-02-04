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
        if (m & 1)
            resultat += 1;
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
        if (bit(i, entree) == 1)
        {
            res ^= golay_A[11 - i];
        }
    }
    return (entree << 11) ^ res;
}

/*
 * décode un mot du code de Golay en supprimant les bits de redondance
 * question 4
 */
mot decode_golay(mot m)
{
    return (m >> 11);
}

/*
 * code de Golay étendu: 23 bit du code de Golay, avec un bit de parité
 * question 5
 */
mot code_golay_etendu(mot entree)
{
    entree=code_golay(entree);
    return (entree<<1)^(poids(entree)&1);
}

/* matrice de partité */
/* question 6 */
mot golay_H[23] = { 0x571, 
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
                    0x1
                    };

/*
 * syndrome d'un mot du code de Golay (sans bit de parité)
 * question 6
 */
mot syndrome_golay(mot m)
{
    mot syndrome=0;
    for (int i =0; i <23;i++){
        if(bit(i,m) == 1){
            syndrome^=golay_H[22-i];}
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
        bitTmp = bit(0,m);
        m = (m>>1) ^ (bitTmp << (n-1));
    }
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
    mot tmp = 1;
    mot motTmp = m;
    mot syndrome;
    int passe = 0;
    for (int j = 0; j < 23; j++)
    {
        for (int i = 0; i < 23; i++)
        {
            syndrome = syndrome_golay(motTmp);
            if (poids(syndrome) <= (3-passe))
            {
                motTmp ^= syndrome;
                return decalage_circulaire(motTmp,23,23-i) ;
            }
            else
            {
                motTmp = decalage_circulaire(motTmp, 23,1);
            }
        }
        passe = 1;
        motTmp = m ^ (tmp << j);
    }
    
    return -1;
}

/*
 * correction d'erreur pour le code de Golay en utilisant la recherche exhaustive
 * question 11
 */
mot correction_exhaustive_golay(mot m)
{
    mot min = code_golay(0);
    mot tmp;
    int distMin = poids(min^m);
    int poidsTmp;
    for (int i = 0; i < (1 << 12); i++)
    {
        tmp = code_golay(i);
        poidsTmp = poids(tmp^m);
        if ( distMin > poidsTmp)
        {
            distMin = poidsTmp;
            min = tmp;
        }
    }
    return min;
}

// Question 12 :
