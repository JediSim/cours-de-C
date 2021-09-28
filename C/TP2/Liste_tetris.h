#ifndef _LISTE_H_
#define _LISTE_H_

typedef char* Elem; /* Vous changerez après ce type lorsque vous l'utiliserez pour le tetris */
struct SCellule {
    Elem val;
    struct SCellule* pred;
    struct SCellule* succ;
};
typedef struct SCellule Cellule;
typedef Cellule* Adr;
typedef Cellule Liste; 
/* Ici, la liste vide est une liste avec un élément (non utilisé). */
/* alloue dynamiquement une liste et retourne son adresse */
extern Liste* Liste_creer();
/* initialise correctement la liste donnée en paramètre, comme si elle était vide. */
extern void Liste_init( Liste* L );
/* détruit tous les éléments stockés dans la liste L. La liste est vide après.*/
extern void Liste_termine( Liste* L );
/* détruit tous les éléments stockés dans la liste L, et libère l'espace mémoire de la liste. */
extern void Liste_detruire( Liste* L );
/* retourne l'adresse du premier élément. */
extern Adr Liste_debut( Liste* L );
/* retourne l'adresse après le dernier élément. */
extern Adr Liste_fin( Liste* L );
/* passe à l'élément suivant. */
extern Adr Liste_suivant( Liste* L, Adr A );
/* passe à l'élément précédent. */
extern Adr Liste_precedent( Liste* L, Adr A );
/* insère devant l'élément A un nouvel élément de valeur v dans L. */
extern Adr Liste_insere( Liste* L, Adr A, Elem v );
/* supprime l'élément A dans L. */
extern void Liste_supprime( Liste* L, Adr A );
/* retourne la valeur stockée dans l'élément A de la liste L. */
extern Elem Liste_valeur( Liste* L, Adr A );
/* modifie la valeur stockée dans l'élément A de la liste L, en lui assignant la valeur v. */
extern void Liste_modifie( Liste* L, Adr A, Elem v );
#endif