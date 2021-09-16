#include <stdlib.h>
#include <math.h>
#include <stdio.h>
 
float f( float x )
{
    return sin( 1/x ); // a modifier pour changer de fct
}
 
void usage()
{
    printf( "fct [debut] [fin] [pas]\n" );
    printf( "- Calcule les valeurs d'une fonction entre [debut] et [fin] par pas de [pas].\n" );
}
 
int main( int argc, char** argv )
{
    float debut, fin, pas;
 
    if ( argc < 4 )
    {
        usage();
        return 0;
    }
    debut = atof( argv[ 1 ] );
    fin = atof( argv[ 2 ] );
    pas = atof( argv[ 3 ] );
 
    while ( debut <= fin )
    {
        printf( "%f %f\n", debut, f( debut ) );
        debut += pas;
    }
    return 0;
} 
