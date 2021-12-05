#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tetris.h"
#include "gtktetris.h"
/*Delifer Paul L3 info Guesdon Theo CMI INFO INFO504*/
int main()
{
    int nbpiece=0;
    int game=1;
    int cpt=0;
    int hauteur_min;
    tableauPiece tabPiece;
    Grille tetris;
    initialise_grille(tetris);
    generer_pieces(tabPiece);

    //cpt = hauteurPlat(tetris);
    int colonne;
    char str[ 8 ];
    printf("\n");

    while (nbpiece<NB_PIECES && game!=0 && hauteurPlat(tetris,0,LARGEUR-1)<HAUTEUR)
    {
        affiche_grille(tetris);
        printf("\n");
        int piece =pieceAleatoire();
        affiche_piece(tabPiece[piece]);
        printf("\n");
            
        while (1)
        {
            printf( "(g)auche, (d)roite ou (0-%i) colonne: ", LARGEUR-1 );

            if ( scanf( "%7s", str ) == 1 ) {
                if ( str[ 0 ] == 'g' ) {  piece = tabPiece[piece].rotG; }
                else if ( str[ 0 ] == 'd' ) {  piece = tabPiece[piece].rotD; }
                else {
                    colonne = atoi( str );
                    break;
            }
                                            }
        }
        
        printf("Choisissez une colonne ou placer la piece");
        printf("\n");
        scanf("%d",&colonne);
        affiche_grille(tetris);
        printf("\n");

        if (colonne > LARGEUR || colonne < 0)
        {
            printf("vous avez choisi une valeur invalide");
            printf("\n");
        }
        else
        {
            hauteur_min = hauteurExacte( tetris, colonne, tabPiece[piece]);
            ecrirePiece(tetris,tabPiece[piece],colonne,hauteur_min);
            nbpiece++;
            nettoyer(tetris);
        }
    if ((hauteurPlat(tetris,0,LARGEUR-1)>HAUTEUR))
            {
            printf("tu as perdu");
            }
        
    }


    return 0;
    }
