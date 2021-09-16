#include <stdio.h>
#include <stdlib.h>

int est_bissextile(int a){
    return ((a%4== 0 && a%100 != 0) || (a%400 == 0));
}

int nb_annees_bissextiles( int debut, int fin )
{
    int cpt = 0;
    int i = debut;
    while(debut != fin)
    {
        if (est_bissextile(debut))
        {
            cpt++;
        }
        debut++;
    }
    if (est_bissextile(debut))
    {
        cpt++;
    }
    return cpt;
}

int main(int argc, char* argv[])
{
    int res = nb_annees_bissextiles(atoi(argv[1]), atoi(argv[2]));
    printf("%i",res);
    return 0;
}