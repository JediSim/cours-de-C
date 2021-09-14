#include <stdio.h>
#include <stdlib.h>

#include "arbre.h"

//-----------------------------------------------------------------------------------fct utile
int max(int a, int b)
{
    if (a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
//-----------------------------------------------------------------------------------fin fct utile


//-----------------------------------------------------------------------------------fct de manipulation d'arbre (arbre_vide, creer_arbre...)
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

int arbre_vide(arbre_int a)
/** 
param : -a [arbre_int]
return : bool vrai si a est vide
**/
{
    return a == NULL;
}

void affiche(arbre_int a, int etage)
/**
procedure qui affiche l'arbre en horizontale exo 1 TD 1 algo
param : -a [arbre_int]
        -etage [int]
**/
{
    int new_etage = ++etage;
    if (arbre_vide(a))
    {
        printf("");
    }
    else
    {
        affiche(a->brd,new_etage);
        for(int i=0;i<(4*etage); i++)
        {
            printf(" ");
            
        }
        printf("%i\n",a->val);
        affiche(a->brg,new_etage);
    }
}

int est_dans(arbre_int n, arbre_int a)
/**
test si un noeud est dans un arbre
param : -n [arbre_int] noeud a chercher
        -a [arbre_int] arbre dans lequel chercher
return : bool vrai si est dedans
**/
{
    if (arbre_vide(a))
    {
        return 0;
    }
    else if (a->val == n->val)
    {
        return 1;
    }
    else if (est_dans(n,a->brg))
    {
        return  1;
    }
    else
    {
        return est_dans(n,a->brd);
    }
}
//----------------------------------------------------------------------------------- fin fct de manipulation d'arbre


//-----------------------------------------------------------------------------------4.3 Metriques des arbres binaires
int nb_noeud(arbre_int a)
/**
param : -a [arbre_int]
return : nb de noeud dans l'arbre
**/
{
    if (arbre_vide(a))
    {
        return 0;      
    }else
    {
        return 1 + nb_noeud(a->brg) + nb_noeud(a->brd);
    }
}

int level_noeud(arbre_int n, arbre_int a)
/**
renvoie le niveau ou est le noeud dans l'arbre
param : -n [arbre_int] noeud a trouver
        -a [arbre_int] arbre ou chercher
return : [int] numero d'étage
**/
{
    if (n->val == a->val)
    {
        return 0;
    }
    else if (est_dans(n,a->brd))
    {
        return 1 + level_noeud(n,a->brd);
    }
    else
    {
        return 1 + level_noeud(n,a->brg);
    }
}

int hauteur_arbre(arbre_int a)
/**
calcul la hauteur d'un arbre
param : -a [arbre_int] arbre à mesurer
return : [int] hauteur de l'arbre
**/
{
    if (arbre_vide(a))
    {
        return 0;
    }
    else
    {
        return 1 + max(hauteur_arbre(a->brg),hauteur_arbre(a->brd));
    }
}

//-----------------------------------------------------------------------------------5. LES ARBRES BINAIRES DE RECHERCHE


int main()
{
    int taille,vide,dans,niveau,hauteur;   
    arbre_int ab,abc;  
    ab = creer_arbre(1,NULL,NULL);
    vide = arbre_vide(ab);
    printf("vide : %i\n",vide);
    vide = arbre_vide(ab->brd);
    printf("vide : %i\n",vide);
    abc = creer_arbre(10,ab,ab);
    taille = nb_noeud(abc);
    
    printf("taille : %i\n", taille);
    affiche(abc,0);

    dans = est_dans(ab,abc);
    printf("est dans : %i\n",dans);

    niveau = level_noeud(ab,abc);
    printf("niveau : %i\n",niveau);

    hauteur = hauteur_arbre(abc);
    printf("hauteur : %i\n",hauteur);

    return 0;
}
