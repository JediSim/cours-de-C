#define TAILLE_CARRE 30
#define MARGE_LARGEUR 4
#define MARGE_HAUTE 5
#define MARGE_BASSE 2

typedef struct {
  Grille g;
  Piece tab[ NB_PIECES ];
  Piece piece; // la piece "en cours" que l'on cherche à placer.
  int col; // la colonne actuelle pour la pièce que l'on cherche à caser.
  int score; // le score
  int delay; // le delay
  int delay_max;
  GtkWidget* label_score;
  GtkWidget* label_delay;
  GtkWidget* drawing_area;
} Jeu;

typedef struct {
  double r;
  double g;
  double b;
} Color;

gboolean rot_gauche( GtkWidget *widget, gpointer data );

gboolean rot_droite( GtkWidget *widget, gpointer data );

void setScoreLabel( Jeu* j, int score );

gint timer( gpointer data );

gboolean gauche( GtkWidget *widget, gpointer data );

gboolean droite( GtkWidget *widget, gpointer data );

gboolean bas( GtkWidget *widget, gpointer data );

gboolean new( GtkWidget *widget, gpointer data );

Color getColor(char c);

void dessineCarre( cairo_t* cr, int ligne, int colonne, char c);

void dessineGrille( cairo_t* cr, Grille g );

void nouvellePiece( Jeu* j );

void dessinePiece( cairo_t* cr, Jeu* j );

gboolean realize_evt_reaction( GtkWidget *widget, gpointer data );

gboolean on_draw( GtkWidget *widget, GdkEventExpose *event, gpointer data );

void creerIHM( Jeu* j );
