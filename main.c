#include "analisadorLexico.h" 
#include "src/SimbolTable/simboltable.h"
#include "src/HashTable/hashtable.h"

int main() {
    AnalisadorLexico *lex = malloc(sizeof(AnalisadorLexico));
    if (lex == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    Token token;
    No *TS = NULL;
    char *tbl[TAM];

    InicializarAnalizadorLexico(lex);
    InserirPalavrasReservadas(tbl);
    Inserir(&TS, "\0");
    IniciarToken(token);

    printf("\n");

    while(1) {
        token = getToken(lex, tbl, TS);
        if (strcmp(token.nome, "EOF") == 0) {
            break;
        }

        printf("<%s, \"%s\"> %i, %i\n", token.nome, token.valor, token.linha, token.coluna);
    }
    Imprimir(TS);

    free(TS);
    free(lex);
    return 0;
}