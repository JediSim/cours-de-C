#include <stdlib.h>
#include "Liste_tetris.h"
Liste* Liste_creer()
{
    Liste* L = (Liste*) malloc( sizeof( Liste ) );
    Liste_init( L );
    return L;
}
void Liste_init( Liste* L )
{
    L->succ = L;
    L->pred = L;
}
void Liste_termine( Liste* L )
{
    while ( Liste_debut( L ) != Liste_fin( L ) )
        Liste_supprime( L, Liste_debut( L ) );
}
void Liste_detruire( Liste* L )
{
    Liste_termine( L );
}
Adr Liste_debut( Liste* L )
{
    return L->succ;
}
Adr Liste_fin( Liste* L )
{
    return L;
}
Adr Liste_suivant( Liste* L, Adr A )
{
    return A->succ;
}
Adr Liste_precedent( Liste* L, Adr A )
{
    return A->pred;
}
Adr Liste_insere( Liste* L, Adr A, Elem v )
{
    Adr ncell = (Adr) malloc( sizeof( Cellule ) );
    ncell->val = v;
    ncell->pred = A;
    return ncell;
}
void Liste_supprime( Liste* L, Adr A )
{
    A->pred->succ = A->succ;
    A->succ->pred = A->pred;
}
Elem Liste_valeur( Liste* L, Adr A )
{
    return A->val;
}
void Liste_modifie( Liste* L, Adr A, Elem v )
{
    A->val = v;
}