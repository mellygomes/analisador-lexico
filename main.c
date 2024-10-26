#include "analisadorLexico.h" 
#include "src/SimbolTable/simboltable.h"
#include "src/HashTable/hashtable.h"

int main() {
    AnalisadorLexico lex;
    Token token;

    IniciarToken(token);
    InicializarAnalizadorLexico(&lex);

    printf("\n\n");

    while(1) {
        token = getToken(&lex);
        if (strcmp(token.nome, "EOF") == 0) {
            break;
        }

        printf("<%s, \"%s\"> %i, %i\n", token.nome, token.valor, token.linha, token.coluna);
    }

    printf("\n\n");

    return 0;
}