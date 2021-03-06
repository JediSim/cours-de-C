#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

#include "tetris.h"
#include "gtktetris.h"

gboolean rot_gauche( GtkWidget *widget, gpointer data )
{
  Jeu* j = (Jeu*) data;
  j->piece = j->tab[j->piece.rotG];

  gtk_widget_queue_draw( j->drawing_area );
  return TRUE;
}

gboolean rot_droite( GtkWidget *widget, gpointer data )
{
  Jeu* j = (Jeu*) data;
  j->piece = j->tab[j->piece.rotD];

  gtk_widget_queue_draw( j->drawing_area );
  return TRUE;
}

void setScoreLabel( Jeu* j, int score )
{
  char str[10];
  sprintf(str, "score %d", score);
  gtk_label_set_text( GTK_LABEL( j->label_score ), str );
}

gint timer( gpointer data )
{
  Jeu* j = (Jeu*) data;
  if (j->delay > 0)
  {
    j->delay = j->delay-1;

    char str[10];
    sprintf(str, "%d", j->delay);
    gtk_label_set_text( GTK_LABEL( j->label_delay ), str );
  }
  else
  {
    j->delay = j->delay_max;
    bas(j->drawing_area, data);
  }
  
  gtk_widget_queue_draw( j->label_delay );
  g_timeout_add (1000, timer, (gpointer) j); // réenclenche le timer.
  return 0;
}

gboolean gauche( GtkWidget *widget, gpointer data )
{
  // Recupère la valeur passée en paramètre.
  Jeu* j = (Jeu*) data;
  if (j->col > 0)
  {
    j->col = j->col-1;
  }

  gtk_widget_queue_draw( j->drawing_area);
  return TRUE; // Tout s'est bien passé
}

gboolean droite( GtkWidget *widget, gpointer data )
{
  // Recupère la valeur passée en paramètre.
  Jeu* j = (Jeu*) data;
  if (j->col < LARGEUR-j->piece.largeur)
  {
    j->col = j->col+1;
  }

  gtk_widget_queue_draw( j->drawing_area);
  return TRUE; // Tout s'est bien passé
}

gboolean bas( GtkWidget *widget, gpointer data )
{
  Jeu* j = (Jeu*) data;

  int h = hauteurExacte(j->g, j->col, &(j->piece));

  if (estFini(j->piece, h)) 
  {
      initialiseGrille( j->g );
      setScoreLabel( j, 0 );
      j->score = 0;
  }
  else
  {
      ecrirePiece(j->g, j->piece, h, j->col);
      nettoyer(j->g);
      j->score += 5;
      setScoreLabel(j, j->score );
  }


  j->piece = pieceAleatoire( j->tab );
  
  j->delay = j->delay_max;

  char str[10];
  sprintf(str, "%d", j->delay);
  gtk_label_set_text( GTK_LABEL( j->label_delay ), str );

  gtk_widget_queue_draw( j->drawing_area );
  return TRUE; // Tout s'est bien passé
}

gboolean new( GtkWidget *widget, gpointer data )
{
  Jeu* j = (Jeu*) data;

  initialiseGrille( j->g );
  genererPieces( j->tab );
  j->score = 0;
  setScoreLabel(j, 0);
  j->delay = j->delay_max;

  gtk_widget_queue_draw( gtk_widget_get_toplevel(widget) );

  return TRUE; // Tout s'est bien passé
}

Color getColor(char c)
{
  Color co = {0.0, 0.0, 0.0};
  switch (c) {
    case 'I':
      co.r = 1.0;
      break;
    case '%':
      co.g = 1.0;
      break;
    case 'L':
      co.b = 1.0;
      co.g = 0.3;
      break;
    default:
      co.r = 1.0;
      co.g = 1.0;
      co.b = 1.0;
      break;
  }
  return co;
}

void dessineCarre( cairo_t* cr, int ligne, int colonne, char c)
{
  Color color = getColor(c);

  if (color.r == 1.0 && color.g == 1.0 && color.b == 1.0) return; // white

  cairo_set_source_rgb (cr, color.r, color.g, color.b);
  cairo_rectangle (cr,
                  (colonne+MARGE_LARGEUR/2) * TAILLE_CARRE,
                  (HAUTEUR-1-ligne+MARGE_HAUTE)*TAILLE_CARRE ,
                  TAILLE_CARRE,
                  TAILLE_CARRE ); // x, y, largeur, hauteur
  cairo_fill_preserve( cr ); // remplit la forme actuelle (un rectangle)
  // => "_preserve" garde la forme (le rectangle) pour la suite

  cairo_set_line_width(cr, 3);

  cairo_set_source_rgb (cr, color.r/2, color.g/2, color.b/2);

  cairo_stroke( cr ); // trace la forme actuelle (le même rectangle)
  // => pas de "_preserve" donc la forme // Recupère la valeur passée en paramètre.(le rectangle) est oublié.
}

void dessineGrille( cairo_t* cr, Grille g )
{
  for (int l = HAUTEUR-1; l >= 0; l--) {
    for (int c = 0; c < LARGEUR; c++) {
      dessineCarre( cr, l, c, g[l][c]);
    }
  }
}

void nouvellePiece( Jeu* j )
{
  j->piece = pieceAleatoire( j->tab );
  j->col = ( LARGEUR - j->piece.largeur ) / 2;
}

void dessinePiece( cairo_t* cr, Jeu* j )
{
  if (j->col + j->piece.largeur >= LARGEUR)
    j->col -= j->col + j->piece.largeur - LARGEUR;

  int col = j->col;
  Piece p = j->piece;


  for (int h = 0; h < p.hauteur; h++) {
    for (int l = 0; l < p.largeur; l++) {
      // dessineCarre assume que l'on écris des pièces dans la grille
      // On a donc repris la formule de la hauteur : HAUTEUR-1-ligne+MARGE_HAUTE
      // Ajouter HAUTEUR permet de se retrouver avec -1-ligne+MARGE_HAUTE.
      // Le reste de la formule de la hauteur permet de placer la pièce correctement
      dessineCarre( cr, HAUTEUR + (p.hauteur-1) - h , col + l, p.forme[h][l]);
    }
  }
}

gboolean realize_evt_reaction( GtkWidget *widget, gpointer data )
{ // force un événement "draw" juste derrière.
  gtk_widget_queue_draw( widget );
  return TRUE;
}

// c'est la réaction principale qui va redessiner tout.
gboolean on_draw( GtkWidget *widget, GdkEventExpose *event, gpointer data )
{
  // Ces premières lignes permettent de récupérer la zone d'affichage
  // et d'initialiser un objet Cairographics cr qui permettra de dessiner
  // sur cette zone.
  GdkWindow* window = gtk_widget_get_window(widget);
  cairo_region_t* cairoRegion = cairo_region_create();
  GdkDrawingContext* drawingContext
    = gdk_window_begin_draw_frame( window, cairoRegion );
  cairo_t* cr = gdk_drawing_context_get_cairo_context( drawingContext );

  // réupere jeu
  Jeu* j = (Jeu*) data;

  // remplissage noir (bordure)
  cairo_set_source_rgb (cr, 0, 0, 0);
  cairo_paint( cr ); // remplit tout dans la couleur choisie.

  // zone de grille + marge haute
  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_rectangle (cr,
                  MARGE_LARGEUR/2 * TAILLE_CARRE,
                  0,
                  LARGEUR * TAILLE_CARRE,
                  (HAUTEUR + MARGE_HAUTE) * TAILLE_CARRE ); // x, y, largeur, hauteur
  cairo_fill( cr );

  // CreerGrille
  dessineGrille( cr, j->g );

  // piece courante
  dessinePiece( cr, j );

  // (B) On a fini, on peut détruire la structure.
  gdk_window_end_draw_frame(window,drawingContext);
  // cleanup
  cairo_region_destroy(cairoRegion);
  return TRUE;
}

void creerIHM( Jeu* j )
{
  ////////////
  // WINDOW //
  ////////////
  GtkWidget *window;

  /* Crée une fenêtre. */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  /* La rend visible. */
  gtk_widget_show(window);

  //////////////////
  // DRAWING AREA //
  //////////////////

  GtkWidget* drawing_area;

  /////////////
  // BUTTONS //
  /////////////

  GtkWidget* left;
  GtkWidget* right;
  GtkWidget* down;

  GtkWidget* tourne_gauche;
  GtkWidget* tourne_droite;

  GtkWidget* button_new;
  GtkWidget* button_quit;

  //////////////
  //// BOXS ////
  //////////////

  GtkWidget* direction_box;
  GtkWidget* left_box;

  GtkWidget* control_box;
  GtkWidget* right_box;

  GtkWidget* main_box;

  //////////////
  // LEFT BOX //
  //////////////

  // DRAWING_AREA
  drawing_area = gtk_drawing_area_new ();
  j->drawing_area = drawing_area;
  // largeur=TAILLE_CARRE*(LARGEUR+4), hauteur = TAILLE_CARRE*(HAUTEUR+7)).
  gtk_widget_set_size_request (drawing_area,
                              TAILLE_CARRE * ( LARGEUR + MARGE_LARGEUR ),
                              TAILLE_CARRE * ( HAUTEUR + MARGE_HAUTE + MARGE_BASSE ));
  g_signal_connect( G_OBJECT (drawing_area), "realize", G_CALLBACK(realize_evt_reaction), j );
  g_signal_connect( G_OBJECT (drawing_area), "draw", G_CALLBACK (on_draw), j );

  // BUTTONS
  left = gtk_button_new_with_label ( "<" );
  g_signal_connect( left, "clicked" , G_CALLBACK( gauche ), j );

  right = gtk_button_new_with_label ( ">" );
  g_signal_connect( right, "clicked" , G_CALLBACK( droite ), j );

  down = gtk_button_new_with_label ( "v" );
  g_signal_connect( down, "clicked" , G_CALLBACK( bas ), j );

  tourne_gauche = gtk_button_new_with_label ( "↺" );
  g_signal_connect( tourne_gauche, "clicked" , G_CALLBACK( rot_gauche ), j );

  tourne_droite = gtk_button_new_with_label ( "↻" );
  g_signal_connect( tourne_droite, "clicked" , G_CALLBACK( rot_droite ), j );

  // ADD TO CONTAINER
  direction_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_container_add( GTK_CONTAINER(direction_box), left);
  gtk_container_add( GTK_CONTAINER(direction_box), down);
  gtk_container_add( GTK_CONTAINER(direction_box), right);
  gtk_container_add( GTK_CONTAINER(direction_box), tourne_gauche);
  gtk_container_add( GTK_CONTAINER(direction_box), tourne_droite);

  left_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_add( GTK_CONTAINER(left_box), drawing_area);
  gtk_container_add( GTK_CONTAINER(left_box), direction_box);

  ///////////////
  // RIGHT BOX //
  ///////////////

  // CONTROL BUTTON

  button_new = gtk_button_new_with_label ( "New" );
  g_signal_connect( button_new, "clicked", G_CALLBACK( new ), j);

  button_quit = gtk_button_new_with_label ( "Quit" );
  g_signal_connect( button_quit, "clicked", G_CALLBACK( gtk_main_quit ), NULL);

  // CONTROL BOX

  control_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_container_add( GTK_CONTAINER(control_box), button_new );
  gtk_container_add( GTK_CONTAINER(control_box), button_quit );

  // SCORE
  j->label_score = gtk_label_new ( "score 0" );

  char str[10];
  sprintf(str, "%d", j->delay);
  j->label_delay = gtk_label_new ( str );

  // RIGHT BOX
  right_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_add( GTK_CONTAINER(right_box), control_box );
  gtk_container_add( GTK_CONTAINER(right_box), j->label_score );
  gtk_container_add( GTK_CONTAINER(right_box), j->label_delay );


  //////////////
  // MAIN BOX //
  //////////////

  // FALSE: les composants internes n'auront pas forcément la même largeur.
  // TRUE: les composants internes auront forcément la même largeur.
  // 10: bords autour des composants.
  main_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
  gtk_container_add( GTK_CONTAINER( window ), main_box );
  gtk_container_add ( GTK_CONTAINER (main_box), left_box );
  gtk_container_add ( GTK_CONTAINER (main_box), right_box );

  //////////////
  // TIME OUT //
  //////////////

  g_timeout_add (1000, timer, (gpointer) j );

  gtk_widget_show_all( main_box );
}

int main(int argc, char *argv[]) {

  /* Passe les arguments à GTK, pour qu'il extrait ceux qui le concernent. */
  gtk_init(&argc, &argv);

  // Pour des pièces aléatoires
  srand(time(NULL));

  Jeu j;

  initialiseGrille( j.g );
  genererPieces( j.tab );
  j.score = 0;
  j.delay = 16;
  j.delay_max = 16;

  // TEST ZONE
  //Piece p = j.tab[3];
  //ecrirePiece(j.g, p, hauteurExacte(j.g, 1, &p), 1);
  nouvellePiece( &j );
  // END TEST ZONE

  creerIHM( &j );

  //////////
  // LOOP //
  //////////
  /* Rentre dans la boucle d'événements. */
  /* Tapez Ctrl-C pour sortir du programme ! */
  gtk_main();
  return 0;

}
