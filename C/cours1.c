#include <stdio.h>
#include <stdlib.h>

#include "cours1.h"



//-----------------------------------------------------------------------------------------------------Q.2

int is_in_string(char c, char s[])
{
    int i = 0;
    while(s[i] != 0)
    {
        if(s[i] == c)return 1;
        i++;
    }
    return 0;
}

int nb_words(char t[], char sep[])
{
    int w,l,n = 0;
    while(t[n] != 0)
    {
        if(t[n] == ' ')
        {
            l = w>0?l++:l;
            w = 0;
        }
        else w++;
        n++;
    }
    l = w>0?l++:l;
    return l;
}

int size_longest_word(char t[], char sep[])
{
    int w = 0;
    int l = 0;
    int n = 0;
    while(t[n] != 0)
    {
        if(t[n] == ' ')
        {
            l = w>l?w:l;
            w = 0;
        }
        else w++;
        n++;
    }
    l = w>l?w:l;
    return l;
}

//-----------------------------------------------------------------------------------------------------Q.4
/**
Substitut d'un mot par un autre mot
- mot meme taille : easy on remplace dans la chaine
- mot plus court : moyen possible via décalage
- mot plus long : impossible chaine de départ trop courte
**/

//-----------------------------------------------------------------------------------------------------Q.5
/**
/!\ existe une version plus rapide /!\
**/
int remove_letter(char c, char s[])
{
    int nr = 0;
    int i = 0;
    int j;
    while(s[i] != 0)
    {
        if (c == s[i])
        {
            nr++;
            j = i;
            while (s[j+1] != 0)
            {
                s[j] = s[j+1];
                j++;
            }
            s[j] = 0;
        }else
        {
            i++;
        }
    }
    return nr;
}
// version plus rapide et avec pointeur

int remove_letter_ptr(char c, char s[])
/**
retire la lettre passé en param dans la chaine
param : -c [char] caractere à supprimer
        -s[] [char] chaine dans laquelle on supprime le caractere
return : [int] nb de caractere supprimé
**/
{
    char* j = &s[0];
    char* i = &s[0];
    while (*i != 0)
    {
        if(*i != c)
        {
            *j = *i;
            *j = *(++j);
        }
        i++;
    }
    *j = 0;
    return i-j;
}

//-----------------------------------------------------------------------------------------------------Q.6
/**
Compter le nombre de mot dans un texte.
En python :
D = {'arbre':5,'le':50,...}
D['arbre'] = D['arbre']+1

En C :
On doit creer un type pour le dico et toutes les fct qui vont avec
**/

//-----------------------------------------------------------------------------------------------------Q.7
void Token_init(Token* t, char str[], char sep[])
{
    for(int i=0,i<128,i++) t->sep[i]=0;
    while(*sep)
    {
        t->sep[*sep] = 1;
        sep++;
    }
    t->texte=str;
    Token_suivant(t);
}

char* Token_valeur(Token* t)
{
    return t->mot;
}

int Token_fini(Token* t)
{
    return *t->mot == 0;
}

void Token_suivant(Token* t)
{
    while((*t->texte != 0) && (t->sep[*t->texte] != 0)) // *t->texte == t->texte[0] 
    {
        t->texte++;
    }
    char* m = t->mot;
    while((*t->texte != 0) && (t->sep[*t->texte] == 0)) // On doit tester que le mot soit pas trop long pour le tableau (m-(t->mot) < 48)
    {
        *m++ = *t->texte++;
    }
    *m = 0;
    while((*t->texte != 0) && (t->sep[*t->texte] != 0)) // *t->texte == t->texte[0] 
    {
        t->texte++;
    }
}

void Token_termine(Token* t)
{
    t->texte = NULL;
    *t->mot = 0;
}

//-----------------------------------------------------------------------------------------------------Q.8
/**
On part du principe que strcmp() est deja codée
**/
// bool prefixe(char mot[], char texte[])
// {
//     while(*mot != 0)
//     {
//         if (*mot != *texte)
//         {
//             return 0;
//         }
//         mot++;
//         texte++;
//     }
//     return 1;
// }

// correction prefixe
bool prefixe(char mot[], char texte[])
{
    while(*mot == *texte && *mot && *texte)
    {
        mot++;
        texte++;
    }
    return *mot == 0;
}

bool mot_dans_texte (char* mot, char* texte)
{
    while(*texte != 0)
    {
        if (prefixe(mot,texte))
        {
            return 1;
        }
        texte++;
    }
    return 0;
}

int main()
{
    char sep[] = " ,;:!?.'";
    char str[] = "c'est une phrase de test";
    int s = size_longest_word(str,sep);
    int nb = nb_words(str,sep);
    printf("mot le plus long : %i \n",s);
    printf("nb mot : %i \n",nb);
    printf("Hello world!\n");
    nb = remove_letter_ptr('e',str);
    printf(str);
    printf("\n nb : %i",nb);
    return 0;
}
