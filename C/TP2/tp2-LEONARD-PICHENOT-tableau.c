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

  // %%
  // %%
  t[1].hauteur = 2;
  t[1].largeur = 2;
  t[1].forme[0] = "%%";
  t[1].forme[1] = "%%";
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
  if (l+p.largeur-1 < LARGEUR)
  {
    for (int i = p.hauteur-1; i >= 0; i--)
    {
      for (int j = 0; j < p.largeur; j++)
      {
        ecrireCase(g,h,l+j,p.forme[i][j]);
      }
      h++;
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
      g[h][l] = g[h+1][l];
    }
  }
  for (int l = 0; l < LARGEUR; l++)
  {
    g[h][l] = ' ';
  }
}

int estPleine(Grille g, int h)
{
  int plein = 1;
  for (int l = 0; l < LARGEUR; l++)
  {
    if (g[h][l] == ' ')
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

int main(int argc, char const *argv[])
{
  //
  // ecrireCase(g,0,5,'b');
  // printf("Hauteur max : %i\n", hauteurPlat(g, 3, 4));
  // afficheGrille( g );
  //
  // int hp = hauteurPlat(g, 3, 3+pieces[1].largeur-1);
  // printf("%i\n", hp);
  // ecrirePiece(g,pieces[1],hp,3);
  // afficheGrille( g );
  // affichePiece(pieceAleatoire(pieces));
  //

  // Init
  Grille g;
  Piece pieces[NB_PIECES];
  genererPieces( pieces );
  initialiseGrille( g );
  srand(time(NULL));

  int nbpieces = 0;
  int touche;
  do {
    Piece p = pieceAleatoire(pieces);
    affichePiece(p);
    afficheGrille(g);

    printf("Choisir une colonne (-1 pour quitter) : ");
    scanf("%i", &touche);
    printf("\n");

    if (touche >= 0) {
      int hp = hauteurPlat(g, touche, touche + p.largeur - 1);
      if (estFini(p,hp))
      {
        printf("La partie est fini !!!\n");
        printf("nombre de pieces : %i\n",nbpieces);
        initialiseGrille( g );
      }
      else
      {
        ecrirePiece(g, p, hp, touche);
        nbpieces++;
        nettoyer(g);
      }
    }
  } while(touche >= 0);
  return 0;
}
