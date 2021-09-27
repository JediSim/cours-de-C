#define HAUTEUR 12
#define LARGEUR 16
#define NB_PIECES 3
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
