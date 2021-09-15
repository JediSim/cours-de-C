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

// Un passage en entree serait suffisant lorsqu'aucune modification n'est nécessaire, 
// mais un passage par adresse aurait été possible (voire préférable).
void affiche( Tortue tortue )
{
  printf( "%f %f\n", tortue.x, tortue.y );
}

int main()
{
  Tortue T;
  init( &T );
  affiche( T );
 
  // (*)
 
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
}