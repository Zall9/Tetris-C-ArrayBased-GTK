#include  "tetris.h"
#define MARGE_HAUTE 5
#define MARGE_BASSE 2
#define MARGE_LARGEUR 4
typedef struct {
  Grille g;
  Piece tab[ NB_PIECES ];
  int piece; // la piece "en cours" que l'on cherche à placer.
  int col; // la colonne actuelle pour la pièce que l'on cherche à caser.
  int score; // le score
  int delay; // le delay
  int partie;//si la partie est en cours
  GtkWidget *drawing_area;
  GtkWidget *label_score_courant;
  GtkWidget *delay_courant;
} Jeu;

void findepartie(Jeu* pJeu);
gint decompte( gpointer data );
void nouvellePiece(Jeu* jeu);
void dessineCarre( cairo_t* cr, int ligne, int colonne, char c );
void dessineGrille( cairo_t* cr, Grille g);
void dessinePiece( cairo_t* cr, Jeu* pJeu );
void nouvellePiece(Jeu* jeu);
void creerIHM( Jeu* ptrJeu);
gboolean realize_evt_reaction( GtkWidget *widget, gpointer data );
gboolean tourner_droite(GtkWidget *widget, gpointer data );
gboolean tourner_gauche(GtkWidget *widget, gpointer data );
gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data);
gboolean on_draw( GtkWidget *widget, GdkEventExpose *event, gpointer data );
gboolean Gauche( GtkWidget *widget, gpointer data );
gboolean Droite( GtkWidget *widget, gpointer data );
gboolean Bas( GtkWidget *widget, gpointer data );
gboolean New( GtkWidget *widget, gpointer data );