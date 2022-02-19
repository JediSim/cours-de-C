#include "stdlib.h"
#include "string.h"
#include "stdio.h"

typedef unsigned char byte;

void code_RC4(byte *Cle, int taille_cle, byte *Message, int taille_message, int n)
{
    int P[256];
    int index_i, index_j, tmp, j;
    byte* res;
    index_i = 0;
    index_j = 0;
    
    for(int i = 0; i < taille_cle; i++)
        P[i] = Cle[i];

    j = 0;
    for(int i = 0; i < 256; i++) {
        j = (j + P[i] + Cle[i % taille_cle])  %  256;
        tmp = P[i];
        P[i] = P[j];    /* échange */
        P[j] = tmp;
    }
    
    int octet_aleatoire;

    for (int i = 0; i < taille_message; i++)
    {
        if (i > n){
            index_i = (index_i + 1)  %  256;
            index_j = (index_j + P[index_i])  %  256;
            tmp = P[i];
            P[i] = P[j];    /* échange */
            P[j] = tmp;
            octet_aleatoire = P[ (P[index_i] + P[index_j])  %  256];
            res[i] = Message[i] ^ octet_aleatoire;
        }
        
    }
    printf("%02X",res);
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("RC4-drop[n], utilisation : %s cle message n\n", argv[0]);
        exit(-1);
    }
    code_RC4((byte*)argv[1], strlen(argv[1]), (byte*)argv[2], strlen(argv[2]), atoi(argv[3]));
    return 0;
}