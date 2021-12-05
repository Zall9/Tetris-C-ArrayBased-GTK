#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED
#define HAUTEUR 12
#define LARGEUR 16
#define NB_PIECES 14
#define HAUTEUR_MAX_DES_PIECES 4

#include <stdio.h>
#include <stdlib.h>
/*Delifer Paul L3 info Guesdon Theo CMI INFO INFO504*/
struct SPiece {
  int   hauteur;
  int   largeur;
  char* forme[ HAUTEUR_MAX_DES_PIECES ];
  int rotD;
  int rotG;
};

typedef struct SPiece Piece;
typedef Piece tableauPiece[7];
typedef char Grille[HAUTEUR][LARGEUR];
void initialise_grille(Grille g);
int valide(Grille g, int hauteur,int largeur);
char lire_case(int x, int y, Grille g);
void affiche_grille(Grille g);
void generer_pieces(tableauPiece tabpiece);
void affiche_piece(Piece p);
void ecrireCase(Grille G,int ligne, int colonne, char parametre);
int hauteurPlat(Grille g, int i, int j);
void ecrirePiece(Grille g, Piece p,int colonne, int ligne);
void supprimerLigne(int num_ligne,Grille g);
int ligneRemplie(Grille g, int ligne);
int nettoyer(Grille g);
int hauteurExacte( Grille g, int col_gauche, Piece piece );
int pieceAleatoire();
#endif // TETRIS_H_INCLUDED
