#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    struct No *proximo;
    char *str;
} No;

void Inserir(No **lista, char *str);
void Imprimir(No *no);
char *Buscar(No **lista, char str[]);
int BuscarIndice(No **lista, char str[]);
void InserirPalavrasReservadas(No **lista);

#endif