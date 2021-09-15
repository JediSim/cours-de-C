#include <stdio.h>
 
void affiche( int n, char* str[] )
{
  int i;
  for ( i = 0; i < n; i++ )
    printf( "argv[ %d ] = %s\n", i, str[ i ] );
}
 
int main( int argc, char* argv[] )
{
  affiche( argc, argv );
  return 0;
}