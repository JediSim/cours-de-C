#include <stdio.h>


int est_bissextile(int a){
    return ((a%4== 0 && a%100 != 0) || (a%400 == 0));
}
int main()
{
    int a;
    scanf("%d",&a);
    if ((a%4== 0 && a % 100 != 0) || (a % 400 == 0))
    {
        printf("l'année %i est bissextile",a);
    }
    else
    {
        printf("l'annee %i n'est pas bissextile",a);
    }
    return 0;
}