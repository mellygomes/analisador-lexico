#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "src/SimbolTable/simboltable.h"
#include "src/HashTable/hashtable.h"

typedef struct {
    int head, linha, coluna;
    char fita[500], lexema[300];
    
}  AnalisadorLexico;

typedef struct {
    char nome[300];
    char valor[300];
    int linha, coluna;
} Token;

void InicializarAnalizadorLexico(AnalisadorLexico *lex);
void IniciarToken(Token token);
char *concatenarChar(char texto[], char letra);
void AtualizarLinhaColuna(AnalisadorLexico *lex, char c);
char ObterCharactere(AnalisadorLexico *lex);

Token getToken(AnalisadorLexico *lex, char *tbl[], No *TS);
Token buildNumber(AnalisadorLexico *lex, Token token, char *tbl[], No *TS);
Token buildExp(AnalisadorLexico *lex, Token token, char *tbl[], No *TS);
Token buildToken(AnalisadorLexico *lex, char *tbl[], No *TS, int state);

#endif