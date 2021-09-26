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

  // LL
  //  L
  //  L
  t[2].hauteur = 3;
  t[2].largeur = 2;
  t[2].forme[0] = "LL";
  t[2].forme[1] = " L";
  t[2].forme[2] = " L";
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
    for (int i = 0; i < p.hauteur; i++)
    {
      for (int j = 0; j < p.largeur; j++)
      {
        if (p.forme[i][j] != ' ')
        {
          ecrireCase(g,h-i,l+j,p.forme[i][j]);
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

int derniereCase(Grille g, int col)
{
  for (int h = HAUTEUR-1; h > 0; h--) 
  {
    if (g[h][col] != ' ') return h+1;
  }
  return 0;
}

int estPosable(Grille g, Piece* piece, int h, int l)
{
  int res = 1;
  if ( h - piece->hauteur+1 < 0 || l + piece->largeur >= LARGEUR) return 0;

  for (int i = h; i < piece->hauteur; i++)
  {
    for (int j = 0; j < piece->largeur; j++)
    {
      if (g[h+i][l+j] != ' ' && piece->forme[i][j] != ' ' ) res = 0;
    }
  }
  printf("res : %i\n hauteur : %i",res,h);
  return res;
}

// int estPosable(Grille g, Piece* p, int h, int col_g) {
   
//  if ( h + p->hauteur >= HAUTEUR && col_g + p->largeur >= LARGEUR) return 0;

//   for (int i = h + p->hauteur; i >= h; i--) 
//   {
//     for(int j = col_g; j < col_g + p->largeur; j++) 
//     {
//       char s_grille = g[i][j];
//       char s_piece = p->forme[i%(p->hauteur-1)][j%(p->largeur-1)];
//       if (s_grille != ' ' && s_piece != ' ') return 0;
//     }
//   }
//   return 1;
// }

int hauteurExacte( Grille g, int col_gauche, Piece* piece )
{
  // int plushaute = derniereCase(g,col_gauche)+piece->hauteur-1;
  // printf("%i",plushaute);
  for (int h = 0; h < HAUTEUR; h++)
  {
    printf("co : %i \n",h);
    if (estPosable(g, piece, h, col_gauche)) 
    {
      printf("posable /!\\\n");
      return h;
    }
    else
    {
      printf("pas posable\n");
    }
  }
  return 0;
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
      int hp = hauteurExacte(g,touche,&p);
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
