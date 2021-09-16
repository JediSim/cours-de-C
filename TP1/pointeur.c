#include <stdio.h>
 
#define MAX 100
 
void affiche()
{ /* t, p, nom_local sont alloués sur la pile d'exécution. */
  int t = 64; /* on se donne une variable locale */
  char* p = (char*) &t; /* permet de voir la mémoire caractère par car. */
  char nom_local[] = "Bonjour Toto";
  for ( int i = 0; i < MAX; ++i )
    printf("p[%5d]=%c : %d\n", i, p[ i ], p[ i ] ); 
}
 
int main( void )
{
  char nom1[] = "Bonjour Tutu"; /* alloué sur la pile, modifiable */
  char* nom2 = "Bonjour Tata";  /* alloué sur le segment de données, non modifiable */
  affiche();
  return 0;
}
