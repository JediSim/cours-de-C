// REY PICHENOT

#include <stdio.h>
#include <stdlib.h>

typedef void* address_t;

int main() {
    address_t *x;

    x = malloc(sizeof(address_t));
    *x = (void*)3735928559;

    printf(" x = %p\n", (address_t)x);
    printf(" *x = %p\n", (address_t)*x);
    printf(" &x = %p\n", (address_t)&x);
}