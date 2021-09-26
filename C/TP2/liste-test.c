#include <stdio.h>
#include "Liste.h"

void affiche( Liste* L )
{
    Adr A;
    for ( A = Liste_debut( L ); A != Liste_fin( L );
            A = Liste_suivant( L, A ) )
        printf( "%f ", Liste_valeur( L, A ) );
    printf( "\n" );
}
int main( void )
{
    Liste* L = Liste_creer( );
    Adr A = Liste_debut( L );
    double x = 1.0;
    while ( x < 100000.0 )
    {
        A = Liste_insere( L, A, x );
        A = Liste_suivant( L, A );
        x = 1.5*x;
    }
    affiche( L );
    Liste_detruire( L );
    return 0;
}