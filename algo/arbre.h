struct noeud_int
{
    int val;
    struct noeud_int *brg;
    struct noeud_int *brd;
};

typedef struct noeud_int *arbre_int;

