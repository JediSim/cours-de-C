// Simon PICHENOT Simon LEONARD CMI info programmation C TP2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tp2-LEONARD-PICHENOT-tableau.h"

void initialiseGrille(Grille g)
{
  for (int h = 0; h < HAUTEUR; h++) {
    for (int l = 0; l < LARGEUR; l++) {
      g[h][l] = ' ';
    }
  }
}

int estValide(Grille g, int h, int l)
{
  return l < LARGEUR && l >= 0 && h < HAUTEUR && h >= 0;
}

char lireCase(Grille g, int h, int l)
{
  if (estValide(g, h, l))
  {
    return g[h][l];
  }
  else
  {
    printf("/!\\ Position de la case invalide /!\\");
    return '\0';
  }
}

void afficheGrille(Grille g)
{
  for (int h = HAUTEUR-1; h >= 0; h--) {
    printf("||");
    for (int l = 0; l < LARGEUR; l++) {
      printf("%c", lireCase(g, h, l));
    }
    printf("||\n");
  }

  // floor
  printf("||");
  for (int i = 0; i < LARGEUR; i++) {
    printf("=");
  }
  printf("||\n");
  printf("  ");
  for (int i = 0; i < LARGEUR; i++) {
    printf("%i",i%10);
  }
  printf("\n");
}

void genererPieces(Piece* t)
{
  // I
  // I
  // I
  // I
  t[0].hauteur = 4;
  t[0].largeur = 1;
  t[0].forme[0] = "I";
  t[0].forme[1] = "I";
  t[0].forme[2] = "I";
  t[0].forme[3] = "I";
  t[0].rotD = 1;
  t[0].rotG = 1;

  // IIII
  t[1].hauteur = 1;
  t[1].largeur = 4;
  t[1].forme[0] = "IIII";
  t[1].rotD = 0;
  t[1].rotG = 0;

  // %%
  // %%
  t[2].hauteur = 2;
  t[2].largeur = 2;
  t[2].forme[0] = "%%";
  t[2].forme[1] = "%%";
  t[2].rotD = 2;
  t[2].rotG = 2;

  // LL
  //  L
  //  L
  t[3].hauteur = 3;
  t[3].largeur = 2;
  t[3].forme[0] = "LL";
  t[3].forme[1] = " L";
  t[3].forme[2] = " L";
  t[3].rotD = 4;
  t[3].rotG = 6;

  //   L
  // LLL
  t[4].hauteur = 2;
  t[4].largeur = 3;
  t[4].forme[0] = "  L";
  t[4].forme[1] = "LLL";
  t[4].rotD = 5;
  t[4].rotG = 3;

  // L
  // L
  // LL
  t[5].hauteur = 3;
  t[5].largeur = 2;
  t[5].forme[0] = "L ";
  t[5].forme[1] = "L ";
  t[5].forme[2] = "LL";
  t[5].rotD = 6;
  t[5].rotG = 4;

  // LLL
  // L
  t[6].hauteur = 2;
  t[6].largeur = 3;
  t[6].forme[0] = "LLL";
  t[6].forme[1] = "L ";
  t[6].rotD = 3;
  t[6].rotG = 5;
}

void affichePiece(Piece p)
{
  for (int h = 0; h < p.hauteur; h++) {
    printf("%s\n", p.forme[h]);
  }
  printf("↑\n");
}

void ecrireCase(Grille g, int h, int l, char c)
{
  if (estValide(g, h, l))
  {
    g[h][l] = c;
  }
  else
  {
    printf("/!\\ Position de la case invalide /!\\");
  }
}

int hauteurPlat(Grille g, int l1, int l2)
{
  // @TODO : test largeur
  for (int h = HAUTEUR-1; h >= 0; h--) {
    for (int l = l1; l <= l2; l++) {
      if (g[h][l] != ' ') {
        return h+1;
      }
    }
  }
  return 0;
}

void ecrirePiece(Grille g, Piece p, int h, int l)
{
  if (l+p.largeur-1 < LARGEUR) // @TODO: useless?
  {
    for (int i = 0; i < p.hauteur; i++)
    {
      for (int j = 0; j < p.largeur; j++)
      {
        if (p.forme[i][j] != ' ')
        {
          ecrireCase(g,h+p.hauteur-1-i,l+j,p.forme[i][j]);
        }  
      }
      // h++;
    }
  }
  else
  {
    printf("La piece ne passe pas en largeur !\n");
  }
}

Piece pieceAleatoire(Piece* t)
{
  int alea = rand() % NB_PIECES;
  return t[alea];
}

int estFini(Piece p, int h)
{
  return (p.hauteur + h) >= HAUTEUR;
}

void supprimerLigne(Grille g, int h)
{
  for (; h < HAUTEUR-1; h++)
  {
    for (int l = 0; l < LARGEUR; l++)
    {
      ecrireCase(g,h,l,lireCase(g,h+1,l));
      // g[h][l] = g[h+1][l];
    }
  }
  for (int l = 0; l < LARGEUR; l++)
  {
    ecrireCase(g,h,l,' ');
    // g[h][l] = ' ';
  }
}

int estPleine(Grille g, int h)
{
  int plein = 1;
  for (int l = 0; l < LARGEUR; l++)
  {
    // g[h][l] 
    if (lireCase(g,h,l) == ' ')
    {
      plein = 0;
    }
  }
  return plein;
}

void nettoyer(Grille g)
{
  for (int h = 0; h < HAUTEUR; h++)
  {
    if (estPleine(g,h))
    {
      supprimerLigne(g,h);
      h = h-1;
    }
  }
}

int estPosable(Grille g, Piece* piece, int h, int l)
{
  if ( h + piece->hauteur-1 >= HAUTEUR || l + piece->largeur-1 >= LARGEUR) return 0;
  for (int i = 0; i < piece->hauteur; i++)
  {
    for (int j = 0; j < piece->largeur; j++)
    {
      if (lireCase(g,h+piece->hauteur-1-i,l+j) != ' ' && piece->forme[i][j] != ' ' ) return 0;
      // g[h+piece->hauteur-1-i][l+j] 
    }
  }
  return 1;
}

int hauteurExacte( Grille g, int col_gauche, Piece* piece )
{
  int h = HAUTEUR-piece->hauteur;
  for(; estPosable(g, piece, h, col_gauche) && h >= 0; h--);
  return h+1;
}

int main(int argc, char const *argv[])
{
  // Init
  Grille g;
  Piece pieces[NB_PIECES];
  genererPieces( pieces );
  initialiseGrille( g );
  srand(time(NULL));

  int nbpieces = 0;
  int colonne;
  char str[8]; // pourquoi ?
  do {
    Piece p = pieceAleatoire(pieces);
    affichePiece(p);
    afficheGrille(g);

    while ( 1 ) {
      printf( "(g)auche, (d)roite ou (0-%i) colonne: ", LARGEUR-1 );
      if ( scanf( "%7s", str ) == 1 ) {
        if ( str[ 0 ] == 'g' ) {  p = pieces[p.rotG]; }
        else if ( str[ 0 ] == 'd' ) {  p = pieces[p.rotD]; }
        else {
          colonne = atoi( str );
          break;
        }
        
      }
      affichePiece(p);
      afficheGrille(g);
    }

    if (colonne >= 0) {
      int hp = hauteurExacte(g,colonne,&p);
      if (estPosable(g, &p, hp, colonne))
      {
        if (estFini(p,hp))
        {
          printf("La partie est fini !!!\n");
          printf("nombre de pieces : %i\n",nbpieces);
          initialiseGrille( g );
        }
        else
        {
          ecrirePiece(g, p, hp, colonne);
          nbpieces++;
          nettoyer(g);
        }
      }
      else
      {
        printf("La piece n'est pas posable\n");
      }
    }
  } while(colonne >= 0);
  return 0;
}
