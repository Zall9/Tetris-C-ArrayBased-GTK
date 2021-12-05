#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include <string.h>
#include <gdk/gdkkeysyms.h>
#include "gtktetris.h"
#include "tetris.h"
#define TAILLE_CARRE 32
void findepartie(Jeu* pJeu)
/*
description: test si la partie est terminer
parametre: la structure jeu
renvois: rien
*/
{
  if (hauteurPlat(pJeu->g,0,LARGEUR-1)>=HAUTEUR)
    {
      pJeu->partie=0;
    }
  }


gint decompte( gpointer data )
{
/*
description: timer du delay 
parametre: data = la structure jeu
renvois: rien de remarquable
*/
  Jeu* pJeu = (Jeu*) data;
  char str[15];

  if (pJeu->delay>=0){
    (pJeu->delay)--;
  }
  else{
    pJeu->delay=40;
    pJeu->delay=pJeu->delay-1- (pJeu->score)/20;
    Bas(pJeu->drawing_area,data);
  }
  sprintf(str, "%d", pJeu->delay);
  gtk_label_set_text( GTK_LABEL(pJeu->delay_courant), str ); 
  g_timeout_add (200, decompte, (gpointer) pJeu ); // réenclenche le timer.
  return 0;
}
void nouvellePiece(Jeu* jeu){
  /*
description: crée une nouvelle piece(entier utiliser dans le tableau de pierce) et la place 
parametre: la structure jeu
renvois: rien
*/
  jeu->piece=pieceAleatoire();
  //jeu->tab[piece]=jeu->piece;
  jeu->col=((LARGEUR- jeu->tab[jeu->piece].largeur)/2);
  //ecrirePiece(jeu->g,jeu->tab[jeu->piece],jeu->col,HAUTEUR-4);
}
void dessinePiece( cairo_t* cr, Jeu* pJeu ){
  /*
description:dessine la piece dans la grille
parametre: cr, la structure jeu
renvois:ren
*/
  int pieceCourante=pJeu->piece;
  Piece pieceCouranteItem=pJeu->tab[pieceCourante];
  
  for(int i=0; i<pieceCouranteItem.hauteur;i++){
    
    for (int j=0; j<pieceCouranteItem.largeur;j++)
    {
      dessineCarre(cr, (HAUTEUR+pieceCouranteItem.hauteur-i-1),(pJeu->col+j),pieceCouranteItem.forme[i][j]);

    }
    
  }

  
}
/*Fonction Draw*/
gboolean realize_evt_reaction( GtkWidget *widget, gpointer data ){
   // force un événement "draw" juste derrière.
  Jeu* pJeu = (Jeu*) data;
  gtk_widget_queue_draw( pJeu->drawing_area ); 
  return TRUE;}
 // c'est la réaction principale qui va redessiner tout.
int partie=1;

gboolean tourner_droite(GtkWidget *widget, gpointer data ){
  /*
description: tourne la piece a droite( recupère la piece correspondant a une rotation de 90° d'une piece)
parametre: une piece
renvois:boolean
*/
  Jeu* pJeu = (Jeu*) data;
  pJeu->piece = pJeu->tab[pJeu->piece].rotD;
  gtk_widget_queue_draw(pJeu->drawing_area);
  return TRUE;
}
gboolean tourner_gauche(GtkWidget *widget, gpointer data ){
    /*
description: tourne la piece a gauche( recupère la piece correspondant a une rotation de 90° d'une piece)
parametre: une piece
renvois:boolean
*/
  Jeu* pJeu = (Jeu*) data;
  pJeu->piece = pJeu->tab[pJeu->piece].rotG;
  gtk_widget_queue_draw(pJeu->drawing_area);
  return TRUE;
}
gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
/*
description: quand l'utilisateur appue sur une touche, regarde quel touche est préssé
             et effectue les action en fonctino de cette touche
*/
  switch (event->keyval)
  {
    case GDK_KEY_Left:
      Gauche( widget, user_data );
      
      break;
    case GDK_KEY_Right:
      Droite( widget, user_data );
      break;
    case GDK_KEY_space:
      Bas( widget, user_data );
      break;
    case GDK_KEY_Down:
      tourner_gauche( widget, user_data );
      break;
    case GDK_KEY_Up:
      tourner_droite( widget, user_data );
      break;
    default:
      break;
  }
  return TRUE;
}
gboolean on_draw( GtkWidget *widget, GdkEventExpose *event, gpointer data )
 {
   
   // Ces premières lignes permettent de récupérer la zone d'affichage
   // et d'initialiser un objet Cairographics cr qui permettra de dessiner
   // sur cette zone.
   GdkWindow* window = gtk_widget_get_window(widget);
   cairo_region_t* cairoRegion = cairo_region_create();
   GdkDrawingContext* drawingContext= gdk_window_begin_draw_frame( window, cairoRegion );
   cairo_t* cr = gdk_drawing_context_get_cairo_context( drawingContext );
   Jeu* pJeu = (Jeu*) data;
   // (A) maintenant je peux dessiner
   
   dessineGrille(cr,pJeu->g);

   dessinePiece(cr,pJeu);
   findepartie(pJeu);
   // (B) On a fini, on peut détruire la structure.
   gdk_window_end_draw_frame(window,drawingContext);
   // cleanup.
   cairo_region_destroy(cairoRegion);
   return TRUE;
}

void dessineCarre( cairo_t* cr, int ligne, int colonne, char c ){
    /*
description: dessine une case 
parametre: cr, deux entier pour la ligne et la colonne dans la grille et un charactere (voir tab)
renvois:rien
*/
  switch (c)
  {
    case (' '):
      cairo_set_source_rgb (cr, 1,1,1); //choisit le blanc
      
        break;
      case ('I'):
         cairo_set_source_rgb (cr, 0, 1, 0); // choisit le vert
        break;
      case ('Z'):
        cairo_set_source_rgb (cr, 0, 1, 0); // choisit le vert
        break;
      case ('%'):
        cairo_set_source_rgb (cr, 1, 0, 0); // choisit le vert

        break;
      case ('L'):
        cairo_set_source_rgb (cr, 0, 0, 0.5); // choisit le vert

        break;
      case ('@'):
        cairo_set_source_rgb (cr, 0.5, 0, 0); // choisit le vert

        break;
        default:
        break;
      }
      cairo_rectangle (cr,(colonne+MARGE_LARGEUR/2) * TAILLE_CARRE,(HAUTEUR-1-ligne+MARGE_HAUTE)*TAILLE_CARRE ,TAILLE_CARRE,TAILLE_CARRE); // x, y, largeur, hauteur
      cairo_fill_preserve( cr ); // remplit la forme actuelle (un rectangle)
      // => "_preserve" garde la forme (le rectangle) pour la suite
      cairo_set_line_width(cr, 3);
      // cairo_set_source_rgb (cr, 0, 0.5, 0); // choisit le vert sombre
      cairo_set_source_rgb (cr, 0, 0, 0);
      cairo_stroke( cr ); // trace la forme actuelle (le même rectangle)
}
void dessineGrille( cairo_t* cr,Grille g){
    /*
description: dessine la grille récupéré dans tetris.c
parametre: une grille
renvois:rien
*/
  for (int i = 0; i <HAUTEUR; i++)
  {
    for (int j = 0; j <LARGEUR; j++)
    {
      dessineCarre(cr,i,j,g[i][j]);
    }
    
  }
  
 }
gboolean Gauche( GtkWidget *widget, gpointer data )
  /*
description: déplace la piece a gauche d'une case dans la grille
parametre: une piece
renvois:boolean
*/
{
  // Recupère la valeur passée en paramètre.
  Jeu* pJeu = (Jeu*) data;
  if((pJeu->col)>0) (pJeu->col)--;
  
  gtk_widget_queue_draw(pJeu->drawing_area);
  return TRUE; // Tout s'est bien passé
}

gboolean Droite( GtkWidget *widget, gpointer data )
  /*
description: déplace la piece a droite d'une case dans la grille
parametre: une piece
renvois:boolean
*/
{
Jeu* pJeu = (Jeu*) data;
  if((pJeu->col)<LARGEUR-pJeu->tab[pJeu->piece].largeur) (pJeu->col)++;
  gtk_widget_queue_draw(pJeu->drawing_area);
  return TRUE;
}


gboolean Bas( GtkWidget *widget, gpointer data )
  /*
description: déplace la piece le plus en bas possible dans la grille en fonction de sa position actuel
parametre: une piece
renvois:boolean
*/
{
  Jeu* pJeu = (Jeu*) data;
  int hauteur= hauteurExacte(pJeu->g,pJeu->col,pJeu->tab[pJeu->piece]);
  //int hauteurPlato=hauteurPlat(pJeu->g,hauteur,pJeu->col);
  
  if (pJeu->partie==1)
  {
    ecrirePiece(pJeu->g ,pJeu->tab[pJeu->piece],pJeu->col,hauteur);
    affiche_grille(pJeu->g);
    pJeu->score+=nettoyer(pJeu->g)*100;
    pJeu->score+=10;
    pJeu->delay=40;
    nettoyer(pJeu->g);
    nouvellePiece(pJeu);
    char str[10];
    sprintf(str, "%d", pJeu->score);
    gtk_label_set_text( GTK_LABEL(pJeu->label_score_courant), str );

  }
    
  gtk_widget_queue_draw(pJeu->drawing_area);
  
  return TRUE; // Tout s'est bien passé


}
gboolean New( GtkWidget *widget, gpointer data )
  /*
description: crée une nouvelle partie (remet tout les compteur et grilles a zero)
parametre: structure piece
renvois:boolean
*/
{
  // Recupère la valeur passée en paramètre.
  Jeu* pJeu = (Jeu*) data;
  pJeu->delay=40;
  pJeu->score=0;
  pJeu->partie=1;
  initialise_grille( pJeu->g );
  nouvellePiece(pJeu);
  gtk_widget_queue_draw(pJeu->drawing_area);
  return TRUE; // Tout s'est bien passé
}
void creerIHM( Jeu* ptrJeu){
/*
description: crée la fenetre de jeu au lancement du program
parametre: la structure piece
renvois:rien
*/
    ptrJeu->delay=50;
    ptrJeu->score=0;
    ptrJeu->partie=1;
    GtkWidget *window;    
    GtkWidget* button_quit,*new;

    GtkWidget* left,*right,*down;
    
    GtkWidget* drawing_area = gtk_drawing_area_new ();
    
    ptrJeu->drawing_area=drawing_area;
    // largeur=150 pixels, hauteur = 100 pixels.
    gtk_widget_set_size_request (drawing_area, TAILLE_CARRE*(LARGEUR+4), TAILLE_CARRE*(HAUTEUR+7));

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_widget_show  (window);
    
    /* Rentre dans la boucle d'événements. */
    /* Tapez Ctrl-C pour sortir du programme ! */
   /*definition des boxs & labelz*/
    GtkWidget* hbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget* hbox1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget* label = gtk_label_new( "Grille TETRIS" );
    GtkWidget* label_score = gtk_label_new( "score:");
      char str[10];
      sprintf(str, "%d",ptrJeu->score);
      ptrJeu->label_score_courant = gtk_label_new ( str );
      //char str[10];
      //gtk_label_set_text( GTK_LABEL(ptrJeu->label_score_courant), str );
    GtkWidget* label_delay = gtk_label_new( "delay" );
    ptrJeu->delay_courant= gtk_label_new( "0");
    GtkWidget* hbox1_1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget* hbox1_2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget* hbox1_1_1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget* hbox1_1_2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget* hbox1_2_1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget* hbox1_2_2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget* hbox1_2_3 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
    //on ajoute label a hbox
    gtk_container_add ( GTK_CONTAINER (hbox), label );
    gtk_container_add ( GTK_CONTAINER (hbox), hbox1 );
    gtk_container_add ( GTK_CONTAINER (hbox1), hbox1_1 );
    gtk_container_add(GTK_CONTAINER(hbox1_1),drawing_area);
    gtk_container_add ( GTK_CONTAINER (hbox1), hbox1_2 );
    gtk_container_add ( GTK_CONTAINER (hbox1_1), hbox1_1_1 );
    gtk_container_add ( GTK_CONTAINER (hbox1_1), hbox1_1_2 );
    gtk_container_add ( GTK_CONTAINER (hbox1_2), hbox1_2_1 );
    gtk_container_add ( GTK_CONTAINER (hbox1_2), hbox1_2_2 );
    gtk_container_add ( GTK_CONTAINER (hbox1_2), hbox1_2_3 );


    
    new = gtk_button_new_with_label( "NEW" );
    button_quit = gtk_button_new_with_label ( "Quit" );
    left = gtk_button_new_with_label( "<" );
    down = gtk_button_new_with_label( "v" );
    right = gtk_button_new_with_label( ">" );
    g_signal_connect( G_OBJECT(drawing_area), "realize", 
                  G_CALLBACK(realize_evt_reaction),
          ptrJeu );
    g_signal_connect( G_OBJECT (drawing_area), "draw",
                  G_CALLBACK (on_draw), 
          ptrJeu );
    g_signal_connect( button_quit, "clicked",
                  G_CALLBACK( gtk_main_quit ),
          ptrJeu);
    g_signal_connect( new, "clicked",
                  G_CALLBACK( New ),
          ptrJeu);
    g_signal_connect( left, "clicked",
                  G_CALLBACK( Gauche ),
          ptrJeu);
    g_signal_connect( right, "clicked",
                  G_CALLBACK(Droite ),
          ptrJeu);
    g_signal_connect(down, "clicked",
                  G_CALLBACK( Bas ),
          ptrJeu);
    g_signal_connect (G_OBJECT (window), "key_press_event",
                   G_CALLBACK (on_key_press), ptrJeu );
    //ajout du boutton quit a hbox1
    gtk_container_add( GTK_CONTAINER( hbox1_2_1 ), button_quit );
    gtk_container_add( GTK_CONTAINER( hbox1_2_1 ), new );
    gtk_container_add( GTK_CONTAINER( hbox1_1_2 ), left );
    gtk_container_add( GTK_CONTAINER( hbox1_1_2 ), down );
    gtk_container_add( GTK_CONTAINER( hbox1_1_2 ), right );
    gtk_container_add( GTK_CONTAINER( hbox1_2_2 ), label_score );
    gtk_container_add( GTK_CONTAINER( hbox1_2_2 ), ptrJeu->label_score_courant );
    gtk_container_add( GTK_CONTAINER( hbox1_2_3 ), label_delay );
    gtk_container_add( GTK_CONTAINER( hbox1_2_3 ), ptrJeu->delay_courant );
    
    gtk_container_add( GTK_CONTAINER( window ), hbox );
    gtk_widget_show  (hbox);
    gtk_widget_show  (hbox1_1);
    gtk_widget_show  (hbox1_1_1);
    gtk_widget_show  (hbox1_1_2);
    gtk_widget_show  (hbox1_2);
    gtk_widget_show  (hbox1_2_1);
    gtk_widget_show  (hbox1_2_2);
    gtk_widget_show  (hbox1_2_3);
    gtk_widget_show  (hbox1);
    gtk_widget_show_all(window);
    gtk_widget_show_all(hbox);
    g_timeout_add (2000, decompte,(gpointer)ptrJeu );
    
}


int main( int argc, char *argv[])
{
    gtk_init (&argc, &argv);
    Jeu jeu;
    initialise_grille( jeu.g );
    
    affiche_grille(jeu.g);
    generer_pieces(jeu.tab);
    nouvellePiece(&jeu);
    creerIHM(&jeu);
    affiche_grille(jeu.g);
    nouvellePiece(&jeu);
    
    
    gtk_main ();
    
      {return 0;}
}

