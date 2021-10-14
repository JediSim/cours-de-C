#define TAILLE_CARRE 16
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
  GtkWidget* window;
} Jeu;

typedef struct {
  double r;
  double g;
  double b;
} Color;

gboolean gauche( GtkWidget *widget, gpointer data );

gboolean droite( GtkWidget *widget, gpointer data );

gboolean bas( GtkWidget *widget, gpointer data );

gboolean new( GtkWidget *widget, gpointer data );

Color getColor(char c);

void dessineCarre( cairo_t* cr, int ligne, int colonne, char c);

void dessineGrille( cairo_t* cr, Grille g );

gboolean realize_evt_reaction( GtkWidget *widget, gpointer data );

gboolean on_draw( GtkWidget *widget, GdkEventExpose *event, gpointer data );

void creerIHM( Jeu* j );
