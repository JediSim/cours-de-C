#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
   float x; // coordonnee x
   float y; // coordonnee y
   float t; // angle en degre
} Tortue;

 
// On note le passage en entree/sortie du C. 
void init( Tortue* ptrTortue )
{
  ptrTortue->x = 0.0f;
  ptrTortue->y = 0.0f;
  ptrTortue->t = 0.0f;
}
 
// On note le passage en entree/sortie du C pour des paramètres à modifier. 
void avance( Tortue* ptrTortue, float d )
{
  ptrTortue->x = ptrTortue->x + d * cos( ptrTortue->t * M_PI / 180.0 );
  ptrTortue->y = ptrTortue->y + d * sin( ptrTortue->t * M_PI / 180.0 );
}

void tourneG(Tortue* ptrTortue, float d)
{
  ptrTortue->t += d;
}

void tourneD(Tortue* ptrTortue, float d)
{
  ptrTortue->t -= d;
}

void allezA(Tortue* ptrTortue, float x, float y)
{
  ptrTortue->x = x;
  ptrTortue->y = y;
}

// Un passage en entree serait suffisant lorsqu'aucune modification n'est nécessaire, 
// mais un passage par adresse aurait été possible (voire préférable).
void affiche( Tortue tortue )
{
  printf( "%f %f\n", tortue.x, tortue.y );
}

// T est la tortue, 
// d est la longueur du trace, 
// k sera utilisé plus tard (indique la profondeur de récursivité demandée).
void koch( Tortue* T, float d, int k )
{
  if (k==0)
  {
    affiche( *T );
    avance( T, d / 3 ); // (*)
    affiche( *T );
  }else
  {
    affiche( *T );
    koch( T, d, k-1 ); // (*)
    affiche( *T );
  
    tourneG( T, 60 );  
    koch( T, d, k-1 ); // (*)
    affiche( *T );
  
    tourneD( T, 120 );  
    koch( T, d, k-1 ); // (*)
    affiche( *T );
  
    tourneG( T, 60 );  
    koch( T, d, k-1 ); // (*)
    affiche( *T );
  }
  
}

int main()
{
  Tortue T;
  init( &T );
  affiche( T );
 
  // (*)
  /** triangle
  // 1er cote
  avance( &T, 10.0f );
  tourneG( &T, 120 );
  affiche( T );
 
  // 2eme cote
  avance( &T, 10.0f );
  tourneG( &T, 120 );
  affiche( T );
 
  // 3eme cote
  avance( &T, 10.0f );
  tourneG( &T, 120 );
  affiche( T );
  **/

  /** Maison
  tourneD(&T,90);
  avance( &T, 5.0f );
  affiche( T );

  tourneG(&T,90);
  avance( &T, 5.0f );
  affiche( T );

  tourneG(&T,90);
  avance( &T, 5.0f );
  affiche( T );

  tourneG(&T,90);
  avance( &T, 5.0f );
  affiche( T );

  tourneD(&T,120);
  avance( &T, 5.0f );
  affiche( T );

  tourneD(&T,120);
  avance( &T, 5.0f );
  affiche( T );
  **/

  koch(&T,5.0,4);
}
/** tracer une maison 
La maison de droite n'est pas trop dur a tracer a condition que l'on passe plusieurs fois sur les memes trais
**/
