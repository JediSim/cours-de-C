#include <stdio.h>
#include <stdlib.h>
 
void echange( int* pi, int* pj )
{
  int t = *pi; 
  *pi   = *pj;
  *pj   = t;
}
 
void aleatoire( int* debut, int* fin )
{
  for ( ; debut != fin; ++debut )
    *debut = rand() % 100;
}
 
void affiche( int* debut, int* fin )
{
  for ( ; debut != fin; ++debut )
    printf( " %d", *debut );
  printf( "\n" );
}
 
// Tri à bulle ?
void tri( int* debut, int* fin )
{
  for ( ; debut != fin-1; ++debut )
    for ( int* bulle = fin-1; bulle != debut; --bulle )
      if ( *bulle < *(bulle-1) )
        echange( bulle, bulle-1 );
}
 
int main()
{
  int t[ 20 ];
  aleatoire( t, t+20 );
  affiche( t, t+20 );
  tri( t, t+20 );
  affiche( t, t+20 );
}

