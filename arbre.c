#include <stdio.h>
#include <stdlib.h>

#include "arbre.h"

arbre_int creer_arbre(int nb, arbre_int bg, arbre_int bd)
{
    arbre_int a;
    a = (arbre_int) malloc(sizeof(struct noeud_int));
    if (a == NULL) 
    {
        fprintf(stderr, "Impossible d'allouer le noeud");
        return NULL;
    }
    a->val = nb;
    a->brg = bg;
    a->brd = bd;
    return a;
}

int arbre_vide(arbre_int a){
    return a == NULL;
}

int taille_arbre(arbre_int a)
{
    if (arbre_vide(a))
    {
        printf("coucou0 sorti\n");
        return 0;      
    }else
    {
        printf("coucou1");
        return 1 + taille_arbre(a->brg);// + taille_arbre(a->brd);
        // erreur dans le cours a voir demain td
    }
}

int main()
{
    int taille,vide;   
    arbre_int ab,abc;  
    ab = creer_arbre(10,NULL,NULL);
    vide = arbre_vide(ab);
    printf("vide : %i\n",vide);
    vide = arbre_vide(ab->brd);
    printf("vide : %i\n",vide);
    abc = creer_arbre(10,ab,ab);
    taille = taille_arbre(abc);
    
    printf("taille : %i", taille);

    return 0;
}