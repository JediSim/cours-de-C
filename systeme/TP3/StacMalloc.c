// REY PICHENOT

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define Ko 1024

void f2(){

    printf("-----------------------------------------------f2\n");

    char* BLK1 = (char*) malloc(4*Ko);
    char* BLK2 = (char*) malloc(4*Ko);
    char* BLK3 = (char*) malloc(4*Ko);

    printf("Adresse de la variable BLK1: %p, adresse du bloc %p \n", &BLK1, BLK1);

    printf("Adresse de la variable BLK2: %p, adresse du bloc %p \n", &BLK2, BLK2);

    printf("Adresse de la variable BLK3: %p, adresse du bloc %p \n", &BLK3, BLK3);

}

void f1(){

    printf("-----------------------------------------------f1\n");

    char* BLK1 = (char*) malloc(4*Ko);
    char* BLK2 = (char*) malloc(4*Ko);
    char* BLK3 = (char*) malloc(4*Ko);

    printf("Adresse de la variable BLK1: %p, adresse du bloc %p \n", &BLK1, BLK1);

    printf("Adresse de la variable BLK2: %p, adresse du bloc %p \n", &BLK2, BLK2);

    printf("Adresse de la variable BLK3: %p, adresse du bloc %p \n", &BLK3, BLK3);

    f2();
}

void rec(int n){

    printf("-------------------rec %i\n",n);

    char* BLK1 = (char*) malloc(4*Ko);

    printf("Adresse de la variable BLK1: %p, adresse du bloc %p \n", &BLK1, BLK1);

    if (n > 0){
        rec(n-1);
    }
}

int main(int argc, char* argv[]){
    int cps = sizeof(char*);
    int n = 5;
    printf("Taille du pointeur %d\n", cps);

    f1();

    printf("---------------------------------début de la recursion-----------\n");

    rec(n);

    return 0;
}

