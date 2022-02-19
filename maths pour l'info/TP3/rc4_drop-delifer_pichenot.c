#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Delifer Paul & Pichenot Simon
typedef unsigned char byte;

void ksa(byte* P, byte* cle, int taille_cle);
byte pgra(byte* P, int* index_i, int* index_j);
void code_RC4(byte *cle, int taille_cle, byte *Message, int taille_message, int n);

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("RC4-drop[n], utilisation : %s cle message n\n", argv[0]);
        exit(-1);
    }
    code_RC4((byte*)argv[1], strlen(argv[1]), (byte*)argv[2], strlen(argv[2]), atoi(argv[3]));
    return 0;
}

// Chiffre la chaine message avec la clé cle et affiche le résultat en hexadécimal. Saute les n premiers octets générés.
void code_RC4(byte* cle, int taille_cle, byte* message, int taille_message, int n)
{
    int index_i = 0;
    int index_j = 0;
    byte P[256];
    byte octet_aleatoire;

    /* initialisation avec Key Scheduling Algorithm */
    ksa(P, cle, taille_cle);

    /* on passe les n premiers octets aléatoires */
    for(int i=0; i<n; i++)
        octet_aleatoire = pgra(P, &index_i, &index_j);
    
    /* On chiffre le message */
    for(int i=0; i<taille_message; i++) {
        octet_aleatoire = pgra(P, &index_i, &index_j);
        message[i] = message[i] ^ octet_aleatoire;
    }

    /* affichage */
    printf("Code obtenu : ");
    for(int i=0; i<taille_message; i++)
        printf("%02X", message[i]);
    printf("\n");
}

// KSA : Key Scheduling Algorithm. L'état est constitué des variables P (tableau de 256 octets), index_i et index_j (entiers).
void ksa(byte* P, byte* cle, int taille_cle)
{
    for(int i = 0; i < 256; i++)
        P[i] = i;

    int j = 0;
    for(int i = 0; i < 256; i++) {
        j = (j + P[i] + cle[i % taille_cle])  %  256;
        byte temp = P[i];
        P[i] = P[j];
        P[j] = temp;
    }
}

// PRGA : Pseudo Random Generator Algorithm.
byte pgra(byte* P, int* index_i, int* index_j)
{
    
    *index_i = (*index_i + 1) % 256;
    *index_j = (*index_j + P[*index_i]) % 256;
    byte temp = P[*index_i];
    P[*index_i] = P[*index_j];
    P[*index_j] = temp;

    return P[ (P[*index_i] + P[*index_j]) % 256];
}