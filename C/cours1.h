struct SToken
{
    int sep[128]; // 0 si pas séparateur, 1 sinon
    char mot[48]; // stock le mot courant
    char* texte; // tête de lecture dans le texte
};
typedef struct SToken SToken;

void Token_init(Token* t, char str[], char sep[]);

char* Token_valeur(Token* t);

int Token_fini(Token* t);

void Token_suivant(Token* t);

void Token_termine(Token* t);
