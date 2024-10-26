#ifndef SIMBOLTABLE_H
#define SIMBOLTABLE_H

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

#endif