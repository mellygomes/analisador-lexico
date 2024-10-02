#ifndef ANALISADORLEXICO_H
#define ANALISADORLEXICO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tabelasimbolo.h"

typedef struct {
    int head, numLinha, coluna;
    char fita[500], lexema[300];
    
}  AnalisadorLexico;

typedef struct {
    char Nome[300];
    char ValorLexema[300];
    int linha, coluna;
} Token;

void InicializarAnalizadorLexico(AnalisadorLexico *lex);
void IniciarToken(Token token);
void IniciarAnaliseLexica(AnalisadorLexico *lex);
char *concatenarChar(char texto[], char letra);
void AtualizarLinhaColuna(AnalisadorLexico *lex, char c);
char ObterCharactere(AnalisadorLexico *lex);

void EstadoInicial(AnalisadorLexico *lex, No *listaP);
void q1(AnalisadorLexico *lex, No *TS, No *listaP);
void q2(AnalisadorLexico *lex, No *TS);
void q3(AnalisadorLexico *lex, No *TS);
Token EstadoFinal(AnalisadorLexico *lex, No *TS, char nome[300], char valor[300], int linha, int coluna);

#endif