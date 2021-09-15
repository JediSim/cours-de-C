#include <stdlib.h>
#include <stdio.h>

#define COLOR(X) printf("\033["X"m")

// tableau bidimensionnel de caractères.
typedef char Jeu [6][7];

void affiche(Jeu g)
{
    int j = 0;
    int i = 0;
    for(;i<6;i++)
    {
        printf("|");
        for(;j<7;j++)
        {
            if (g[i][j]=='x')
            {
                // COLOR("33");
                printf(" %c",g[i][j]);
                printf(" |");
                // COLOR("0");
            }else if (g[i][j]=='0')
            {
                // COLOR("31");
                printf(" %c",g[i][j]);
                printf(" |");
                // COLOR("0");
            }else
            {
                printf(" %c |",g[i][j]);
            } 
        }
        printf("\n");
        j = 0;
    }
}

void init (Jeu g)
{
    int i,j = 0;
    for(;i<6;i++)
    {
        for(;j<7;j++)
        {
            g[i][j] = '.';
        }
        j = 0;
    }
}

void joue (int j, int c, Jeu p)
{
    int i = 0;
    // c = c-1;
    if(j==1)
    {
        while(p[i][c]=='.' && !(p[i][c]==0))
        {
            i++;
        }
        p[i-1][c]='x';
    }else if(j==2)
    {
        while(p[i][c]=='.' && !(p[i][c]==0))
        {
            i++;
        }
        p[i-1][c]='o';
    }
}

int n_est_pas_pleine(int c, Jeu g)
{
    return g[0][c]=='.';
}

int main()
{
    Jeu game;
    init(game);
    int e,p;
    e=1;                      /* stock le dernier caractère entré par l'utilisateur */
    p=1;                  /* indique le joueur qui doit jouer */
    while (e!=0) {                /* on ne quitte le jeu que quand l'utilisateur entre 0 */
        affiche(game);
        printf("Quelle colonne joue le joueur %d ? (0 pour sortir)",p);
        scanf("%d", &e);            /* le joueur entre la colonne ou il souhaite jouer */
        if (e!=0 ){         
            if (n_est_pas_pleine(e-1,game)) {     /* on doit tester si la colonne est déja pleine ou non */
                joue(p,e-1,game);           /* on met a jour la grille */
                p=3-p;              /* le joueur courant change */
            }
            else {
                printf("C'est impossible !\n");
            };
        }   
    }
    return 0;
}