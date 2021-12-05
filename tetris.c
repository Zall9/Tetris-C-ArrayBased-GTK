#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"
#include <stdlib.h>
#include <math.h>
#include "tetris.h" 
 

/*Delifer Paul L3 info Guesdon Theo CMI INFO INFO504*/
void initialise_grille(Grille g){
/*Procedure d'initialisation de la grille de jeu*/
    for(int i =0;i<HAUTEUR;i++){
        for(int j=0;j<LARGEUR;j++){
            g[i][j]=32;//32 correspond à la valeur ASCII du caractere ' '
                                          }
                                        }
                                }
int valide(Grille g,int hauteur, int largeur){
    return (largeur <= LARGEUR && largeur >= 0 && hauteur <= HAUTEUR+3 && hauteur >= 0) ;
}
                                        
char lire_case(int x, int y, Grille g){
    /*Fonction permettant de lire une case*/
    if (valide(g,x,y)){
        return g[x][y];
    }
    else{
        return 0;
    }
}
void affiche_grille(Grille g){
    /*Procedure affichant la grille & son état actuel*/
    for(int i = HAUTEUR-1;i>=0;i--){
        printf("%i",i%10);
        printf("||");
        for(int j=LARGEUR-1;j>=0;j--){
            printf("%c", g[i][j]);
                                  }
        printf("||\n");
                                }
    printf(" ||||");
    for(int i = 0; i<LARGEUR;i++){
        printf("|");
                                 }
    printf("\n");
    printf("   ");
    for(int i = 0; i<LARGEUR;i++){
        printf("%i",i%10);
                                 }
    printf("||\n");                 }

/*-------------------------------GÉNÉRATION DES PIECES----------------------------------*/
void generer_pieces(tableauPiece tabPiece){
    /*Fonction générant un tableau contenant les pieces disponibles en jeu*/
  // I
  // I
  // I
  // I
  tabPiece[0].hauteur = 4;
  tabPiece[0].largeur = 1;
  tabPiece[0].forme[0] = "I";
  tabPiece[0].forme[1] = "I";
  tabPiece[0].forme[2] = "I";
  tabPiece[0].forme[3] = "I";
  tabPiece[0].rotD = 1;
  tabPiece[0].rotG = 1;

  // IIII
  tabPiece[1].hauteur = 1;
  tabPiece[1].largeur = 4;
  tabPiece[1].forme[0] = "IIII";
  tabPiece[1].rotD = 0;
  tabPiece[1].rotG = 0;

  // %%
  // %%
  tabPiece[2].hauteur = 2;
  tabPiece[2].largeur = 2;
  tabPiece[2].forme[0] = "%%";
  tabPiece[2].forme[1] = "%%";
  tabPiece[2].rotD = 2;
  tabPiece[2].rotG = 2;

  // LL
  //  L
  //  L
  tabPiece[3].hauteur = 3;
  tabPiece[3].largeur = 2;
  tabPiece[3].forme[0] = "LL";
  tabPiece[3].forme[1] = " L";
  tabPiece[3].forme[2] = " L";
  tabPiece[3].rotD = 4;
  tabPiece[3].rotG = 6;

  //   L
  // LLL
  tabPiece[4].hauteur = 2;
  tabPiece[4].largeur = 3;
  tabPiece[4].forme[0] = "  L";
  tabPiece[4].forme[1] = "LLL";
  tabPiece[4].rotD = 5;
  tabPiece[4].rotG = 3;

  // L
  // L
  // LL
  tabPiece[5].hauteur = 3;
  tabPiece[5].largeur = 2;
  tabPiece[5].forme[0] = "L ";
  tabPiece[5].forme[1] = "L ";
  tabPiece[5].forme[2] = "LL";
  tabPiece[5].rotD = 6;
  tabPiece[5].rotG = 4;

  // LLL
  // L
  tabPiece[6].hauteur = 2;
  tabPiece[6].largeur = 3;
  tabPiece[6].forme[0] = "LLL";
  tabPiece[6].forme[1] = "L  ";
  tabPiece[6].rotD = 3;
  tabPiece[6].rotG = 5;
  
  // @ 
  //@@@
   tabPiece[7].hauteur = 2;
  tabPiece[7].largeur = 3;
  tabPiece[7].forme[0] = " @ ";
  tabPiece[7].forme[1] = "@@@";
  tabPiece[7].rotD =8;
  tabPiece[7].rotG =10;  
   // @ 
  // @@
  //  @
  tabPiece[8].hauteur = 3;
  tabPiece[8].largeur = 2;
  tabPiece[8].forme[0] = " @";
  tabPiece[8].forme[1] = "@@";
  tabPiece[8].forme[2] = " @";
  tabPiece[8].rotD = 9;
  tabPiece[8].rotG = 7;
   // @ 
  //  @@
  tabPiece[9].hauteur = 2;
  tabPiece[9].largeur = 3;
  tabPiece[9].forme[0] = "@@@";
  tabPiece[9].forme[1] = " @ ";
  tabPiece[9].rotD = 10;
  tabPiece[9].rotG = 8;
  //

  tabPiece[10].hauteur = 3;
  tabPiece[10].largeur = 2;
  tabPiece[10].forme[0] = "@ ";
  tabPiece[10].forme[1] = "@@";
  tabPiece[10].forme[2] = "@ ";
  tabPiece[10].rotD = 7;
  tabPiece[10].rotG = 9;
   // zz 
  
  //zz
  tabPiece[11].hauteur = 2;
  tabPiece[11].largeur = 3;
  tabPiece[11].forme[0] = "ZZ ";
  tabPiece[11].forme[1] = " ZZ";
  tabPiece[11].rotD = 12;
  tabPiece[11].rotG = 12;
  //

  tabPiece[12].hauteur = 3;
  tabPiece[12].largeur = 2;
  tabPiece[12].forme[0] = " Z";
  tabPiece[12].forme[1] = "ZZ";
  tabPiece[12].forme[2] = "Z ";
  tabPiece[12].rotD = 11;
  tabPiece[12].rotG = 11;

     // @ 
  //  @@
  tabPiece[13].hauteur = 2;
  tabPiece[13].largeur = 3;
  tabPiece[13].forme[0] = " ZZ";
  tabPiece[13].forme[1] = "ZZ ";
  tabPiece[13].rotD = 14;
  tabPiece[13].rotG = 14;
  //

  tabPiece[14].hauteur = 3;
  tabPiece[14].largeur = 2;
  tabPiece[14].forme[0] = "Z ";
  tabPiece[14].forme[1] = "ZZ";
  tabPiece[14].forme[2] = " Z";
  tabPiece[14].rotD = 13;
  tabPiece[14].rotG = 13;


}
void affiche_piece(Piece p){
/*Procedure affichant la piece que le joueur à tiré aléatoirement*/
    for (int i=p.hauteur-1;i>=0;i--){
        for(int j=0;p.forme[i][j]!='\0';j++)
            printf("%c", p.forme[i][j]);
        printf("\n");
    }
    //printf("↑");
}

void ecrireCase(Grille g,int ligne, int colonne, char parametre)
/*Procédure écrivant une piece passée en paramètre dans la grille g à l'indice g[colonne][ligne]*/
{
    if (valide(g,ligne,colonne))
    {
        g[colonne][ligne]=parametre;
    }
}
int hauteurPlat(Grille g, int colonne1 , int colonne2)
/*Fonction retournant la hauteur maximale du plateau contenue entre la colonne 1 & 2*/
{
    int hauteur_finale = 0;
    int hauteur_courant = 0;
    for(int j=colonne1;j<colonne2;j++)
        {
            for(int i=HAUTEUR-1;i>=0;i--)
            {
                if(g[i][j]!=' ')
                {
                    hauteur_courant = i+1;
                    if (hauteur_courant > hauteur_finale)
                    {
                        hauteur_finale = hauteur_courant;
                    }
                    break;
                }
            }
        }
    return hauteur_finale;
}

void ecrirePiece(Grille g, Piece p,int colonne, int ligne)
/*procédure écrivant la piece p à l'indice ligne colonne passé en parametre s'il y a de la place*/
{
    {
        for(int i=0;i <p.hauteur; i++)
        {
            for(int j=0; j < p.largeur; j++)
            {
                if(p.forme[i][j]!=' ')
                {
                    ecrireCase(g,colonne+j,ligne+(p.hauteur)-i,p.forme[i][j]);
                }
            }
        }
    }
}

void supprimerLigne(int num_ligne,Grille g)
/*Procedure permettant de supprimer une ligne num_ligne dans la grille g*/
{
    int i;
    for(i=num_ligne;i<HAUTEUR-1;i++)
    {
        for(int j=0;j<LARGEUR;j++)
        {
            g[i][j]=g[i+1][j];
        }
    }
    for(int k=0;k<LARGEUR;k++)
    {
     g[i][k]=32;
    }
}
int ligneRemplie(Grille g, int ligne){
    /*fonction permettant de déterminer si la ligne passée en paramètre dans la grille g est vide ou non*/
    int res=1;
    for(int i=0;i<LARGEUR;i++){
        if (g[ligne][i]==32){
            res=0;
            return res;
        }
    }
    return res;
}
int nettoyer(Grille g){
    /*fonction permettant le nettoyage de la grille. Toutes les lignes remplies seront effacées*/
    int nb_ligne=0;
    for(int i=0;i<HAUTEUR;i++){
        if(ligneRemplie(g,i)){
            supprimerLigne(i,g);
            i--;
            nb_ligne++;
                                     }
                    }
    return nb_ligne;}
int estPosable(Grille g, Piece piece, int h, int l)
{
  if ( h + piece.hauteur-1 >= HAUTEUR || l + piece.largeur-1 >= LARGEUR) return 0;
  for (int i = 0; i < piece.hauteur; i++)
  {
    for (int j = 0; j < piece.largeur; j++)
    {
      if (lire_case(h+piece.hauteur-1-i,l+j,g) != ' ' && piece.forme[i][j] != ' ' ) return 0;
      // g[h+piece->hauteur-1-i][l+j]
    }
  }
  return 1;
}
int hauteurExacte(Grille g, int colonne_gauche, Piece p)
{
    int h = HAUTEUR-p.hauteur;
    for(; h >= 0 && estPosable(g, p, h, colonne_gauche) ; h--){continue;}
    return h;
}

int pieceAleatoire()
{
   int alea = (int)(((double)rand()/((double)RAND_MAX)) * (14));
    return alea;
}
