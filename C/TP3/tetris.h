#ifndef _TETRIS_H_
#define _TETRIS_H_

#define HAUTEUR 12
#define LARGEUR 16
#define NB_PIECES 7
#define HAUTEUR_MAX_PIECES 4

struct SPiece {
  int   hauteur;
  int   largeur;
  char* forme[ HAUTEUR_MAX_PIECES ];
  int rotD;
  int rotG;
};
typedef struct SPiece Piece;

typedef char Grille[HAUTEUR][LARGEUR];

void initialiseGrille(Grille g);

int estValide(Grille g, int h, int l);

char lireCase(Grille g, int lgn, int col);

void afficheGrille(Grille g);

void genererPieces(Piece* t);

void affichePiece(Piece p);

void ecrireCase(Grille g, int h, int l, char c);

int hauteurPlat(Grille g, int l1, int l2);

void ecrirePiece(Grille g, Piece p, int h, int l);

Piece pieceAleatoire(Piece* t);

int estFini(Piece p, int h);

void supprimerLigne(Grille g, int h);

int estPleine(Grille g, int h);

void nettoyer(Grille g);

int estPosable(Grille g, Piece* piece, int h, int l);

int hauteurExacte( Grille g, int col_gauche, Piece* piece );

#endif /* ifndef _TETRIS_H_ */
